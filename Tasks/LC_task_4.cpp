#include <algorithm>
#include <limits>
#include <vector>

struct StepResult {
  size_t lhs_idx = 0;
  size_t rhs_idx = 0;
};


struct StepResult2{
    size_t lhs_idx = 0;
    int lhs_value = 0;
    size_t rhs_idx = 0;
    int rhs_value = 0;

    size_t nums1_shift= 0;
    size_t nums2_shift= 0;
};

class Solution {
 public:

  StepResult2 GetNumBefore2(const std::vector<int>& lhs, size_t l_s, size_t l_e,
          const std::vector<int>& rhs, size_t r_s, size_t r_e) {
      StepResult2 res;
      if(l_s >= l_e){
        res.lhs_idx = (r_s + r_e)/2 + l_e;
        res.lhs_value = rhs[(r_s + r_e)/2];
        res.rhs_idx = res.lhs_idx == r_e - 1 ? res.lhs_idx - 1 : res.lhs_idx + 1;
        res.rhs_value = rhs[res.rhs_idx];
        if(res.rhs_idx < res.lhs_idx){
            std::swap(res.lhs_idx, res.rhs_idx);
            std::swap(res.lhs_value, res.rhs_value);
        }
        res.nums2_shift = res.rhs_idx;
        return res;
      }
      if(r_s >= r_e){
        res.lhs_idx = (l_s + l_e)/2 + r_e;
        res.lhs_value = lhs[(l_s + l_e)/2];
        res.rhs_idx = res.lhs_idx == l_e - 1 ? res.lhs_idx - 1 : res.lhs_idx + 1;
        res.rhs_value = lhs[res.rhs_idx];
        if(res.rhs_idx < res.lhs_idx){
            std::swap(res.lhs_idx, res.rhs_idx);
            std::swap(res.lhs_value, res.rhs_value);
        }
        res.nums1_shift = res.rhs_idx;
        return res;
      }
      // both vectors contain values
      res.lhs_value = lhs[(l_e + l_s)/2];
      auto rhs_begin = rhs.begin() + r_s;
      auto rhs_end = rhs.begin() + r_e;
      auto rhs_it = std::upper_bound(rhs_begin, rhs_end, res.lhs_value);
      // case when rhs_it is end
 


      return res;
  }


  StepResult GetNumBefore(const std::vector<int>& lhs, size_t l_s, size_t l_e,
                          const std::vector<int>& rhs, size_t r_s, size_t r_e) {
    int lhs_mid = lhs[(l_e + l_s) / 2];
    auto lhs_end = lhs.begin() + l_e;
    auto lhs_begin = lhs.begin() + l_s;
    auto lhs_it = std::upper_bound(lhs_begin, lhs_end, lhs_mid);
    if (lhs_it == lhs_end) {
      lhs_it = std::lower_bound(lhs_begin, lhs_end, lhs_mid);
    }
    // linear in case of range with the same value
    auto rhs_begin = rhs.begin() + r_s;
    auto rhs_end = rhs.begin() + r_e;
    auto rhs_it = std::upper_bound(rhs_begin, rhs_end, *lhs_it);
    StepResult res;
    res.lhs_idx = lhs_it - lhs.begin();
    res.rhs_idx = rhs_it - rhs.begin();
    return res;
  }

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

    size_t full_size = nums1.size() + nums2.size();
    size_t m_idx = full_size / 2;
    size_t l_s = 0;
    size_t l_e = nums1.size();
    size_t r_s = 0;
    size_t r_e = nums2.size();
    while (true) {
      StepResult res = GetNumBefore(nums1, l_s, l_e, nums2, r_s, r_e);
      size_t num_before = res.lhs_idx + res.rhs_idx + 1;
      if (num_before == m_idx) {
        if (res.lhs_idx == nums1.size()) {
          return GetMedianForOne(nums2, res.rhs_idx, !(full_size % 2));
        } else if (res.rhs_idx == nums2.size()) {
          // num_before points to the lhs_idx + 1
          return GetMedianForOne(nums1, res.lhs_idx + 1, !(full_size % 2));
        } else {
          return full_size % 2
                     ? nums2[res.rhs_idx]
                     : 0.5 * (nums1[res.lhs_idx] + nums2[res.rhs_idx]);
        }
      } else if (num_before < m_idx) {
        l_s = res.lhs_idx + 1;
        r_s = res.rhs_idx + 1;
      } else {
        l_e = res.lhs_idx;
        r_e = res.rhs_idx;
      }

      if (l_s >= l_e) {
        // if we collapse in the middle we still can have median between
        // nums1_element and nums2_element!
        return GetMedianForOne(nums2, m_idx - l_e - 1, !(full_size % 2));
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
