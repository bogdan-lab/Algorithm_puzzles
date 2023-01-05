#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class Solution {
 public:
  int maxProfit(int k, std::vector<int>& prices) {
    int pn = prices.size();
    // profit[bought][start][k]
    std::vector<std::vector<std::vector<int>>> profit(
        2, std::vector<std::vector<int>>(pn, std::vector<int>(k + 1)));
    for (int i = 1; i <= k; ++i) {
      profit[0][pn - 1][i] = 0;
      profit[1][pn - 1][i] = prices.back();
    }

    for (int i = 1; i <= k; ++i) {
      for (int p = pn - 2; p >= 0; --p) {
        profit[1][p][i] =
            std::max(profit[1][p + 1][i], profit[0][p + 1][i - 1] + prices[p]);
        profit[0][p][i] =
            std::max(profit[0][p + 1][i], profit[1][p + 1][i] - prices[p]);
      }
    }

    return profit[0][0][k];
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
