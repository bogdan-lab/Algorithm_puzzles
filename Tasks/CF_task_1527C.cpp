#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <utility>
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

int64_t CalcWeight(const std::vector<int>& data) {
  std::vector<int64_t> dp(data.size());
  std::unordered_map<int64_t, int64_t> count;
  int64_t res = 0;
  for (size_t i = 0; i < data.size(); ++i) {
    if (i > 0) {
      dp[i] = dp[i - 1];
    }

    auto it = count.find(data[i]);
    if (it != count.end()) {
      dp[i] += it->second;
      it->second += i + 1;
    } else {
      count.insert({data[i], i + 1});
    }
    res += dp[i];
  }
  return res;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n;
    input >> n;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }
    std::cout << CalcWeight(data) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2
4
1 2 1 1
4
1 2 3 4
)";
    Solution(ss);
    std::cout << "expected = 6; 0\n";
  }
}
