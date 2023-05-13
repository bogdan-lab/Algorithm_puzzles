#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

using Number = std::vector<int>;
struct EqualRes {
  size_t count = 0;
  bool left_is_better = true;
};

void PrintNumber(const Number& n) {
  for (const auto& el : n) {
    std::cout << el << ",";
  }
  std::cout << '\n';
}

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
  assert(res.size() == num_size);
  return res;
}

EqualRes CountEqual(const Number& lhs, size_t li, const Number& rhs,
                    size_t ri) {
  EqualRes res;
  assert(lhs[li] == rhs[ri]);
  auto val = lhs[li];
  while (li < lhs.size() && ri < rhs.size() && lhs[li] == rhs[ri]) {
    res.count += (lhs[li] == val);
    ++li;
    ++ri;
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
  std::cout << "lhs.size = " << lhs.size() << " rhs.size = " << rhs.size()
            << '\n';
  for (size_t left_size = 0; left_size <= k; ++left_size) {
    size_t right_size = k - left_size;
    if (left_size > lhs.size() || right_size > rhs.size()) {
      continue;
    }
    Number lhs_best = BuildMaxNumber(lhs, left_size);
    Number rhs_best = BuildMaxNumber(rhs, right_size);
    // std::cout << "lbest_size = " << lhs_best.size()
    //           << " rbest_size = " << rhs_best.size() << '\n';
    Number current = Merge(lhs_best, rhs_best);
    std::cout << "LEFT = ";
    PrintNumber(lhs_best);
    std::cout << "RIGHT = ";
    PrintNumber(rhs_best);
    PrintNumber(current);
    if (IsLess(max_num, current)) {
      max_num = std::move(current);
      // std::cout << "MAX_NUM = \n";
      // PrintNumber(max_num);
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
  Number left{2, 1, 7, 8, 0, 1, 7, 3, 5, 8, 9, 0, 0, 7, 0, 2, 2, 7, 3, 5, 5};
  Number right{2, 6, 2, 0, 1, 0, 5, 4, 5, 5, 3, 3, 3, 4};
  auto res = s.maxNumber(left, right, 35);
  PrintNumber(res);
  return 0;
}