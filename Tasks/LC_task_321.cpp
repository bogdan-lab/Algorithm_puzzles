#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>

using Number = std::vector<int>;
struct EqualRes {
  size_t count = 0;
  bool left_is_better = true;
};

bool IsLess(const std::vector<int>& lhs, const std::vector<int>& rhs) {
  assert(lhs.size() == rhs.size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    if (lhs[i] < rhs[i]) {
      return true;
    } else if (lhs[i] > rhs[i]) {
      return false;
    }
  }
  return false;
}

Number Create(int prefix, const Number& suffix) {
  Number res;
  res.reserve(suffix.size() + 1);
  res.push_back(prefix);
  std::copy(suffix.begin(), suffix.end(), std::back_inserter(res));
  return res;
}

Number BuildMaxNumber(const Number& data, size_t num_size) {
  assert(num_size <= data.size());
  Number res;
  res.reserve(num_size);
  for (size_t i = 0; i < data.size(); ++i) {
    size_t elements_left = data.size() - i - 1;
    while (!res.empty() && res.back() < data[i] &&
           num_size - res.size() <= elements_left) {
      res.pop_back();
    }
    if (res.size() < num_size) {
      res.push_back(data[i]);
    }
  }
  return res;
}

EqualRes CountEqual(const Number& lhs, size_t li, const Number& rhs,
                    size_t ri) {
  EqualRes res;
  while (li < lhs.size() && ri < rhs.size() && lhs[li] == rhs[ri]) {
    ++li;
    ++ri;
    ++res.count;
  }
  res.left_is_better =
      ri == rhs.size() ||
      (li < lhs.size() && ri < rhs.size() && lhs[li] > rhs[ri]);
  return res;
}

Number Merge(const Number& lhs, const Number& rhs) {
  Number res;
  res.reserve(lhs.size() + rhs.size());
  size_t li = 0;
  size_t ri = 0;
  while (li < lhs.size() || ri < rhs.size()) {
    if (li == lhs.size()) {
      res.push_back(rhs[ri++]);
    } else if (ri == rhs.size()) {
      res.push_back(lhs[li++]);
    } else {
      if (lhs[li] < rhs[ri]) {
        res.push_back(rhs[ri++]);
      } else if (lhs[li] > rhs[ri]) {
        res.push_back(lhs[li++]);
      } else {
        EqualRes eq = CountEqual(lhs, li, rhs, ri);
        while (eq.count--) {
          if (eq.left_is_better) {
            res.push_back(lhs[li++]);
          } else {
            res.push_back(rhs[ri++]);
          }
        }
      }
    }
  }
  return res;
}

Number FindLargestNumber(Number& lhs, Number& rhs, int k) {
  Number max_num(k, 0);
  for (size_t left_size = 0; left_size <= k; ++left_size) {
    size_t right_size = k - left_size;
    if (left_size > lhs.size() || right_size > rhs.size()) {
      continue;
    }
    Number current =
        Merge(BuildMaxNumber(lhs, left_size), BuildMaxNumber(rhs, right_size));
    if (IsLess(max_num, current)) {
      max_num = std::move(current);
    }
  }
  return max_num;
}

class Solution {
 public:
  std::vector<int> maxNumber(Number& left, Number& right, int k) {
    return FindLargestNumber(left, right, k);
  }
};

int main() {
  Solution s;
  Number left = {7, 3, 4, 6, 5};
  Number right = {1, 0, 0};
  s.maxNumber(left, right, 4);
  return 0;
}