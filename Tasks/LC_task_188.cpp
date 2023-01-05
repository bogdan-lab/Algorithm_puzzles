#include <algorithm>
#include <cassert>
#include <vector>

constexpr int kEmpty = -1001;

int Solve(const std::vector<int>& prices, int start, int k,
          std::vector<std::vector<int>>& profit) {
  if (k <= 0 || start >= prices.size() - 1) return 0;
  if (profit[start][k] == kEmpty) {
    for (int i = start + 1; i < prices.size(); ++i) {
      int curr_prof = prices[i] - prices[start];
      profit[start][k] = std::max(
          {profit[start][k], Solve(prices, i + 1, k - 1, profit) + curr_prof,
           Solve(prices, i, k, profit)});
    }
  }
  return profit[start][k];
}

class Solution {
 public:
  int maxProfit(int k, std::vector<int>& prices) {
    std::vector<std::vector<int>> profit(prices.size(),
                                         std::vector<int>(k + 1, kEmpty));

    int res = Solve(prices, 0, k, profit);

    return res;
  }
};

int main() {
  Solution s;
  {
    std::vector<int> prices{2, 4, 1};
    assert(s.maxProfit(2, prices) == 2);
  }
  {
    std::vector<int> prices{3, 2, 6, 5, 0, 3};
    assert(s.maxProfit(2, prices) == 7);
  }
  return 0;
}
