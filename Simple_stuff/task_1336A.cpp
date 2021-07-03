#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
using Graph = std::vector<std::vector<int>>;

enum class Colors { WHITE, GRAY, BLACK };
enum class CityType { UNDEFINED, TOURIST, INDUSTRIAL };

struct DFSnode {
  int t_in;
  int t_out;
  int id;
  int parent;
  int depth;
};

std::vector<DFSnode> do_DFS(const Graph& g) {
  std::vector<DFSnode> dfs;
  dfs.reserve(g.size());
  for (int id = 0; id < g.size(); ++id) {
    dfs.push_back({0, 0, id, 0, 0});
  }
  std::vector<Colors> colors(g.size(), Colors::WHITE);
  std::stack<int> buff;
  buff.push(0);
  int t = 0;
  int depth = 0;
  colors[0] = Colors::GRAY;
  dfs[0].t_in = t++;
  dfs[0].depth = depth++;
  while (!buff.empty()) {
    int top_id = buff.top();
    auto it = std::find_if(g[top_id].begin(), g[top_id].end(),
                           [&](int id) { return colors[id] == Colors::WHITE; });
    if (it == g[top_id].end()) {
      dfs[top_id].t_out = t++;
      colors[top_id] = Colors::BLACK;
      buff.pop();
      depth--;
    } else {
      colors[*it] = Colors::GRAY;
      buff.push(*it);
      dfs[*it].t_in = t++;
      dfs[*it].parent = top_id;
      dfs[*it].depth = depth++;
    }
  }
  return dfs;
}

std::vector<CityType> get_industrial_id(std::vector<DFSnode> dfs, int n,
                                        int k) {
  int t_num = n - k;
  std::partial_sort(
      dfs.begin(), dfs.begin() + t_num, dfs.end(),
      [](const DFSnode& lhs, const DFSnode& rhs) {
        int lhs_include = lhs.t_out - lhs.t_in;
        int rhs_include = rhs.t_out - rhs.t_in;
        return lhs_include > rhs_include ||
               (lhs_include == rhs_include && lhs.depth < rhs.depth);
      });
  std::vector<CityType> ctypes(n, CityType::UNDEFINED);
  for (int i = 0; i < n; ++i) {
    ctypes[dfs[i].id] = i < t_num ? CityType::TOURIST : CityType::INDUSTRIAL;
  }
  return ctypes;
}

int64_t calc_max_pleasure(const Graph& g, int n, int k) {
  std::vector<DFSnode> dfs = do_DFS(g);
  std::vector<CityType> ctypes = get_industrial_id(dfs, n, k);
  int64_t res = 0;
  for (int id = 0; id < n; ++id) {
    if (ctypes[id] == CityType::INDUSTRIAL) {
      int curr_id = id;
      int64_t joy = dfs[curr_id].depth;
      while (ctypes[dfs[curr_id].parent] != CityType::TOURIST) {
        curr_id = dfs[curr_id].parent;
        joy = dfs[curr_id].depth;
      }
      res += joy;
    }
  }
  return res;
}

void solution(std::istream& input) {
  int n, k;
  input >> n >> k;
  int line_num = n - 1;
  Graph g(n);
  while (line_num--) {
    int p1, p2;
    input >> p1 >> p2;
    g[p1 - 1].push_back(p2 - 1);
    g[p2 - 1].push_back(p1 - 1);
  }
  std::cout << calc_max_pleasure(g, n, k) << '\n';
}

int main() {
  /*
    {
    std::stringstream ss;
    ss << R"(7 4
  1 2
  1 3
  1 4
  3 5
  3 6
  4 7)";
    solution(ss);
    std::cout << "expected = 7\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 1
  1 2
  1 3
  2 4)";
    solution(ss);
    std::cout << "expected = 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(8 5
  7 5
  1 7
  6 1
  3 7
  8 3
  2 1
  4 5)";
    solution(ss);
    std::cout << "expected = 9\n";
  }
  {
    std::stringstream ss;
    ss << R"(2 1
  1 2)";
    solution(ss);
    std::cout << "expected = 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 3
  1 2
  1 3
  1 4)";
    solution(ss);
    std::cout << "expected = 3\n";
  }
  {
    std::stringstream ss;
    ss << R"(20 7
9 7
3 7
15 9
1 3
11 9
18 7
17 18
20 1
4 11
2 11
12 18
8 18
13 2
19 2
10 9
6 13
5 8
14 1
16 13)";
    solution(ss);
    std::cout << "expected = 38\n";
  }
*/
  solution(std::cin);
  return 0;
}

