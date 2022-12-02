#include <algorithm>
#include <limits>
#include <vector>

struct Line {
  Line(std::vector<int> l, std::vector<int> r)
      : p1(std::move(l)), p2(std::move(r)) {}
  std::vector<int> p1;
  std::vector<int> p2;
};

int Cross(const std::vector<int>& v1, const std::vector<int>& v2) {
  return v1[0] * v2[1] - v1[1] * v2[0];
}

bool IsOnLine(const Line& l, const std::vector<int>& p) {
  return Cross({p[0] - l.p1[0], p[1] - l.p1[1]},
               {p[0] - l.p2[0], p[1] - l.p2[1]}) == 0;
}

class Solution {
 public:
  int maxPoints(std::vector<std::vector<int>>& points) {
    if (points.size() <= 1) return 1;
    std::vector<Line> all_lines;
    for (int i = 0; i < points.size(); ++i) {
      for (int j = i + 1; j < points.size(); ++j) {
        all_lines.push_back(Line(points[i], points[j]));
      }
    }

    std::vector<int> count(all_lines.size());
    for (const auto& p : points) {
      for (int i = 0; i < all_lines.size(); ++i) {
        if (IsOnLine(all_lines[i], p)) {
          ++count[i];
        }
      }
    }
    return *std::max_element(count.begin(), count.end());
  }
};
