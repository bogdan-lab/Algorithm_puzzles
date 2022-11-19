#include <algorithm>
#include <vector>

class Solution {
 public:
  int maxProfit(std::vector<int>& prices) {
    if (prices.size() == 1) return 0;
    std::vector<int> data(prices.size());
    int min_p = prices.front();
    int max_val = 0;
    for (size_t i = 1; i < prices.size(); ++i) {
      max_val = std::max(max_val, prices[i] - min_p);
      min_p = std::min(min_p, prices[i]);
      data[i] = max_val;
    }
    // Here data[i] stores income on range [0, i]
    int max_p = prices.back();
    max_val = 0;
    int res = 0;
    for (int i = prices.size() - 2; i >= 0; --i) {
      res = std::max(res, data[i + 1] + max_val);
      max_val = std::max(max_val, max_p - prices[i]);
      max_p = std::max(max_p, prices[i]);
    }
    res = std::max(res, data[0] + max_val);
    return res;
  }
};
