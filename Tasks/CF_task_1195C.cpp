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

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> top(n);
  for (auto& el : top) {
    input >> el;
  }
  std::vector<int> bot(n);
  for (auto& el : bot) {
    input >> el;
  }

  std::vector<std::vector<int64_t>> dp(2, std::vector<int64_t>(n));
  dp[0].back() = top.back();
  dp[1].back() = bot.back();
  for (int i = n - 2; i >= 0; --i) {
    dp[0][i] = std::max(dp[1][i + 1] + top[i], dp[0][i + 1]);
    dp[1][i] = std::max(dp[0][i + 1] + bot[i], dp[1][i + 1]);
  }
  std::cout << std::max(dp[0].front(), dp[1].front()) << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
