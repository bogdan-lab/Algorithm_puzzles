#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
using Graph = std::vector<std::stack<int>>;

enum class Colors { WHITE, GRAY, BLACK };
enum class CityType { UNDEFINED, TOURIST, INDUSTRIAL };

struct DFSnode {
  int t_in;
  int t_out;
  int id;
  int parent;
  int depth;
  int eff_depth;
};

std::vector<DFSnode> do_DFS(Graph g) {
  std::vector<DFSnode> dfs;
  dfs.reserve(g.size());
  for (int id = 0; id < g.size(); ++id) {
    dfs.push_back({0, 0, id, 0, 0, 0});
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
    while (!g[top_id].empty() && colors[g[top_id].top()] != Colors::WHITE) {
      g[top_id].pop();
    }
    if (g[top_id].empty()) {
      dfs[top_id].t_out = t++;
      colors[top_id] = Colors::BLACK;
      buff.pop();
      depth--;
    } else {
      int next_id = g[top_id].top();
      buff.push(next_id);
      colors[next_id] = Colors::GRAY;
      dfs[next_id].t_in = t++;
      dfs[next_id].parent = top_id;
      dfs[next_id].depth = depth++;
    }
  }
  return dfs;
}

std::vector<CityType> get_industrial_id(std::vector<DFSnode> dfs, int n,
                                        int k) {
  std::sort(dfs.begin(), dfs.end(), [](const DFSnode& lhs, const DFSnode& rhs) {
    return lhs.eff_depth > rhs.eff_depth;
  });
  std::vector<CityType> ctypes(n, CityType::UNDEFINED);
  for (int i = 0; i < n; ++i) {
    ctypes[dfs[i].id] = i < k ? CityType::INDUSTRIAL : CityType::TOURIST;
  }
  return ctypes;
}

void fill_effective_depth(const Graph& g, std::vector<DFSnode>& dfs) {
  for (auto& el : dfs) {
    el.eff_depth = el.depth - (el.t_out - el.t_in) / 2;
  }
}

int64_t calc_max_pleasure(const Graph& g, int n, int k) {
  std::vector<DFSnode> dfs = do_DFS(g);
  fill_effective_depth(g, dfs);
  std::vector<CityType> ctypes = get_industrial_id(dfs, n, k);
  int64_t res = 0;
  for (int id = 0; id < n; ++id) {
    if (ctypes[id] == CityType::INDUSTRIAL) {
      res += dfs[id].eff_depth;
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
    g[p1 - 1].push(p2 - 1);
    g[p2 - 1].push(p1 - 1);
  }
  std::cout << calc_max_pleasure(g, n, k) << '\n';
}

void RunTests() {
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
}

int main() {
  //RunTests();
  solution(std::cin);
  return 0;
}

