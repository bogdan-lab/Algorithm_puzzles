#include <algorithm>
#include <vector>

int EMPTY_VALUE = 1000'001;

struct StepResult {
  int lhs_value = EMPTY_VALUE;
  int rhs_value = EMPTY_VALUE;
  size_t nums_before;
};

class Solution {
 public:
  StepResult GetNumBefore(const std::vector<int>& lhs, size_t l_s, size_t l_e,
                          const std::vector<int>& rhs, size_t r_s, size_t r_e) {
    int lhs_mid = lhs[(l_e + l_s) / 2];
    auto rhs_it =
        std::upper_bound(rhs.begin() + r_s, rhs.begin() + r_e, lhs_mid);
    StepResult res;
    res.nums_before = (l_e + l_s) / 2 + 1 + (rhs_it - rhs.begin() + r_s);
    res.lhs_value = lhs_mid;
    res.rhs_value = rhs_it == rhs.end() ? EMPTY_VALUE : *rhs_it;
    return res;
  }

  double GetMedianForOne(const std::vector<int>& vec, size_t pos,
                         bool double_val) {
    return double_val ? 0.5 * (vec[pos] + vec[pos + 1]) : vec[pos];
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

    size_t full_size = nums1.size() + nums2.size();
    size_t m_idx = full_size / 2;
    size_t l_s = 0;
    size_t l_e = nums1.size();
    size_t r_s = 0;
    size_t r_e = nums2.size();
    while (true) {
      StepResult res = GetNumBefore(nums1, l_s, l_e, nums2, r_s, r_e);

      if (m_idx == res.nums_before) {
        return full_size % 2 ? 1.0 * (res.lhs_value + res.rhs_value) / 2
                             : 1.0 * res.lhs_value;
      } else if (res.nums_before < m_idx) {
        l_s = (l_s + l_e) / 2 + 1;
        if (l_s >= l_e) {
          return GetMedianForOne(nums2, m_idx - res.nums_before,
                                 !(full_size % 2));
        }
        r_s = res.nums_before - l_s;
        if (r_s >= r_e) {
          return GetMedianForOne(nums1, m_idx - res.nums_before,
                                 !(full_size % 2));
        }
      } else {
        l_e = (l_s + l_e) / 2 + 1;
        if (l_s >= l_e) {
          return GetMedianForOne(nums2, m_idx - res.nums_before,
                                 !(full_size % 2));
        }
        r_e = res.nums_before - l_e;
        if (r_s >= r_e) {
          return GetMedianForOne(nums1, m_idx - res.nums_before,
                                 !(full_size % 2));
        }
      }
    }

    return 3.0;
  }
};
