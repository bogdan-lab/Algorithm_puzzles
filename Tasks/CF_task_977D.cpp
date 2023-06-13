#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

using Graph = std::vector<std::vector<size_t>>;
constexpr uint64_t kMidRange = std::numeric_limits<uint64_t>::max() / 2;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void PrintAnswer(const std::vector<uint64_t>& ans) {
  for (const auto& el : ans) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

bool CanMove(uint64_t from, uint64_t to) {
  if ((from % 3) == 0 && from / 3 == to) {
    return true;
  }
  if (from <= kMidRange && 2 * from == to) {
    return true;
  }
  return false;
}

Graph BuildGraph(const std::vector<uint64_t>& data) {
  Graph res(data.size());
  for (size_t i = 0; i < data.size(); ++i) {
    for (size_t j = 0; j < data.size(); ++j) {
      if (CanMove(data[i], data[j])) {
        res[i].push_back(j);
      }
    }
  }
  return res;
}

std::vector<uint64_t> ConstructNewOrder(const std::vector<uint64_t>& data,
                                        const std::vector<size_t>& order) {
  std::vector<uint64_t> res(data.size());
  for (size_t i = 0; i < res.size(); ++i) {
    res[i] = data[order[i]];
  }
  return res;
}

void DFS(const Graph& g, size_t i, std::vector<uint8_t>& lookup,
         std::vector<size_t>& order) {
  if (lookup[i]) return;
  lookup[i] = 1;
  for (const auto& n : g[i]) {
    DFS(g, n, lookup, order);
  }
  order.push_back(i);
}

std::vector<uint64_t> ReorderElements(const Graph& g,
                                      const std::vector<uint64_t>& data) {
  std::vector<uint8_t> lookup(data.size());
  std::vector<size_t> order;
  order.reserve(data.size());

  for (size_t i = 0; i < g.size(); ++i) {
    DFS(g, i, lookup, order);
  }

  std::reverse(order.begin(), order.end());
  return ConstructNewOrder(data, order);
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<uint64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }

  Graph g = BuildGraph(data);
  std::vector<uint64_t> ans = ReorderElements(g, data);
  PrintAnswer(ans);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
4 8 6 3 12 9
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
