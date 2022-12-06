#include <algorithm>
#include <vector>

int GetMinimum(const std::vector<int>& nums, int l, int r) {
  if (r - l <= 1) return std::min(nums[l], nums[r]);
  if (nums[l] < nums[r]) return nums[l];
  int m = (l + r) / 2;
  return std::min(GetMinimum(nums, l, m), GetMinimum(nums, m + 1, r));
}

class Solution {
 public:
  int findMin(std::vector<int>& nums) {
    return GetMinimum(nums, 0, nums.size() - 1);
  }
};
