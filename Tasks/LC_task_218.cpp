#include <algorithm>
#include <cassert>
#include <limits>
#include <stack>
#include <tuple>
#include <vector>

struct Point {
  int64_t x = 0;
  int64_t y = 0;
};

enum class Direction { kLeft, kRight, kStraight };

Direction GetDirection(Point p0, Point p1, Point p2) {
  Point lhs{p1.x - p0.x, p1.y - p0.y};
  Point rhs{p2.x - p0.x, p2.y - p0.y};

  int64_t r = lhs.y * rhs.x;
  int64_t l = lhs.x * rhs.y;

  if (l > r) {
    return Direction::kLeft;
  } else if (l < r) {
    return Direction::kRight;
  } else {
    return Direction::kStraight;
  }
}

std::vector<Point> GrahamScan(const std::vector<Point>& data) {
  std::vector<Point> res;
  res.push_back(data[0]);
  res.push_back(data[1]);
  res.push_back(data[2]);

  for (int i = 3; i < data.size(); ++i) {
    while (GetDirection(res[res.size() - 2], res.back(), data[i]) ==
           Direction::kLeft) {
      res.pop_back();
    }
    res.push_back(data[i]);
  }

  return res;
}

std::vector<std::vector<int>> ExtractAnswer(const std::vector<Point>& gstk) {
  std::vector<std::vector<int>> res;
  res.reserve(gstk.size() - 1);
  for (int i = 1; i < gstk.size(); ++i) {
    res.emplace_back();
    if (res.size() == 1) {
      res.back().push_back(gstk[i].x);
      res.back().push_back(gstk[i].y);
    } else {
      if (res[res.size() - 2][1] > gstk[i].y) {
        res.back().push_back(res[res.size() - 2][0]);
        res.back().push_back(gstk[i].y);
      } else if (res[res.size() - 2][1] < gstk[i].y) {
        res.back().push_back(gstk[i].x);
        res.back().push_back(gstk[i].y);
      }
    }
  }

  return res;
}

class Solution {
 public:
  std::vector<std::vector<int>> getSkyline(
      std::vector<std::vector<int>>& buildings) {
    std::vector<Point> data;
    data.reserve(2 * buildings.size() + 2);
    data.push_back({buildings[0][0], 0});
    data.push_back({std::numeric_limits<int>::max(), 0});
    for (const auto& el : buildings) {
      data.push_back({el[0], el[2]});
      data.push_back({el[1], el[2]});
    }

    std::sort(data.begin(), data.end(), [](Point l, Point r) {
      return std::tie(l.x, l.y) < std::tie(r.x, r.y);
    });

    std::vector<Point> gstk = GrahamScan(data);
    return ExtractAnswer(gstk);
  }
};

int main() {
  Solution s;
  {
    std::vector<std::vector<int>> input{
        {2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
    std::vector<std::vector<int>> exp{{2, 10},  {3, 15}, {7, 12}, {12, 0},
                                      {15, 10}, {20, 8}, {24, 0}};
    assert(s.getSkyline(input) == exp);
  }
  return 0;
}
