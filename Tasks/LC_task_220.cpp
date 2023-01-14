#include <algorithm>
#include <cassert>
#include <limits>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  bool containsNearbyAlmostDuplicate(std::vector<int>& nums, int indexDiff,
                                     int valueDiff) {
    std::unordered_map<int, int> count;
    for (int i = 0; i < nums.size(); ++i) {
      int lvl = nums[i] / (valueDiff + 1);
      if (nums[i] < 0) --lvl;
      auto it = count.find(lvl);
      if (it != count.end()) return true;
      count[lvl] = nums[i];

      it = count.find(lvl - 1);
      if (it != count.end() && std::abs(it->second - nums[i]) <= valueDiff)
        return true;

      it = count.find(lvl + 1);
      if (it != count.end() && std::abs(it->second - nums[i]) <= valueDiff)
        return true;

      if (count.size() > indexDiff) {
        int prev = i - indexDiff;
        int prev_lvl = nums[prev] / (valueDiff + 1);
        if (nums[prev] < 0) --prev_lvl;
        count.erase(prev_lvl);
      }
    }

    return false;
  }
};
