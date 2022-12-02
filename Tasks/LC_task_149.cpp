#include <algorithm>
#include <limits>
#include <vector>

constexpr int kEmptyValue = std::numeric_limits<int>::max();

struct Line {
  int x_vertical = kEmptyValue;
  int y_horizontal = kEmptyValue;

  std::vector<int> p0;
  int step_right = kEmptyValue;
  int step_up = kEmptyValue;
};

int GetGCD(int lhs, int rhs) {
  if (lhs < rhs) std::swap(lhs, rhs);
  while (rhs) {
    lhs %= rhs;
    std::swap(lhs, rhs);
  }
  return lhs;
}

Line GetLine(std::vector<int> lhs, std::vector<int> rhs) {
  Line res;
  if (lhs[0] > rhs[0]) std::swap(lhs, rhs);
  res.p0 = lhs;
  if (lhs[0] == rhs[0]) {
    res.x_vertical = lhs[0];
    return res;
  }
  if (lhs[1] == rhs[1]) {
    res.y_horizontal = lhs[1];
    return res;
  }

  res.step_right = rhs[0] - lhs[0];
  res.step_up = rhs[1] - lhs[1];
  int gcd = GetGCD(std::abs(res.step_right), std::abs(res.step_up));
  res.step_right /= gcd;
  res.step_up /= gcd;
  return res;
}

bool IsOnLine(std::vector<int> p0, const Line& l) {
  if (p0[0] == l.x_vertical) {
    return true;
  }
  if (p0[1] == l.y_horizontal) {
    return true;
  }
  std::vector<int> cp = l.p0;
  if (p0[0] > cp[0]) std::swap(p0, cp);
  int right = cp[0] - p0[0];
  // step_right is always positive!
  int steps = right / l.step_right;
  if (right != steps * l.step_right) return false;
  return steps * l.step_up + p0[1] == cp[1];
}

class Solution {
 public:
  int maxPoints(std::vector<std::vector<int>>& points) {
    if (points.size() <= 1) return 1;
    std::vector<Line> all_lines;
    for (int i = 0; i < points.size(); ++i) {
      for (int j = i + 1; j < points.size(); ++j) {
        all_lines.push_back(GetLine(points[i], points[j]));
      }
    }

    std::vector<int> count(all_lines.size());
    for (const auto& p : points) {
      for (int i = 0; i < all_lines.size(); ++i) {
        if (IsOnLine(p, all_lines[i])) {
          ++count[i];
        }
      }
    }
    return *std::max_element(count.begin(), count.end());
  }
};
