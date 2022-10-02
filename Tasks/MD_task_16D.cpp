#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

class Point {
 public:
  Point() = default;
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
    return OnSegment(p);
  }

  bool DoCrosses(const Vector& other) const {
    int side_1 = Direction(start_, end_, other.start_);
    int side_2 = Direction(start_, end_, other.end_);

    int side_3 = Direction(other.start_, other.end_, start_);
    int side_4 = Direction(other.start_, other.end_, end_);

    bool other_at_different_sides =
        (side_1 > 0 && side_2 < 0) || (side_1 < 0 && side_2 > 0);
    bool this_at_different_sides =
        (side_3 > 0 && side_4 < 0) || (side_3 < 0 && side_4 > 0);

    if (other_at_different_sides && this_at_different_sides) {
      return true;
    } else if (side_1 == 0 && OnSegment(other.start_)) {
      return true;
    } else if (side_2 == 0 && OnSegment(other.end_)) {
      return true;
    } else if (side_3 == 0 && other.OnSegment(start_)) {
      return true;
    } else if (side_4 == 0 && other.OnSegment(end_)) {
      return true;
    } else {
      return false;
    }
  }

 private:
  int Direction(Point p1, Point p2, Point p3) const {
    return Vector{p1, p3}.Cross({p1, p2});
  }

  bool OnSegment(Point p) const {
    int min_x = start_.GetX();
    int max_x = end_.GetX();
    if (min_x > max_x) std::swap(min_x, max_x);

    int min_y = start_.GetY();
    int max_y = end_.GetY();
    if (min_y > max_y) std::swap(min_y, max_y);

    return p.GetX() <= max_x && p.GetX() >= min_x && p.GetY() <= max_y &&
           p.GetY() >= min_y;
  }

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
  int n;
  input >> n;
  std::vector<Point> data(n);
  for (auto& el : data) {
    int x, y;
    input >> x >> y;
    el = Point{x, y};
  }

  int64_t area = 0;
  int index = 1;
  Vector prev(data[0], data[index++]);
  Vector next(data[0], data[index++]);
  area += prev.Cross(next);
  while (index < data.size()) {
    prev = next;
    next = Vector{data[0], data[index++]};
    area += prev.Cross(next);
  }

  std::cout << 0.5 * std::abs(area) << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
1 0
0 1
1 1
)";
    Solution(ss);
    std::cout << "expected = 0.5\n";
  }
}
