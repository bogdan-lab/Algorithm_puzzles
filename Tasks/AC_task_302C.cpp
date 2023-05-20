#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

bool SingleDiff(const std::string& lhs, const std::string& rhs) {
  int count = 0;
  for (int i = 0; i < lhs.size(); ++i) {
    count += (lhs[i] != rhs[i]);
  }
  return count == 1;
}

void DFS(const Graph& g, size_t i, std::vector<int8_t>& lookup) {
  if (lookup[i]) return;
  lookup[i] = 1;
  for (size_t next : g[i]) {
    DFS(g, next, lookup);
  }
}

bool DFSCheck(const Graph& g, size_t start) {
  std::vector<int8_t> lookup(g.size());

  DFS(g, start, lookup);

  return std::find(lookup.begin(), lookup.end(), 0) == lookup.end();
}

void Solution(std::istream& input) {
  int n, m;
  input >> n >> m;
  std::vector<std::string> data(n);
  for (auto& el : data) {
    input >> el;
  }

  Graph g(n);
  for (int i = 0; i < data.size(); ++i) {
    for (int j = i + 1; j < data.size(); ++j) {
      if (SingleDiff(data[i], data[j])) {
        g[i].push_back(j);
        g[j].push_back(i);
      }
    }
  }

  for (size_t i = 0; i < g.size(); ++i) {
    if (DFSCheck(g, i)) {
      std::cout << "Yes\n";
      return;
    }
  }
  std::cout << "No\n";
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
