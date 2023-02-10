#include <iostream>
#include <sstream>
#include <vector>

constexpr uint64_t kMod = 1'000'000'000 + 7;

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
  int n, k;
  input >> n >> k;

  std::vector<std::vector<uint64_t>> dp(n + 1, std::vector<uint64_t>(k + 1));
  for (int i = 1; i <= n; ++i) {
    dp[i][1] = 1;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
      for (int len = 1; len < k; ++len) {
        dp[j][len + 1] += dp[i][len];
        dp[j][len + 1] %= kMod;
      }
    }
  }

  uint64_t count = 0;
  for (int i = 1; i <= n; ++i) {
    count += dp[i].back();
    count %= kMod;
  }
  std::cout << count << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
