#include <algorithm>
#include <vector>

int GetMinInRotated(const std::vector<int>& nums, int l, int r) {
  while (r - l > 1) {
    int m = (r + l) / 2;
    if (nums[m] <= nums[r]) {
      r = m;
    } else {
      l = m;
    }
  }
  return std::min(nums[l], nums[r]);
}

class Solution {
 public:
  int findMin(std::vector<int>& nums) {
    int r = nums.size() - 1;
    int l = 0;
    while (l < r && nums[r] == nums[l]) {
      ++l;
    }
    if (nums[l] > nums[r]) {
      return GetMinInRotated(nums, l, r);
    }
    return nums[l];
  }
};
