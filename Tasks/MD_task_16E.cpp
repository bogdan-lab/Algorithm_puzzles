#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

struct Point {
  double x = 0;
  double y = 0;
  double angle = 0.0;
  double len = 0.0;
};

bool operator==(const Point& l, const Point& r) {
  return l.x == r.x && l.y == r.y;
}

bool operator!=(const Point& l, const Point& r) { return !(l == r); }

bool IsLeftTurn(Point p1, Point p2, Point p3);

double Perimeter(const std::vector<Point>& data);
double Length(const Point& l, const Point& r);

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

bool IsLeftTurn(Point p1, Point p2, Point p3) {
  return (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x) > 0;
}

double SqrLength(const Point& l, const Point& r) {
  double dx = r.x - l.x;
  double dy = r.y - l.y;
  return dx * dx + dy * dy;
}

double Length(const Point& l, const Point& r) {
  return std::sqrt(SqrLength(l, r));
}

double Perimeter(const std::vector<Point>& data) {
  double res = 0.0;
  for (int i = 1; i < data.size(); ++i) {
    res += Length(data[i - 1], data[i]);
  }
  res += Length(data.back(), data.front());
  return res;
}

double PolarAngle(Point s, Point e) { return -(e.x - s.x) / e.len; }

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<Point> data(n);
  for (auto& el : data) {
    input >> el.x >> el.y;
  }

  std::swap(data.back(), *std::min_element(data.begin(), data.end(),
                                           [](const Point& l, const Point& r) {
                                             return std::tie(l.y, l.x) <
                                                    std::tie(r.y, r.x);
                                           }));

  Point min_point = data.back();
  data.pop_back();

  for (auto& el : data) {
    el.len = SqrLength(min_point, el);
    el.angle = PolarAngle(min_point, el);
  }

  std::sort(data.begin(), data.end(), [](const Point& l, const Point& r) {
    double nl = -l.len;
    double nr = -r.len;
    return std::tie(l.angle, nl) < std::tie(r.angle, nr);
  });

  data.erase(std::unique(data.begin(), data.end(),
                         [](const Point& l, const Point& r) {
                           return l.angle == r.angle;
                         }),
             data.end());

  std::vector<Point> stack;
  stack.reserve(data.size());
  stack.push_back(min_point);
  int index = 0;
  stack.push_back(data[index++]);
  stack.push_back(data[index++]);
  while (index < data.size()) {
    size_t s = stack.size();
    while (!IsLeftTurn(stack[s - 2], stack[s - 1], data[index])) {
      stack.pop_back();
    }
    stack.push_back(data[index]);
    ++index;
  }

  std::cout << std::setprecision(20) << Perimeter(stack) << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
0 0
2 0
0 2
1 1
2 2
)";
    Solution(ss);
    std::cout << "expected = 8\n";
  }
}
