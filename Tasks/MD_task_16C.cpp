#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

enum class Crossing { kNotCross, kUpword, kDownword };

struct Point {
  int x = 0;
  int y = 0;
};

Crossing CheckCrossing(Point start, Point end, int y) {
  if (start.y <= y && end.y >= y) {
    return Crossing::kUpword;
  } else if (start.y >= y && end.y <= y) {
    return Crossing::kDownword;
  } else {
    return Crossing::kNotCross;
  }
}

int64_t Cross(Point s1, Point e1, Point s2, Point e2) {
  return (e1.x - s1.x) * (e2.y - s2.y) - (e2.x - s2.x) * (e1.y - s1.y);
}

bool CheckInSegment(Point s, Point e, Point p) {
  int min_x = s.x;
  int max_x = e.x;
  if (min_x > max_x) std::swap(min_x, max_x);

  int min_y = s.y;
  int max_y = e.y;
  if (min_y > max_y) std::swap(min_y, max_y);

  return p.x <= max_x && p.x >= min_x && p.y <= max_y && p.y >= min_y;
}

bool HasPoint(Point start, Point end, Point p) {
  int64_t res = Cross(start, p, start, end);
  if (res) return false;
  return CheckInSegment(start, end, p);
}

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int64_t n;
  Point p;
  input >> n >> p.x >> p.y;

  std::vector<Point> data(n + 1);
  for (int i = 0; i < n; ++i) {
    input >> data[i].x >> data[i].y;
  }
  data.back() = data.front();

  int wn = 0;
  for (int i = 1; i < data.size(); ++i) {
    Point s = data[i - 1];
    Point e = data[i];
    if (HasPoint(s, e, p)) {
      std::cout << "YES\n";
      return;
    }
    Crossing cr = CheckCrossing(s, e, p.y);
    switch (cr) {
      case Crossing::kUpword: {
        wn += Cross(s, e, s, p) > 0;
        break;
      }
      case Crossing::kDownword: {
        wn -= Cross(s, e, s, p) < 0;
        break;
      }
      default: {
        break;
      }
    }
  }
  std::cout << (wn ? "YES\n" : "NO\n");
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 2 3
1 1
10 2
2 8
)";
    Solution(ss);
    std::cout << "expected = YES\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 1 1
1 1
10 2
2 8
)";
    Solution(ss);
    std::cout << "expected = YES\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 1 5
1 1
10 2
1 8
)";
    Solution(ss);
    std::cout << "expected = YES\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 5 1
1 1
10 2
10 1
)";
    Solution(ss);
    std::cout << "expected = YES\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 -5 1
1 1
10 2
10 1
)";
    Solution(ss);
    std::cout << "expected = NO\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 -5 1
1 1
5 5
-5 5
)";
    Solution(ss);
    std::cout << "expected = NO\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 -2 1
1 1
-5 -5
-5 5
)";
    Solution(ss);
    std::cout << "expected = YES\n";
  }
}
