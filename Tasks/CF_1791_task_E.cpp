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

void SolveOne(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::vector<int> dp(data.size());
  dp[0] = data[0];
  dp[1] = std::max(data[0] + data[1], -data[0] - data[1]);
  for (int i = 2; i < data.size(); ++i) {
    dp[i] = std::max(dp[i - 1] + data[i], dp[i - 2] - data[i - 1] - data[i]);
  }
  std::cout << dp.back() << '\n';
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
