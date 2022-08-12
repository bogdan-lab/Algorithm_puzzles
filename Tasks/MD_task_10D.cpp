#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <unordered_set>
#include <vector>

using Graph = std::vector<std::stack<int>>;
using UniqueGraph = std::vector<std::unordered_set<int>>;

std::vector<int> GetDFSOrder(Graph graph);
UniqueGraph BuildCondensedGraph(Graph reversed_graph,
                                const std::vector<int>& dfs_order);
void AddEdgeToGraph(UniqueGraph& graph, int start, int end);
int CountEdges(const UniqueGraph& graph);

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
  Graph direct_graph(vertex_num);
  Graph reversed_graph(vertex_num);
  while (edge_num--) {
    int start, end;
    input >> start >> end;
    --start;
    --end;
    direct_graph[start].push(end);
    reversed_graph[end].push(start);
  }
  std::vector<int> dfs_order = GetDFSOrder(std::move(direct_graph));
  UniqueGraph unique_graph =
      BuildCondensedGraph(std::move(reversed_graph), dfs_order);
  std::cout << CountEdges(unique_graph) << '\n';
}

int CountEdges(const UniqueGraph& graph) {
  int sum = 0;
  for (const auto& el : graph) {
    sum += el.size();
  }
  return sum;
}

void AddEdgeToGraph(UniqueGraph& graph, int start, int end) {
  int max_id = std::max(start, end);
  if (graph.size() <= max_id) {
    graph.resize(max_id + 1);
  }
  graph[start].insert(end);
}

UniqueGraph BuildCondensedGraph(Graph graph,
                                const std::vector<int>& dfs_order) {
  UniqueGraph res;
  std::vector<int> node_to_comp(dfs_order.size());
  int curr_component_count = 0;
  std::vector<int> lookup(dfs_order.size());
  for (const auto& curr_index : dfs_order) {
    if (lookup[curr_index]) continue;
    std::stack<int> buff;
    buff.push(curr_index);
    lookup[curr_index] = 1;
    node_to_comp[curr_index] = curr_component_count;
    while (!buff.empty()) {
      int top_id = buff.top();
      while (!graph[top_id].empty() && lookup[graph[top_id].top()]) {
        int next_id = graph[top_id].top();
        if (node_to_comp[next_id] != curr_component_count) {
          // We found edge which points from current component to the one formed
          // previously However current graph is reversed therefore we need to
          // store the reversed edge
          AddEdgeToGraph(res, node_to_comp[next_id], curr_component_count);
        }
        graph[top_id].pop();
      }
      if (graph[top_id].empty()) {
        buff.pop();
      } else {
        int next_id = graph[top_id].top();
        graph[top_id].pop();
        lookup[next_id] = 1;
        node_to_comp[next_id] = curr_component_count;
        buff.push(next_id);
      }
    }
    ++curr_component_count;
  }
  return res;
}

std::vector<int> GetDFSOrder(Graph graph) {
  std::vector<int> lookup(graph.size());
  std::vector<int> order;
  int curr_index = 0;
  while (curr_index < graph.size()) {
    if (lookup[curr_index]) {
      ++curr_index;
      continue;
    }
    std::stack<int> buff;
    buff.push(curr_index);
    lookup[curr_index] = 1;
    while (!buff.empty()) {
      int top_id = buff.top();
      while (!graph[top_id].empty() && lookup[graph[top_id].top()]) {
        graph[top_id].pop();
      }
      if (graph[top_id].empty()) {
        order.push_back(top_id);
        buff.pop();
      } else {
        int next_id = graph[top_id].top();
        graph[top_id].pop();
        lookup[next_id] = 1;
        buff.push(next_id);
      }
    }
    ++curr_index;
  }
  std::reverse(order.begin(), order.end());
  return order;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4 4
2 1
3 2
2 3
4 3
)";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
}
