#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
using Graph = std::vector<std::vector<int>>;

enum class Colors { WHITE, GRAY, BLACK };

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
  colors[0] = Colors::GRAY;
  dfs[0].t_in = t++;
  int depth = 0;
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

std::vector<int> get_industrial_id(std::vector<DFSnode> dfs, int ind_num) {
  std::sort(dfs.begin(), dfs.end(),
                    [](const DFSnode& lhs, const DFSnode& rhs) {
                      return lhs.t_out - lhs.t_in > rhs.t_out - rhs.t_in;
                    });
  std::vector<int> res;
  res.reserve(ind_num);
  auto sort_it = dfs.begin() + ind_num;
  for (auto it = sort_it; it != dfs.end(); ++it) {
    res.push_back(it->id);
  }
  return res;
}

int64_t calc_max_pleasure(const Graph& g, int n, int k) {
  std::vector<DFSnode> dfs = do_DFS(g);
  std::vector<int> industrial_ids = get_industrial_id(dfs, k);
  int64_t res = 0;
  std::vector<int> checked(n, 0);
  for(auto id : industrial_ids){
      if(!checked[id]){
          checked[id] = 1;
          int64_t curr_joy = dfs[dfs[id].parent].depth;
          res += curr_joy;
          for(auto child : g[id]){
              if(child != dfs[id].parent){
                  checked[child] = 1;
                  res += curr_joy;
              }
          }
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
  std::cout << calc_max_pleasure(g, n, k);
}

int main() {
  std::stringstream ss;
  ss << R"(7 4
1 2
1 3
1 4
3 5
3 6
4 7)";
  solution(ss);
  return 0;
}

