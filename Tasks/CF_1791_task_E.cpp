#include <algorithm>
#include <iostream>
#include <numeric>
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

void SolveOne(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  for (int i = 0; i < data.size() - 1; ++i) {
    if (data[i] < 0) {
      data[i] = -data[i];
      data[i + 1] = -data[i + 1];
    }
  }

  if (data.back() < 0) {
    auto it = std::min_element(data.begin(), data.end() - 1);
    if (*it < -data.back()) {
      *it = -(*it);
      data.back() = -data.back();
    }
  }

  int64_t res = 0;
  for (const auto& el : data) {
    res += el;
  }
  std::cout << res << '\n';
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
