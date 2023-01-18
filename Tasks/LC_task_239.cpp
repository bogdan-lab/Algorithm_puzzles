#include <algorithm>
#include <set>
#include <vector>

class Solution {
 public:
  std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
    std::vector<int> res;
    res.reserve(nums.size() - k + 1);

    std::set<std::pair<int, int>> data;
    for (int i = 0; i < k; ++i) {
      data.insert({nums[i], i});
    }
    res.push_back(std::prev(data.end())->first);
    for (int i = k; i < nums.size(); ++i) {
      data.erase({nums[i - k], i - k});
      data.insert({nums[i], i});
      res.push_back(std::prev(data.end())->first);
    }

    return res;
  }
};
