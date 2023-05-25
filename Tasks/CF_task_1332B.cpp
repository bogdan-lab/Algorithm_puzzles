#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

struct Answer {
  explicit Answer(size_t size) : colors(size), max_color(0) {}
  std::vector<int> colors;
  int max_color;
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

int GCD(int lhs, int rhs) {
  if (lhs > rhs) std::swap(lhs, rhs);
  while (lhs) {
    rhs %= lhs;
    std::swap(lhs, rhs);
  }
  return rhs;
}

Graph BuildGraph(const std::vector<int>& data) {
  Graph res(data.size());

  for (size_t i = 0; i < data.size(); ++i) {
    for (size_t j = i + 1; j < data.size(); ++j) {
      int gcd = GCD(data[i], data[j]);
      if (gcd > 1) {
        res[i].push_back(j);
        res[j].push_back(i);
      }
    }
  }
  return res;
}

void DFS(const Graph& g, int i, std::vector<int>& colors, int curr_color) {
  if (colors[i]) return;
  colors[i] = curr_color;
  for (int n : g[i]) {
    DFS(g, n, colors, curr_color);
  }
}

Answer GetColors(const Graph& g) {
  Answer res(g.size());
  for (int i = 0; i < g.size(); ++i) {
    if (res.colors[i]) continue;
    ++res.max_color;
    DFS(g, i, res.colors, res.max_color);
  }
  return res;
}

void PrintAnswer(const Answer& ans) {
  std::cout << ans.max_color << '\n';
  for (const auto& el : ans.colors) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

void SolveOne(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  Graph g = BuildGraph(data);
  Answer ans = GetColors(g);
  PrintAnswer(ans);
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
