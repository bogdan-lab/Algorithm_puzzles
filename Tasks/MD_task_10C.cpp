#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

using Graph = std::vector<std::stack<int>>;

enum class Color { kWhite, kGrey, kBlack };

struct TopologicalSort {
  TopologicalSort(size_t vertex_num) { order.reserve(vertex_num); }

  bool success = false;
  std::vector<int> order;
};

TopologicalSort DoTopologicalSort(Graph graph);

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
    graph[start].push(end);
  }
  TopologicalSort res = DoTopologicalSort(std::move(graph));
  if (res.success) {
    for (const auto& el : res.order) {
      std::cout << el + 1 << ' ';
    }
    std::cout << '\n';
  } else {
    std::cout << "-1\n";
  }
}

TopologicalSort DoTopologicalSort(Graph graph) {
  std::vector<Color> lookup(graph.size(), Color::kWhite);
  TopologicalSort res(graph.size());
  int curr_index = 0;
  while (curr_index < graph.size()) {
    if (lookup[curr_index] != Color::kWhite) {
      ++curr_index;
      continue;
    }
    std::stack<int> buff;
    buff.push(curr_index);
    lookup[curr_index] = Color::kGrey;
    while (!buff.empty()) {
      int top_id = buff.top();
      while (!graph[top_id].empty() &&
             lookup[graph[top_id].top()] != Color::kWhite) {
        if (lookup[graph[top_id].top()] == Color::kGrey) {
          return res;
        } else {
          graph[top_id].pop();
        }
      }
      if (graph[top_id].empty()) {
        // We have finished with this vertex
        lookup[top_id] = Color::kBlack;
        res.order.push_back(top_id);
        buff.pop();
      } else {
        int next_id = graph[top_id].top();
        graph[top_id].pop();
        lookup[next_id] = Color::kGrey;
        buff.push(next_id);
      }
    }
    ++curr_index;
  }
  res.success = true;
  std::reverse(res.order.begin(), res.order.end());
  return res;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6 6
1 2
3 2
4 2
2 5
6 5
4 6
)";
    Solution(ss);
    std::cout << "expected = 4 6 3 1 2 5\n";
  }
}
