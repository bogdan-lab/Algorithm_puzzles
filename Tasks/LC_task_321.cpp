#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <vector>

using Number = std::vector<int>;

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

Number Merge(const Number& lhs, const Number& rhs) {
  Number res;
  res.reserve(lhs.size() + rhs.size());
  std::merge(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(),
             std::back_inserter(res), std::greater<int>());
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