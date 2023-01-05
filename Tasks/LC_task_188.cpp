#include <algorithm>
#include <cassert>
#include <vector>

constexpr int kEmpty = -1001;

int Solve(const std::vector<int>& prices, int pos, int k,
          std::vector<std::vector<std::vector<int>>>& profit,
          int bought) {  // profit[bought][k][pos]
  if (k <= 0 || pos >= prices.size()) return 0;
  if (profit[bought][k][pos] == kEmpty) {
    profit[bought][k][pos] = Solve(prices, pos + 1, k, profit, bought);
    if (bought) {
      profit[bought][k][pos] =
          std::max(profit[bought][k][pos],
                   Solve(prices, pos + 1, k - 1, profit, 0) + prices[pos]);
    } else {
      profit[bought][k][pos] =
          std::max(profit[bought][k][pos],
                   Solve(prices, pos + 1, k, profit, 1) - prices[pos]);
    }
  }
  return profit[bought][k][pos];
}

class Solution {
 public:
  int maxProfit(int k, std::vector<int>& prices) {
    std::vector<std::vector<std::vector<int>>> profit(
        2, std::vector<std::vector<int>>(
               k + 1, std::vector<int>(prices.size(), kEmpty)));
    return Solve(prices, 0, k, profit, 0);
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
