#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

int64_t GetCount(const std::vector<int>& data);

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

int64_t GetCount(const std::vector<int>& data) {
  int64_t count = 0;
  std::vector<int64_t> dp(data.size());
  for (int i = 1; i < data.size(); ++i) {
    for (int j = 0; j < i - 1; ++j) {
      // add precise
      dp[i] += (data[j] + j >= i);
    }
    // add overflow
    dp[i] += std::max<int64_t>(dp[i - 1] - data[i - 1] + 1, 0);
  }
  for (int i = 0; i < data.size(); ++i) {
    count += std::max<int64_t>(data[i] - 1 - dp[i], 0);
  }
  return count;
}

void Solution(std::istream& input) {
  int t;
  input >> t;

  while (t--) {
    size_t n;
    input >> n;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }

    std::cout << GetCount(data) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
7
1 4 2 2 2 2 2
2
2 3
5
1 1 1 1 1
4
1 9 2 1
1
6
)";
    Solution(ss);
    std::cout << "expected = 4; 3; 0; 9; 5\n";
  }
}
