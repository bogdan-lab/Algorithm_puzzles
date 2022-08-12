#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

using Graph = std::vector<std::vector<int>>;
constexpr int kEmptyId = -1;
std::vector<int> GetConnectionPoints(const Graph& graph);
void DFS(const Graph& graph, int id, int parent, std::vector<int>& lookup,
         std::vector<int>& min_achieve_depth, std::vector<int>& current_depth,
         std::vector<int>& connection_points);

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
  Graph graph(vertex_num);
  while (edge_num--) {
    int start, end;
    input >> start >> end;
    --start;
    --end;
    graph[start].push_back(end);
    graph[end].push_back(start);
  }
  std::vector<int> connection_points = GetConnectionPoints(graph);
  std::sort(connection_points.begin(), connection_points.end());
  connection_points.erase(
      std::unique(connection_points.begin(), connection_points.end()),
      connection_points.end());
  std::cout << connection_points.size() << '\n';
  for (const auto& el : connection_points) {
    std::cout << el + 1 << ' ';
  }
  std::cout << '\n';
}

void DFS(const Graph& graph, int id, int parent, std::vector<int>& lookup,
         std::vector<int>& min_achieve_depth, std::vector<int>& current_depth,
         std::vector<int>& connection_points) {
  lookup[id] = 1;
  current_depth[id] = parent == kEmptyId ? 0 : current_depth[parent] + 1;
  min_achieve_depth[id] = current_depth[id];
  int children_count = 0;
  for (const auto& ch : graph[id]) {
    if (ch == parent) continue;
    if (lookup[ch]) {
      min_achieve_depth[id] =
          std::min(min_achieve_depth[id], current_depth[ch]);
    } else {
      DFS(graph, ch, id, lookup, min_achieve_depth, current_depth,
          connection_points);
      min_achieve_depth[id] =
          std::min(min_achieve_depth[id], min_achieve_depth[ch]);
      if (current_depth[id] <= min_achieve_depth[ch] && parent != kEmptyId) {
        // Check root case separately!
        connection_points.push_back(id);
      }
      ++children_count;
    }
  }
  if (parent == kEmptyId && children_count > 1) {
    connection_points.push_back(id);
  }
}

std::vector<int> GetConnectionPoints(const Graph& graph) {
  std::vector<int> current_depth(graph.size());
  std::vector<int> min_achieve_depth(graph.size());
  std::vector<int> lookup(graph.size());
  std::vector<int> connection_points;

  for (int id = 0; id < graph.size(); ++id) {
    if (lookup[id]) continue;
    DFS(graph, id, /*parent=*/kEmptyId, lookup, min_achieve_depth,
        current_depth, connection_points);
  }

  return connection_points;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6 7
1 2
2 3
2 4
2 5
4 5
1 3
3 6
)";
    Solution(ss);
    std::cout << "expected = 2; 2 3\n";
  }
}
