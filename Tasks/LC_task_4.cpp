#include <algorithm>
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
    // empty cases
    if (nums1.empty()) {
      return GetMedianForOne(nums2, nums2.size() / 2, !(nums2.size() % 2));
    }
    if (nums2.empty()) {
      return GetMedianForOne(nums1, nums1.size() / 2, !(nums1.size() % 2));
    }
    size_t mid_idx = (nums1.size() + nums2.size()) / 2;

    auto lhs_begin = nums1.begin();
    auto lhs_end = nums1.end();
    auto rhs_begin = nums2.begin();
    auto rhs_end = nums2.end();

    while (true) {
      if (lhs_begin == lhs_end) {
        // do something ...
      }
      int lhs_mid_val = *(lhs_begin + (lhs_end - lhs_begin) / 2);
      auto [lhs_range_begin, lhs_range_end] =
          std::equal_range(lhs_begin, lhs_end, lhs_mid_val);
      auto [rhs_range_begin, rhs_range_end] =
          std::equal_range(rhs_begin, rhs_end, lhs_mid_val);
      size_t lhs_mid_glob_idx_b = lhs_range_begin - lhs_begin;
      size_t lhs_mid_glob_idx_e =
          (lhs_range_end - lhs_begin) + rhs_range_end - rhs_begin;

      // 0 1 2 3 4
      // 1 1 1 3 4  -> lhs_begin_idx = 0
      // 2 2 2 2 5  -> lhs_end_idx = 3 + 4 - 1 = 6

      if (mid_idx >= lhs_mid_glob_idx_b && mid_idx < lhs_mid_glob_idx_e) {
        // what if mid_idx is first val and we have odd length ???
      }
      // Looking for the second value
      // range check above guarantee that if we are here we will not have
      // situation where both equal_range ends are range ends
      int rhs_mid_val = [&]() {
        if (lhs_range_end == lhs_end) {
          return *rhs_range_end;
        } else if (rhs_range_end == rhs_end) {
          return *lhs_range_end;
        } else {
          return std::min(*lhs_range_end, *rhs_range_end);
        }
      }();

      auto [lhs_range_begin_2, lhs_range_end_2] =
          std::equal_range(lhs_begin, lhs_end, rhs_mid_val);
      auto [rhs_range_begin_2, rhs_range_end_2] =
          std::equal_range(rhs_begin, rhs_end, rhs_mid_val);

      size_t rhs_mid_glob_idx_b = lhs_range_begin_2 - lhs_begin;
      size_t rhs_mid_glob_idx_e =
          (lhs_range_end_2 - lhs_begin) + rhs_range_end_2 - rhs_begin;

      if (mid_idx >= rhs_mid_glob_idx_b && mid_idx < rhs_mid_glob_idx_e) {
        // what if mid_idx is first val and we have odd length ???
        // what if in second ???
      }
      // Here we have two ranges and we checked if our mid point is in one of
      // them updating search range
      if (mid_idx >= rhs_mid_glob_idx_e) {
        // shift left edge
      } else {
        // shift right edge
      }
    }

    return std::numeric_limits<double>::quiet_NaN();
  }
};

int main() {
  std::vector<int> nums1{1, 2, 3, 4, 5};
  std::vector<int> nums2{1, 2, 3, 4, 5};
  Solution s;

  double res = s.findMedianSortedArrays(nums1, nums2);

  return 0;
}
