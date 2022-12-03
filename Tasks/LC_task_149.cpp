#include <algorithm>
#include <limits>
#include <map>
#include <vector>

int GetGCD(int lhs, int rhs) {
  if (lhs > rhs) std::swap(lhs, rhs);
  while (rhs) {
    lhs %= rhs;
    std::swap(lhs, rhs);
  }
  return lhs;
}

std::pair<int, int> GetXY(std::vector<int> l, std::vector<int> r) {
  if (l[0] > r[0]) std::swap(l, r);
  std::pair<int, int> res;
  res.first = r[0] - l[0];
  res.second = r[1] - l[1];
  int gcd = GetGCD(res.first, std::abs(res.second));
  res.first /= gcd;
  res.second /= gcd;
  return res;
}

class Solution {
 public:
  int maxPoints(std::vector<std::vector<int>>& points) {
    if (points.size() <= 1) return 1;
    int ans = 0;
    for (int i = 0; i < points.size(); ++i) {
      std::map<std::pair<int, int>, int> dp;
      int same_x = 0;
      int same_y = 0;
      for (int j = i + 1; j < points.size(); ++j) {
        if (points[i][0] == points[j][0]) {
          ++same_x;
        } else if (points[i][1] == points[j][1]) {
          ++same_y;
        } else {
          int& count = dp[GetXY(points[i], points[j])];
          ++count;
          ans = std::max(ans, count);
        }
      }
      ans = std::max({ans, same_x, same_y});
    }
    return ans + 1;
  }
};
