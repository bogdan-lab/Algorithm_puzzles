#include <algorithm>
#include <limits>
#include <vector>

class Solution {
 public:
  int maximumGap(std::vector<int>& nums) {
    if (nums.size() < 2) return 0;
    if (nums.size() == 2)
      return nums[0] < nums[1] ? nums[1] - nums[0] : nums[0] - nums[1];
    int min_val = *std::min_element(nums.begin(), nums.end());
    int max_val = *std::max_element(nums.begin(), nums.end());
    if (min_val == max_val) return 0;
    int gap = (max_val - min_val + nums.size() - 2) / (nums.size() - 1);
    std::vector<int> bucket_min(nums.size(), std::numeric_limits<int>::max());
    std::vector<int> bucket_max(nums.size(), std::numeric_limits<int>::min());

    for (const auto& el : nums) {
      int i = (el - min_val) / gap;
      bucket_min[i] = std::min(bucket_min[i], el);
      bucket_max[i] = std::max(bucket_max[i], el);
    }

    int max_gap = std::numeric_limits<int>::min();
    int prev_max = min_val;
    for (int i = 0; i < bucket_min.size(); ++i) {
      if (bucket_max[i] == std::numeric_limits<int>::min()) continue;
      max_gap = std::max(
          {max_gap, bucket_max[i] - bucket_min[i], bucket_min[i] - prev_max});
      prev_max = bucket_max[i];
    }
    if (!bucket_max.back() == std::numeric_limits<int>::min()) {
      max_gap = std::max({max_gap, bucket_min.back() - prev_max,
                          bucket_max.back() - bucket_min.back()});
    }
    return max_gap;
  }
};
