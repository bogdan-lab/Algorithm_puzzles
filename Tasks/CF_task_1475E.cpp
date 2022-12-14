#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

constexpr int kMod = 1'000'000'007;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

int GetNumber(std::vector<int>& data, int chose_num) {
  std::sort(data.begin(), data.end());
  int index = data.size() - chose_num;
  int eq_val = data[index];
  int64_t n = std::count(data.begin(), data.end(), eq_val);
  int64_t k = std::count(data.begin() + index, data.end(), eq_val);

  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1));
  for (int i = 0; i < dp.size(); ++i) {
    dp[i][0] = 1;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= k; ++j) {
      dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % kMod;
    }
  }
  return dp[n][k];
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n, k;
    input >> n >> k;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }
    std::cout << GetNumber(data, k) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
4 3
1 3 1 2
4 2
1 1 1 1
2 1
1 2
)";
    Solution(ss);
    std::cout << "expected = 2; 6; 1\n";
  }
}
