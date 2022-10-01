#include <algorithm>
#include <iostream>
#include <sstream>

class Point {
 public:
  Point(int x, int y) : x_(x), y_(y) {}
  int GetX() const { return x_; }
  int GetY() const { return y_; }

 private:
  int x_ = 0;
  int y_ = 0;
};

class Vector {
 public:
  Vector(Point start, Point end) : start_(start), end_(end) {}

  int Cross(const Vector& other) const {
    return (end_.GetX() - start_.GetX()) *
               (other.end_.GetY() - other.start_.GetY()) -
           (other.end_.GetX() - other.start_.GetX()) *
               (end_.GetY() - start_.GetY());
  }

  bool HasPoint(Point p) const {
    if (Cross({end_, p})) return false;
    int min_x = start_.GetX();
    int max_x = end_.GetX();
    if (min_x > max_x) std::swap(min_x, max_x);

    int min_y = start_.GetY();
    int max_y = end_.GetY();
    if (min_y > max_y) std::swap(min_y, max_y);

    return p.GetX() <= max_x && p.GetX() >= min_x && p.GetY() <= max_y &&
           p.GetY() >= min_y;
  }

 private:
  Point start_;
  Point end_;
};

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
  int x, y;
  input >> x >> y;
  Point test(x, y);
  input >> x >> y;
  Point start(x, y);
  input >> x >> y;
  Point end(x, y);

  Vector vec(start, end);

  std::cout << (vec.HasPoint(test) ? "YES\n" : "NO\n");
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 3 1 2 5 4)";
    Solution(ss);
    std::cout << "expected = YES\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 2 4 2 4 5)";
    Solution(ss);
    std::cout << "expected = YES\n";
  }
  {
    std::stringstream ss;
    ss << R"(40 2 4 2 4 5)";
    Solution(ss);
    std::cout << "expected = NO\n";
  }
}
