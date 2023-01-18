#include <algorithm>
#include <queue>
#include <vector>

class Solution {
 public:
  std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
    std::vector<int> res;
    res.reserve(nums.size() - k + 1);

    std::priority_queue<std::pair<int, int>> data;
    for (int i = 0; i < k; ++i) {
      data.push({nums[i], i});
    }
    res.push_back(data.top().first);
    for (int i = k; i < nums.size(); ++i) {
      while (!data.empty() && data.top().second <= i - k) {
        data.pop();
      }
      data.push({nums[i], i});
      res.push_back(data.top().first);
    }

    return res;
  }
};
