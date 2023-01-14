#include <algorithm>
#include <cassert>
#include <limits>
#include <unordered_set>
#include <vector>

bool Check(const std::vector<int>& levels, int w_size) {
  std::unordered_set<int> count;
  for (int i = 0; i < w_size; ++i) {
    auto it = count.insert(levels[i]);
    if (!it.second) return true;
  }

  for (int i = count.size(); i < levels.size(); ++i) {
    int prev_lvl = levels[i - w_size];
    count.erase(prev_lvl);
    auto it = count.insert(levels[i]);
    if (!it.second) return true;
  }
  return false;
}

class Solution {
 public:
  bool containsNearbyAlmostDuplicate(std::vector<int>& nums, int indexDiff,
                                     int valueDiff) {
    assert(!nums.empty());
    int min_val = *std::min_element(nums.begin(), nums.end());

    for (auto& el : nums) {
      el -= min_val;
    }

    std::vector<int> levels1(nums.size());
    std::vector<int> levels2(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
      levels1[i] = nums[i] / (valueDiff + 1);
      levels2[i] =
          (static_cast<int64_t>(nums[i]) + static_cast<int64_t>(valueDiff)) /
          static_cast<int64_t>(valueDiff + 1);
    }

    int w_size = std::min<int>(indexDiff + 1, nums.size());
    return Check(levels1, w_size) || Check(levels2, w_size);
  }
};
