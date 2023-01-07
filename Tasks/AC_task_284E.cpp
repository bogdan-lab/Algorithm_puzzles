#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

constexpr int kMax = 1'000'000;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void DFS(const std::vector<std::vector<int>>& graph, int id,
         std::vector<int>& lookup, int& count) {
  if (lookup[id]) return;
  lookup[id] = 1;
  ++count;
  if (count >= kMax) return;

  for (const auto& i : graph[id]) {
    DFS(graph, i, lookup, count);
  }

  lookup[id] = 0;
}

int CountPathes(const std::vector<std::vector<int>>& graph) {
  std::vector<int> lookup(graph.size());
  int count = 0;

  DFS(graph, 0, lookup, count);

  return std::min(count, kMax);
}

void Solution(std::istream& input) {
  int n, m;
  input >> n >> m;

  std::vector<std::vector<int>> graph(n);
  while (m--) {
    int u, v;
    input >> u >> v;
    --u;
    --v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  std::cout << CountPathes(graph) << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
