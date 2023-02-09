#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

std::vector<std::vector<int>> BuildParentGraph(const std::vector<int>& data) {
  std::vector<std::vector<int>> graph(data.size());
  for (int i = 0; i < data.size(); ++i) {
    int div = i + 1;
    for (int j = i + div; j < data.size(); j += div) {
      if (data[i] < data[j]) {
        graph[j].push_back(i);
      }
    }
  }
  return graph;
}

std::vector<int> GetCount(const std::vector<std::vector<int>>& pg) {
  std::vector<int> count(pg.size(), 1);

  for (int i = pg.size() - 1; i >= 0; --i) {
    for (const auto& pid : pg[i]) {
      count[pid] = std::max(count[pid], count[i] + 1);
    }
  }

  return count;
}

void SolveOne(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::vector<std::vector<int>> graph = BuildParentGraph(data);
  std::vector<int> count = GetCount(graph);
  std::cout << *std::max_element(count.begin(), count.end()) << '\n';
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
4
5 3 4 6
7
1 4 2 3 6 4 9
5
5 4 3 2 1
1
9
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
