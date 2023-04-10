#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

using Number = std::vector<int>;

bool IsLess(const std::vector<int>& lhs, const std::vector<int>& rhs) {
  assert(lhs.size() == rhs.size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    if (lhs[i] < rhs[i]) {
      return true;
    } else if (lhs[i] > rhs[i]) {
      return false;
    }
  }
  return false;
}

Number Create(int prefix, const Number& suffix) {
  Number res;
  res.reserve(suffix.size() + 1);
  res.push_back(prefix);
  std::copy(suffix.begin(), suffix.end(), std::back_inserter(res));
  return res;
}

void Print(const Number& data) {
  for (const auto& el : data) {
    std::cout << el << ',';
  }
  std::cout << std::endl;
}

Number BuildMaxNumber(const Number& data, size_t k) {
  // dp[suffix][num_size] = max number
  std::vector<std::vector<Number>> dp(data.size() + 1,
                                      std::vector<Number>(k + 1, Number{}));
  dp[1][1] = {data.back()};
  for (size_t ss = 2; ss <= data.size(); ++ss) {
    dp[ss][1] = {std::max(data[data.size() - ss], dp[ss - 1][1][0])};
  }

  for (size_t ss = 2; ss <= data.size(); ++ss) {
    for (size_t ns = 2; ns <= std::min(ss, k); ++ns) {
      Number current = Create(data[data.size() - ss], dp[ss - 1][ns - 1]);
      if (ns < ss && IsLess(current, dp[ss - 1][ns])) {
        dp[ss][ns] = dp[ss - 1][ns];
      } else {
        dp[ss][ns] = current;
      }
      Print(dp[ss][ns]);
    }
  }
  return dp.back().back();
}

class Solution {
 public:
  std::vector<int> maxNumber(Number& left, Number& right, int k) {
    Number best_left = BuildMaxNumber(left, std::min<size_t>(left.size(), k));
    return best_left;
  }
};

int main() {
  Solution s;
  Number left = {7, 3, 4, 6, 5};
  Number right = {};
  s.maxNumber(left, right, 3);
  return 0;
}