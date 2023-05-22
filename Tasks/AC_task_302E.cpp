#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

struct Graph {
  Graph(int size) : g(size), count(size) {}
  std::vector<std::unordered_set<int>> g;
  uint32_t count = 0;
};

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void PrintState(const Graph& data) { std::cout << data.count << '\n'; }

void AddEdge(Graph& data, int lhs, int rhs) {
  data.count -= data.g[lhs].empty();
  data.g[lhs].insert(rhs);
  data.count -= data.g[rhs].empty();
  data.g[rhs].insert(lhs);
}

void RemoveEdges(Graph& data, int v) {
  for (const auto& el : data.g[v]) {
    data.g[el].erase(v);
    data.count += data.g[el].empty();
  }
  data.count += !data.g[v].empty();
  data.g[v].clear();
}

void Solution(std::istream& input) {
  int n, q;
  input >> n >> q;
  Graph data(n);
  while (q--) {
    int t;
    input >> t;
    if (t == 1) {
      int u, v;
      input >> u >> v;
      AddEdge(data, u - 1, v - 1);
    } else if (t == 2) {
      int v;
      input >> v;
      RemoveEdges(data, v - 1);
    }
    PrintState(data);
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 7
1 1 2
1 1 3
1 2 3
2 1
1 1 2
2 2
1 1 2
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
