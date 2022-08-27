#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <vector>

struct EdgeChange {
  int start = -1;
  int end = -1;
  int64_t change = -1;
};

int64_t CalculateFlux(std::vector<std::unordered_map<int, int64_t>>& data,
                      int start, int end, int64_t threshold);
std::vector<EdgeChange> BFS(
    const std::vector<std::unordered_map<int, int64_t>>& data, int start,
    int end, int64_t threshold);
std::vector<EdgeChange> GetPath(const std::vector<EdgeChange>& parents,
                                int start, int end);
int64_t GetThreshold(int64_t max_weight);
void DFS(const std::vector<std::unordered_map<int, int64_t>>& data,
         std::vector<int>& sep, int id);

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int vertex_num, edge_num;
  input >> vertex_num >> edge_num;
  std::vector<std::unordered_map<int, int64_t>> graph(vertex_num);
  std::vector<std::pair<int, int>> edge_order;
  int64_t max_weight = std::numeric_limits<int64_t>::min();
  while (edge_num--) {
    int l, r;
    int64_t w;
    input >> l >> r >> w;
    --l;
    --r;
    graph[l][r] += w;
    graph[r][l] += w;
    edge_order.push_back({l, r});
    max_weight = std::max(max_weight, graph[l][r]);
  }
  int64_t threshold = GetThreshold(max_weight);
  int64_t flux = CalculateFlux(graph, 0, vertex_num - 1, threshold);
  std::vector<int> graph_sep(graph.size());
  DFS(graph, graph_sep, 0);
  std::vector<int> edge_ids;
  for (size_t i = 0; i < edge_order.size(); ++i) {
    if (graph_sep[edge_order[i].first] != graph_sep[edge_order[i].second]) {
      edge_ids.push_back(i + 1);
    }
  }
  std::cout << edge_ids.size() << ' ' << flux << '\n';
  for (const auto& el : edge_ids) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

void DFS(const std::vector<std::unordered_map<int, int64_t>>& data,
         std::vector<int>& sep, int id) {
  if (sep[id]) return;
  sep[id] = 1;
  for (const auto& e : data[id]) {
    DFS(data, sep, e.first);
  }
}

int64_t GetThreshold(int64_t val) {
  int64_t res = 1;
  while (2 * res < val) {
    res *= 2;
  }
  return res;
}

std::vector<EdgeChange> GetPath(const std::vector<EdgeChange>& bfs_res,
                                int start, int end) {
  std::vector<EdgeChange> result;
  int cid = end;
  while (cid != start) {
    result.push_back(bfs_res[cid]);
    cid = bfs_res[cid].start;
  }
  std::reverse(result.begin(), result.end());
  return result;
}

int64_t CalculateFlux(std::vector<std::unordered_map<int, int64_t>>& data,
                      int start, int end, int64_t threshold) {
  // Find path by BFS
  std::vector<EdgeChange> bfs_res = BFS(data, start, end, threshold);
  if (bfs_res[end].start == -1) {
    if (threshold > 0) {
      return CalculateFlux(data, start, end, threshold / 2);
    } else {
      return 0;
    }
  }
  // Find minimum change in the path
  std::vector<EdgeChange> path = GetPath(bfs_res, start, end);
  int64_t min_change = std::min_element(path.begin(), path.end(),
                                        [](EdgeChange l, EdgeChange r) {
                                          return l.change < r.change;
                                        })
                           ->change;
  // Adding flux to the right will result in flux creation to the left
  // Here we push flux with its minimum value through the system.
  // This is the residual capacity should decrease to the given value, when the
  // flux itself - increase
  for (const auto& el : path) {
    data[el.start][el.end] -= min_change;
    if (!data[el.start][el.end]) {
      data[el.start].erase(el.end);
    }
    // Flux from start to end effectively increases capacity of the edge from
    // end to start
    data[el.end][el.start] += min_change;
  }
  return min_change + CalculateFlux(data, start, end, threshold);
}

std::vector<EdgeChange> BFS(
    const std::vector<std::unordered_map<int, int64_t>>& data, int start,
    int end, int64_t threshold) {
  std::vector<EdgeChange> parent(data.size());
  std::vector<int> lookup(data.size());
  std::queue<int> buff;
  buff.push(start);
  while (!buff.empty()) {
    int top_id = buff.front();
    if (top_id == end) break;
    buff.pop();
    for (const auto& e : data[top_id]) {
      if (e.second < threshold || lookup[e.first]) continue;
      lookup[e.first] = 1;
      buff.push(e.first);
      parent[e.first] = {.start = top_id, .end = e.first, .change = e.second};
    }
  }
  return parent;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 3
1 2 3
1 3 5
3 2 7
)";
    Solution(ss);
    std::cout << "expected = 2; 8; 1; 2\n";
  }
}
