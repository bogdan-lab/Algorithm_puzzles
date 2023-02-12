#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <vector>

constexpr int kMin = std::numeric_limits<int>::min();
constexpr int kMax = std::numeric_limits<int>::max();

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Update(std::pair<int, int>& p, int val) {
  p.first = std::max(p.first, val);
  p.second = std::min(p.second, val);
}

std::queue<std::pair<int, int>> BuildQueue(const std::vector<int>& w) {
  std::queue<std::pair<int, int>> res;
  for (int i = 0; i < w.size(); ++i) {
    res.push({w[i], i});
  }
  return res;
}

int64_t CountSum(const std::vector<std::pair<int, int>>& data) {
  int64_t res = 0;
  for (const auto& el : data) {
    res += el.first + el.second;
  }
  return res;
}

void SolveOne(std::istream& input) {
  int n, k;
  input >> n >> k;
  std::vector<int> num(n);
  for (auto& el : num) {
    input >> el;
  }
  std::vector<int> w(k);
  for (auto& el : w) {
    input >> el;
  }

  std::sort(num.begin(), num.end(), std::greater<int>());
  std::sort(w.begin(), w.end());
  std::queue<std::pair<int, int>> buff = BuildQueue(w);
  std::vector<std::pair<int, int>> data(k, std::make_pair(kMin, kMax));

  for (const auto& el : num) {
    std::pair<int, int> top = buff.front();
    buff.pop();
    Update(data[top.second], el);
    --top.first;
    if (top.first) {
      buff.push(top);
    }
  }

  std::cout << CountSum(data) << '\n';
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
