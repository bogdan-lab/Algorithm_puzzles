#include <algorithm>
#include <vector>

class Solution {
 public:
  int maxProfit(std::vector<int>& prices) {
    if (prices.size() == 1) return 0;
    std::vector<int> prefix(prices.size());
    int min_p = prices.front();
    int max_val = 0;
    for (size_t i = 1; i < prices.size(); ++i) {
      max_val = std::max(max_val, prices[i] - min_p);
      min_p = std::min(min_p, prices[i]);
      prefix[i] = max_val;
    }

    std::vector<int> suffix(prices.size());
    int max_p = prices.back();
    max_val = 0;
    for (int i = prices.size() - 2; i >= 0; --i) {
      max_val = std::max(max_val, max_p - prices[i]);
      max_p = std::max(max_p, prices[i]);
      suffix[i] = max_val;
    }

    // Case where we do only 1 the most optimal trade or do not do any trade at
    // all.
    int res = prefix.back();
    for (int i = 1; i < prefix.size() - 1; ++i) {
      res = std::max(res, prefix[i] + suffix[i + 1]);
    }
    return res;
  }
};
