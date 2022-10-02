#include <iostream>
#include <sstream>
#include <vector>

class Point {
 public:
  Point() = default;
  Point(int64_t x, int64_t y) : x_(x), y_(y) {}
  int64_t GetX() const { return x_; }
  int64_t GetY() const { return y_; }

 private:
  int64_t x_ = 0;
  int64_t y_ = 0;
};

bool operator==(const Point& l, const Point& r) {
  return l.GetX() == r.GetX() && l.GetY() == r.GetY();
}

bool operator!=(const Point& l, const Point& r) { return !(l == r); }

class Vector {
 public:
  Vector(Point start, Point end) : start_(start), end_(end) {}

  Point GetStart() const { return start_; }
  Point GetEnd() const { return end_; }

  int64_t Cross(const Vector& other) const {
    return (end_.GetX() - start_.GetX()) *
               (other.end_.GetY() - other.start_.GetY()) -
           (other.end_.GetX() - other.start_.GetX()) *
               (end_.GetY() - start_.GetY());
  }

  int64_t Dot(const Vector& other) const {
    return (end_.GetX() - start_.GetX()) *
               (other.end_.GetX() - other.start_.GetX()) +
           (end_.GetY() - start_.GetY()) *
               (other.end_.GetY() - other.start_.GetY());
  }

  int64_t SqrLen() const {
    return (end_.GetX() - start_.GetX()) * (end_.GetX() - start_.GetX()) +
           (end_.GetY() - start_.GetY()) * (end_.GetY() - start_.GetY());
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

  bool DoCoincide(const Vector& other) const {
    int64_t dot_res = Dot(other);
    return dot_res * dot_res == SqrLen() * other.SqrLen();
  }

 private:
  int64_t Direction(Point p1, Point p2, Point p3) const {
    return Vector{p1, p3}.Cross({p1, p2});
  }

  bool OnSegment(Point p) const {
    int64_t min_x = start_.GetX();
    int64_t max_x = end_.GetX();
    if (min_x > max_x) std::swap(min_x, max_x);

    int64_t min_y = start_.GetY();
    int64_t max_y = end_.GetY();
    if (min_y > max_y) std::swap(min_y, max_y);

    return p.GetX() <= max_x && p.GetX() >= min_x && p.GetY() <= max_y &&
           p.GetY() >= min_y;
  }

  Point start_;
  Point end_;
};

void Solution(std::istream& input = std::cin);
void RunTests();

Vector GetNextVector(const std::vector<Vector>& data, int curr_index) {
  return data[(curr_index + 1) % data.size()];
}

Vector GetPrevVector(const std::vector<Vector>& data, int curr_index) {
  int prev = curr_index == 0 ? data.size() - 1 : curr_index - 1;
  return data[prev];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int64_t n, x, y;
  input >> n >> x >> y;
  Point test(x, y);
  std::vector<Point> raw_data(n);
  for (auto& el : raw_data) {
    input >> x >> y;
    el = Point(x, y);
  }
  // Filter zero length
  std::vector<Point> data;
  data.reserve(raw_data.size());
  for (const auto& el : raw_data) {
    if (data.empty() || el != data.back()) {
      data.push_back(el);
    }
  }

  std::vector<Vector> side_data;
  side_data.reserve(data.size());
  for (int64_t i = 1; i < data.size(); ++i) {
    side_data.push_back(Vector{data[i - 1], data[i]});
  }
  side_data.push_back(Vector{data.back(), data.front()});

  // Building test vector
  int64_t max_x = 0;
  for (const auto& p : data) {
    max_x = std::max(max_x, p.GetX());
  }
  ++max_x;
  Vector test_vec{test, Point{max_x, test.GetY()}};

  // Counting crossections
  int count = 0;
  // int d_count = 0;
  for (int i = 0; i < side_data.size(); ++i) {
    // if (side_data[i].GetStart().GetY() == test.GetY() &&
    //     side_data[i].GetStart().GetX() >= test.GetX()) {
    //   d_count++;
    // }

    if (side_data[i].HasPoint(test)) {
      std::cout << "YES\n";
      return;
    } else if (test_vec.HasPoint(side_data[i].GetStart())) {
      // Count crossections if prev start and this end are on the different
      // sides relatively the test vec
      Point prev = GetPrevVector(side_data, i).GetStart();
      int64_t prev_dir = test_vec.Cross({test, prev});
      int64_t next_dir = test_vec.Cross({test, side_data[i].GetEnd()});
      count += (prev_dir > 0 && next_dir < 0) || (prev_dir < 0 && next_dir > 0);
    } else if (test_vec.HasPoint(side_data[i].GetEnd())) {
      // Count if this start and next end are on the differnt side relatively
      // to the test_vec
      // Point next = GetNextVector(side_data, i).GetEnd();
      // int64_t prev_dir = test_vec.Cross({test, side_data[i].GetStart()});
      // int64_t next_dir = test_vec.Cross({test, next});
      // count += (prev_dir > 0 && next_dir < 0) || (prev_dir < 0 && next_dir >
      // 0);
      //
      // DO NOTHING. next time it will be checked as start
    } else if (side_data[i].DoCrosses(test_vec)) {
      ++count;
    }
  }
  std::cout << ((count % 2) ? "YES\n" : "NO\n");
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
