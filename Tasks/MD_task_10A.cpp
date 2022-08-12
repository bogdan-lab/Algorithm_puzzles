#include <iostream>
#include <limits>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

using Graph = std::vector<std::stack<int>>;

constexpr int kEmptyValue = std::numeric_limits<int>::max();

struct ResultStruct {
  ResultStruct(size_t vertex_num)
      : vertex_to_component(vertex_num, kEmptyValue) {}

  int component_count = 0;
  std::vector<int> vertex_to_component;
};

ResultStruct FindComponents(Graph graph);
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
  int vertex, edges;
  input >> vertex >> edges;
  Graph graph(vertex);
  while (edges--) {
    int start, end;
    input >> start >> end;
    --start;
    --end;
    graph[start].push(end);
    graph[end].push(start);
  }
  ResultStruct res = FindComponents(std::move(graph));
  std::cout << res.component_count << '\n';
  for (const auto& el : res.vertex_to_component) {
    std::cout << el + 1 << ' ';
  }
  std::cout << '\n';
}

ResultStruct FindComponents(Graph graph) {
  std::vector<int> lookup(graph.size());
  ResultStruct res(graph.size());
  std::stack<int> buff;
  int curr_index = 0;
  while (curr_index < graph.size()) {
    if (lookup[curr_index] == 1) {
      ++curr_index;
      continue;
    }
    buff.push(curr_index);
    lookup[curr_index] = 1;
    ++curr_index;
    while (!buff.empty()) {
      int top_id = buff.top();
      while (!graph[top_id].empty() && lookup[graph[top_id].top()] == 1) {
        graph[top_id].pop();
      }
      if (graph[top_id].empty()) {
        // I am in the bottom
        res.vertex_to_component[top_id] = res.component_count;
        buff.pop();
      } else {
        // I can go deeper
        lookup[graph[top_id].top()] = 1;
        buff.push(graph[top_id].top());
      }
    }
    ++res.component_count;
  }
  return res;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 1
1 2
)";
    Solution(ss);
    std::cout << "expected = 2; 1 1 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 2
1 3
2 4
)";
    Solution(ss);
    std::cout << "expected = 2; 1 2 1 2\n";
  }
}
