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
  int change = -1;
};

struct MidPath {
  int start = -1;
  int mid = -1;
  int end = -1;
};

int CalculateFlux(std::vector<std::unordered_map<int, int>>& data, int start,
                  int end, int threshold,
                  std::vector<std::unordered_map<int, int>>& actual_flux);
std::vector<EdgeChange> BFS(
    const std::vector<std::unordered_map<int, int>>& data, int start, int end,
    int threshold);
std::vector<EdgeChange> GetPath(const std::vector<EdgeChange>& parents,
                                int start, int end);
int GetThreshold(int max_weight);
void AddNodeToGraph(std::vector<std::unordered_map<int, int>>& data, int start,
                    int end, int weight, int curr_add_node);

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
  std::vector<std::unordered_map<int, int>> graph(vertex_num);
  std::vector<MidPath> edge_order;
  int max_weight = std::numeric_limits<int>::min();
  int curr_add_node = vertex_num;
  while (edge_num--) {
    int l, w, r;
    input >> l >> r >> w;
    --l;
    --r;
    AddNodeToGraph(graph, l, r, w, curr_add_node);
    max_weight = std::max(max_weight, w);
    edge_order.push_back({l, curr_add_node, r});
    ++curr_add_node;
  }
  int threshold = GetThreshold(max_weight);
  std::vector<std::unordered_map<int, int>> actual_flux(graph.size());
  std::cout << CalculateFlux(graph, 0, vertex_num - 1, threshold, actual_flux)
            << '\n';
  for (const auto& el : edge_order) {
    std::cout << actual_flux[el.start][el.mid] - actual_flux[el.end][el.mid]
              << '\n';
  }
}

void AddNodeToGraph(std::vector<std::unordered_map<int, int>>& data, int start,
                    int end, int weight, int curr_add_node) {
  data.resize(curr_add_node + 1);
  data[start][curr_add_node] = weight;
  data[curr_add_node][start] = weight;
  data[curr_add_node][end] = weight;
  data[end][curr_add_node] = weight;
}

int GetThreshold(int val) {
  int res = 1;
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

int CalculateFlux(std::vector<std::unordered_map<int, int>>& data, int start,
                  int end, int threshold,
                  std::vector<std::unordered_map<int, int>>& actual_flux) {
  // Find path by BFS
  std::vector<EdgeChange> bfs_res = BFS(data, start, end, threshold);
  if (bfs_res[end].start == -1) {
    if (threshold > 0) {
      return CalculateFlux(data, start, end, threshold / 2, actual_flux);
    } else {
      return 0;
    }
  }
  // Find minimum change in the path
  std::vector<EdgeChange> path = GetPath(bfs_res, start, end);
  int min_change = std::min_element(path.begin(), path.end(),
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
    actual_flux[el.start][el.end] += min_change;
  }
  return min_change + CalculateFlux(data, start, end, threshold, actual_flux);
}

std::vector<EdgeChange> BFS(
    const std::vector<std::unordered_map<int, int>>& data, int start, int end,
    int threshold) {
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
    ss << R"(2
2
1 2 1
2 1 3
)";
    Solution(ss);
    std::cout << "expected = 4; 1; -3\n";
  }
}
