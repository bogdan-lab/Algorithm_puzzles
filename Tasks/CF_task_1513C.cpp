#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

constexpr int kMod = 1'000'000'000 + 7;
constexpr int kMaxM = 2 * 100'000;

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
  // building dp
  std::vector<int> dp(kMaxM + 1 + 10);
  for (int i = 0; i < 10; ++i) {
    dp[i] = 1;
  }
  for (int i = 10; i < 19; ++i) {
    dp[i] = 2;
  }
  dp[19] = 3;

  for (int i = 20; i < dp.size(); ++i) {
    dp[i] = dp[i - 9] + dp[i - 10];
    dp[i] %= kMod;
  }

  while (n--) {
    int val, m;
    input >> val >> m;

    int res = 0;
    while (val) {
      int residual = val % 10;
      val -= residual;
      val /= 10;
      res += dp[residual + m];
      res %= kMod;
    }
    std::cout << res << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
1912 1
5 6
999 1
88 2
12 100
)";
    Solution(ss);
    std::cout << "expected = 5; 2; 6; 4; 2115\n";
  }
}
