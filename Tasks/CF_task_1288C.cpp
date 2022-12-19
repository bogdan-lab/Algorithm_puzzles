#include <iostream>
#include <sstream>
#include <vector>

constexpr int kMod = 1'000'000'000 + 7;

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
  int n, m;
  input >> n >> m;
  std::vector<std::vector<int>> dp(n + 2 * m, std::vector<int>(2 * m + 1));
  for (int i = 0; i < dp.size(); ++i) {
    dp[i][0] = 1;
  }
  for (int i = 1; i < dp.size(); ++i) {
    for (int j = 1; j < dp[i].size(); ++j) {
      dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
      dp[i][j] %= kMod;
    }
  }
  std::cout << dp.back().back() << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2 2
)";
    Solution(ss);
    std::cout << "expected = 5\n";
  }
  {
    std::stringstream ss;
    ss << R"(10 1
)";
    Solution(ss);
    std::cout << "expected = 55\n";
  }
  {
    std::stringstream ss;
    ss << R"(723 9
)";
    Solution(ss);
    std::cout << "expected =157557417\n";
  }
}
