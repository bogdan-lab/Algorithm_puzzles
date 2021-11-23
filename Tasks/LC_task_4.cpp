#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

class Solution {
 public:
  double GetMedianForOne(const std::vector<int>& vec, size_t pos,
                         bool double_val) {
    return double_val ? 0.5 * (vec[pos] + vec[pos - 1]) : vec[pos];
  }

  double findMedianSortedArrays(std::vector<int>& nums1,
                                std::vector<int>& nums2) {
    const size_t full_size = nums1.size() + nums2.size();
    const size_t mid_idx = full_size / 2;
    const bool need_calc_avg = !(full_size % 2);
    auto lhs_begin = nums1.begin();
    auto lhs_end = nums1.end();
    auto rhs_begin = nums2.begin();
    auto rhs_end = nums2.end();

    while (true) {
      // Checck it in the end
      if (lhs_begin == lhs_end) {
        size_t pos = mid_idx - (lhs_begin - nums1.begin());
        if (pos > 0) {
          return GetMedianForOne(nums2, pos, need_calc_avg);
        } else {
          return need_calc_avg ? 0.5 * (nums2[0] + *std::prev(lhs_begin))
                               : nums2[0];
        }
      }
      if (rhs_begin == rhs_end) {
        size_t pos = mid_idx - (rhs_begin - nums2.begin());
        if (pos > 0) {
          return GetMedianForOne(nums1, pos, need_calc_avg);
        } else {
          return need_calc_avg ? 0.5 * (nums1[0] + *std::prev(rhs_begin))
                               : nums1[0];
        }
      }
      int lhs_mid_val = *(lhs_begin + (lhs_end - lhs_begin) / 2);
      auto lhs_range_begin_1 =
          std::lower_bound(lhs_begin, lhs_end, lhs_mid_val);
      auto lhs_range_end_1 = std::upper_bound(lhs_begin, lhs_end, lhs_mid_val);
      auto rhs_range_begin_1 =
          std::lower_bound(rhs_begin, rhs_end, lhs_mid_val);
      auto rhs_range_end_1 = std::upper_bound(rhs_begin, rhs_end, lhs_mid_val);
      size_t lhs_mid_glob_idx_b =
          (lhs_range_begin_1 - lhs_begin) + (rhs_range_begin_1 - rhs_begin);
      size_t lhs_mid_glob_idx_e =
          (lhs_range_end_1 - lhs_begin) + (rhs_range_end_1 - rhs_begin);

      if (mid_idx >= lhs_mid_glob_idx_b && mid_idx < lhs_mid_glob_idx_e) {
        if (need_calc_avg && mid_idx == lhs_mid_glob_idx_b) {
          int prev_value = [&]() {
            if (lhs_range_begin_1 == nums1.begin()) {
              return *std::prev(rhs_range_begin_1);
            }
            if (rhs_range_begin_1 == nums2.begin()) {
              return *std::prev(lhs_range_begin_1);
            }
            return std::max(*std::prev(lhs_range_begin_1),
                            *std::prev(rhs_range_begin_1));
          }();
          return 0.5 * (lhs_mid_val + prev_value);
        } else {
          return lhs_mid_val;
        }
      }
      if (lhs_range_end_1 == lhs_end && rhs_range_end_1 == rhs_end) {
        lhs_end = lhs_range_begin_1;
        rhs_end = rhs_range_begin_1;
        continue;
      }
      // Searching for the second value
      int rhs_mid_val = [&]() {
        if (lhs_range_end_1 == lhs_end) {
          return *rhs_range_end_1;
        }
        if (rhs_range_end_1 == rhs_end) {
          return *lhs_range_end_1;
        }
        return std::min(*lhs_range_end_1, *rhs_range_end_1);
      }();

      auto lhs_range_begin_2 =
          std::lower_bound(lhs_begin, lhs_end, rhs_mid_val);
      auto lhs_range_end_2 = std::upper_bound(lhs_begin, lhs_end, rhs_mid_val);
      auto rhs_range_begin_2 =
          std::lower_bound(rhs_begin, rhs_end, rhs_mid_val);
      auto rhs_range_end_2 = std::upper_bound(rhs_begin, rhs_end, rhs_mid_val);
      size_t rhs_mid_glob_idx_b =
          (lhs_range_begin_2 - lhs_begin) + (rhs_range_begin_2 - rhs_begin);
      size_t rhs_mid_glob_idx_e =
          (lhs_range_end_2 - lhs_begin) + rhs_range_end_2 - rhs_begin;

      if (mid_idx >= rhs_mid_glob_idx_b && mid_idx < rhs_mid_glob_idx_e) {
        return need_calc_avg && mid_idx == rhs_mid_glob_idx_b
                   ? 0.5 * (lhs_mid_val + rhs_mid_val)
                   : rhs_mid_val;
      }

      // Here we have two ranges and we checked if our mid point is in one of
      // them updating search range
      if (mid_idx >= rhs_mid_glob_idx_e) {
        lhs_begin = lhs_range_end_2;
        rhs_begin = rhs_range_end_2;
      } else {
        lhs_end = lhs_range_begin_1;
        rhs_end = rhs_range_begin_1;
      }
    }
  }
};

int main() {
  {  // General case
    std::vector<int> nums1{1, 2, 3, 4, 5};
    std::vector<int> nums2{1, 2, 3, 4, 5};
    Solution s;
    double res = s.findMedianSortedArrays(nums1, nums2);
    std::cout << res << " expected 3\n";
  }
  {
    std::vector<int> nums1{1};
    std::vector<int> nums2;
    Solution s;
    double res = s.findMedianSortedArrays(nums1, nums2);
    std::cout << res << " expected 1\n";
  }
  {
    std::vector<int> nums1;
    std::vector<int> nums2{1};
    Solution s;
    double res = s.findMedianSortedArrays(nums1, nums2);
    std::cout << res << " expected 1\n";
  }
  {
    std::vector<int> nums1{1, 3};
    std::vector<int> nums2{2};
    Solution s;
    double res = s.findMedianSortedArrays(nums1, nums2);
    std::cout << res << " expected 2\n";
  }
  {
    std::vector<int> nums1{5, 5};
    std::vector<int> nums2{5, 5};
    Solution s;
    double res = s.findMedianSortedArrays(nums1, nums2);
    std::cout << res << " expected 5\n";
  }
  {
    std::vector<int> nums1{1, 3};
    std::vector<int> nums2{2, 7};
    Solution s;
    double res = s.findMedianSortedArrays(nums1, nums2);
    std::cout << res << " expected 2.5\n";
  }
  {
    std::vector<int> nums1{1, 2, 3};
    std::vector<int> nums2{4, 5, 6};
    Solution s;
    double res = s.findMedianSortedArrays(nums1, nums2);
    std::cout << res << " expected 3.5\n";
  }
  {
    std::vector<int> nums1{1, 2, 5};
    std::vector<int> nums2{3, 4, 6};
    Solution s;
    double res = s.findMedianSortedArrays(nums1, nums2);
    std::cout << res << " expected 3.5\n";
  }
  return 0;
}
