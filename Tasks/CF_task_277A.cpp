#include <iostream>
#include <sstream>
#include <vector>

constexpr int kMaxLanguages = 100;
using EmployeeData = std::vector<std::vector<int>>;
using Graph = std::vector<std::vector<int>>;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

Graph BuildGraph(const EmployeeData& data) {
  Graph res(data.size());

  for (size_t i = 0; i < data.size(); ++i) {
    for (size_t j = i + 1; j < data.size(); ++j) {
      for (size_t k = 0; k < data[i].size(); ++k) {
        if (data[i][k] == 1 && data[j][k] == 1) {
          res[i].push_back(j);
          res[j].push_back(i);
          break;
        }
      }
    }
  }
  return res;
}

void DFS(const Graph& g, size_t i, std::vector<int>& lookup) {
  if (lookup[i]) return;
  lookup[i] = 1;
  for (const auto& next : g[i]) {
    DFS(g, next, lookup);
  }
}

int CountTrees(const Graph& g) {
  std::vector<int> lookup(g.size());
  int count = 0;

  for (size_t i = 0; i < g.size(); ++i) {
    if (lookup[i]) continue;
    DFS(g, i, lookup);
    ++count;
  }

  return count;
}

void Solution(std::istream& input) {
  int n, m;
  input >> n >> m;

  EmployeeData data(n, std::vector<int>(kMaxLanguages + 1));
  for (int i = 0; i < n; ++i) {
    int k;
    input >> k;
    while (k--) {
      int l;
      input >> l;
      data[i][l] = 1;
    }
  }

  Graph g = BuildGraph(data);
  std::cout << CountTrees(g) - 1 << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5 5
1 2
2 2 3
2 3 4
2 4 5
1 5
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
