#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <utility>
#include <vector>

constexpr int kEmptyId = -1;

struct Edge {
  int from = 0;
  int to = 0;
  int64_t weight = 0;
};

void Solution(std::istream& input = std::cin);
void RunTests();

bool CheckIsConnected(const std::vector<std::vector<Edge>>& data, int root);
int64_t FindMST(const std::vector<std::vector<Edge>>& data, int root);
std::vector<int> Condensate(const std::vector<std::vector<Edge>>& data);
void TimeSortDFS(const std::vector<std::vector<Edge>>& data,
                 std::vector<int>& lookup, std::vector<int>& end_time_ids,
                 int root);
void ComponentDFS(const std::vector<std::vector<Edge>>& data,
                  std::vector<int>& comp_map, int id, int curr_comp);
std::vector<std::vector<Edge>> ReverseGraph(
    const std::vector<std::vector<Edge>>& data);
void DFS(int id, const std::vector<std::vector<Edge>>& data,
         std::vector<int>& lookup);

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
  std::vector<std::vector<Edge>> edges(vertex_num);
  while (edge_num--) {
    int l, r;
    int64_t w;
    input >> l >> r >> w;
    --l;
    --r;
    if (l == r) continue;
    edges[l].push_back({l, r, w});
  }
  if (!CheckIsConnected(edges, 0)) {
    std::cout << "NO\n";
    return;
  }
  std::cout << "YES\n" << FindMST(edges, 0) << '\n';
}

void TimeSortDFS(const std::vector<std::vector<Edge>>& data,
                 std::vector<int>& lookup, std::vector<int>& end_time_ids,
                 int id) {
  if (lookup[id]) return;
  lookup[id] = 1;
  for (const auto& e : data[id]) {
    TimeSortDFS(data, lookup, end_time_ids, e.to);
  }
  end_time_ids.push_back(id);
}

std::vector<std::vector<Edge>> ReverseGraph(
    const std::vector<std::vector<Edge>>& data) {
  std::vector<std::vector<Edge>> result(data.size());
  for (const auto& vec : data) {
    for (const auto& e : vec) {
      result[e.to].push_back({e.to, e.from, e.weight});
    }
  }
  return result;
}
void ComponentDFS(const std::vector<std::vector<Edge>>& data,
                  std::vector<int>& comp_map, int id, int curr_comp) {
  if (comp_map[id] != kEmptyId) return;
  comp_map[id] = curr_comp;
  for (const auto& e : data[id]) {
    ComponentDFS(data, comp_map, e.to, curr_comp);
  }
}

std::vector<int> Condensate(const std::vector<std::vector<Edge>>& data) {
  std::vector<int> end_time_ids(data.size());
  std::vector<int> lookup(data.size());
  for (int i = 0; i < data.size(); ++i) {
    if (lookup[i]) continue;
    TimeSortDFS(data, lookup, end_time_ids, i);
  }
  std::reverse(end_time_ids.begin(), end_time_ids.end());
  std::vector<std::vector<Edge>> reversed = ReverseGraph(data);
  std::vector<int> comp_map(data.size());
  int component_id = 0;
  for (const auto id : end_time_ids) {
    if (comp_map[id] != kEmptyId) continue;
    ComponentDFS(data, comp_map, id, component_id);
    ++component_id;
  }
  return comp_map;
}

int64_t FindMST(const std::vector<std::vector<Edge>>& data, int root) {
  // Find minimum income edge for each vertex
  std::vector<Edge> min_edge_to;
  min_edge_to.reserve(data.size());
  for (int i = 0; i < data.size(); ++i) {
    min_edge_to.push_back(
        {/*from=*/0, /*to=*/i, /*weight=*/std::numeric_limits<int64_t>::max()});
  }
  for (const auto& vec : data) {
    for (const auto& e : vec) {
      if (min_edge_to[e.to].weight > e.weight) {
        min_edge_to[e.to].from = e.from;
        min_edge_to[e.to].weight = e.weight;
      }
    }
  }
  // Minimum edges will be in result
  int64_t res = 0;
  for (const auto& e : min_edge_to) {
    if (e.to != root) res += e.weight;
  }
  // Prepare graph for check
  std::vector<std::vector<Edge>> zero_graph(data.size());
  for (const auto& e : min_edge_to) {
    zero_graph[e.from].push_back(e);
  }
  if (CheckIsConnected(zero_graph, root)) {
    return res;
  }
  // Build condensated graph and start from it
  std::vector<int> comp_map = Condensate(zero_graph);
  int comp_count = *std::max_element(comp_map.begin(), comp_map.end()) + 1;
  std::vector<std::vector<Edge>> new_edges(comp_count);
  for (const auto& vec : data) {
    for (const auto& e : vec) {
      int new_from = comp_map[e.from];
      int new_to = comp_map[e.to];
      int64_t new_weight = e.weight - min_edge_to[e.to].weight;
      new_edges[new_from].push_back({new_from, new_to, new_weight});
    }
  }
  res += FindMST(new_edges, comp_map[root]);
  return res;
}

bool CheckIsConnected(const std::vector<std::vector<Edge>>& data, int root) {
  std::vector<int> lookup(data.size());
  DFS(root, data, lookup);
  return std::accumulate(lookup.begin(), lookup.end(), 0) == lookup.size();
}

void DFS(int id, const std::vector<std::vector<Edge>>& data,
         std::vector<int>& lookup) {
  if (lookup[id]) return;
  lookup[id] = 1;
  for (const auto& e : data[id]) {
    DFS(e.to, data, lookup);
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2 1
2 1 10
)";
    Solution(ss);
    std::cout << "expected = NO\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 5
1 2 2
1 3 3
1 4 3
2 3 2
2 4 2
)";
    Solution(ss);
    std::cout << "expected = YES; 6\n";
  }
}
