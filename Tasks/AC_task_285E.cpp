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
  std::vector<int64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }
  if (data.size() == 1) {
    std::cout << 0 << '\n';
    return;
  }

  std::vector<int64_t> sums(n);
  int index = 1;
  int dbi = 0;
  while (index < sums.size()) {
    sums[index] = sums[index - 1] + data[dbi];
    ++index;
    if (index == sums.size()) break;
    sums[index] = sums[index - 1] + data[dbi];
    ++index;
    ++dbi;
  }

  std::vector<int64_t> dp(n + 1);
  // dp[i] maximum cost we can get using knapsack with size i
  for (int i = 1; i < dp.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      // sums[j] is the cost of chunk with size j-1
      dp[i] = std::max(dp[i], dp[i - j - 1] + sums[j]);
    }
  }

  std::cout << dp.back() << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(7
10 10 1 1 1 1 1
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
