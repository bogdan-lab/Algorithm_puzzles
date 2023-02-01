#include <algorithm>
#include <vector>

int GetVal(const std::vector<int>& nums, int i) {
  if (i < 0 || i >= nums.size()) return 1;
  return nums[i];
}

int GetDP(const std::vector<std::vector<int>>& nums, int l, int r) {
  if (l > r) return 0;
  return nums[l][r];
}

int CalcMaxPoints(const std::vector<int>& nums, int start, int end,
                  const std::vector<std::vector<int>>& dp) {
  int res = 0;
  for (int k = start; k <= end; ++k) {
    int last_tick =
        GetVal(nums, start - 1) * GetVal(nums, k) * GetVal(nums, end + 1);
    res = std::max(res,
                   last_tick + GetDP(dp, start, k - 1) + GetDP(dp, k + 1, end));
  }
  return res;
}

class Solution {
 public:
  int maxCoins(std::vector<int>& nums) {
    // dp[start][end]
    std::vector<std::vector<int>> dp(nums.size(),
                                     std::vector<int>(nums.size()));

    for (int w = 0; w < nums.size(); ++w) {
      for (int start = 0; start + w < nums.size(); ++start) {
        int end = start + w;
        dp[start][end] = CalcMaxPoints(nums, start, end, dp);
      }
    }

    return dp[0][nums.size() - 1];
  }
};
