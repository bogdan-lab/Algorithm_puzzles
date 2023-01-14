#include <algorithm>
#include <cassert>
#include <limits>
#include <unordered_set>
#include <vector>

bool Check(const std::vector<std::pair<int, int>>& levels, int w_size) {
  std::unordered_set<int> count;
  int i = 0;
  while (i < levels.size() && levels[i].first < w_size) {
    auto it = count.insert(levels[i].second);
    if (!it.second) return true;
    ++i;
  }

  int j = 0;
  while (i < levels.size()) {
    // remove tail
    while (levels[j].first <= levels[i].first - w_size) {
      count.erase(levels[j].second);
      ++j;
    }
    auto it = count.insert(levels[i].second);
    if (!it.second) return true;
    ++i;
  }
  return false;
}

std::vector<std::pair<int, int>> GetLevels(const std::vector<int>& nums,
                                           int diff) {
  std::vector<std::pair<int, int>> levels;
  levels.reserve(2 * nums.size());
  for (int i = 0; i < nums.size(); ++i) {
    if (diff == 0) {
      levels.push_back({i, nums[i]});
    } else {
      int val = nums[i] / diff;
      if (!(nums[i] % diff)) {
        levels.push_back({i, val - 1});
        levels.push_back({i, val});
      } else {
        levels.push_back({i, val});
      }
    }
  }
  return levels;
}

class Solution {
 public:
  bool containsNearbyAlmostDuplicate(std::vector<int>& nums, int indexDiff,
                                     int valueDiff) {
    assert(!nums.empty());
    int min_val = *std::min_element(nums.begin(), nums.end());

    if (valueDiff > 0) {
      int tmp = (std::abs(min_val) + valueDiff - 1) / valueDiff;
      min_val = tmp * valueDiff;
    }

    for (auto& el : nums) {
      el += min_val;
    }

    std::vector<std::pair<int, int>> levels = GetLevels(nums, valueDiff);
    return Check(levels, std::min<int>(indexDiff + 1, nums.size()));
  }
};
