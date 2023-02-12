#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <tuple>
#include <utility>
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

int CountManWithVal(const std::vector<std::pair<int, int>>& data, int val) {
  auto begin = std::lower_bound(
      data.begin(), data.end(), val,
      [](std::pair<int, int> p, int v) { return p.first < v; });
  auto end = std::upper_bound(
      data.begin(), data.end(), val,
      [](int v, std::pair<int, int> p) { return v < p.first; });
  return end - begin;
}

int CountGirlsWithVal(const std::vector<std::pair<int, int>>& data, int val) {
  auto begin = std::lower_bound(
      data.begin(), data.end(), val,
      [](std::pair<int, int> p, int v) { return p.second < v; });
  auto end = std::upper_bound(
      data.begin(), data.end(), val,
      [](int v, std::pair<int, int> p) { return v < p.second; });
  return end - begin;
}

void SolveOne(std::istream& input) {
  int a, b, k;
  input >> a >> b >> k;
  std::vector<int> man(k);
  for (auto& el : man) {
    input >> el;
  }
  std::vector<int> girls(k);
  for (auto& el : girls) {
    input >> el;
  }

  std::vector<std::pair<int, int>> first_man;
  first_man.reserve(man.size());
  for (int i = 0; i < k; ++i) {
    first_man.push_back({man[i], girls[i]});
  }
  auto first_girls = first_man;
  std::sort(first_man.begin(), first_man.end());
  std::sort(first_girls.begin(), first_girls.end(),
            [](std::pair<int, int> lhs, std::pair<int, int> rhs) {
              return std::tie(lhs.second, lhs.first) <
                     std::tie(rhs.second, rhs.first);
            });
  int64_t count = 0;
  for (const auto& el : first_man) {
    int m = CountManWithVal(first_man, el.first);
    int g = CountGirlsWithVal(first_girls, el.second);
    count += first_man.size() + 1 - m - g;
  }

  std::cout << count / 2 << '\n';
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
