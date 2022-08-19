#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <vector>

constexpr int kIntInfinity = std::numeric_limits<int>::max();
constexpr double kDoubleInfinity = std::numeric_limits<double>::max();
constexpr int kEmptyId = -1;

struct Point {
  int x = 0;
  int y = 0;
};

class SpecialPriorityQueue {
 public:
  SpecialPriorityQueue(int el_num)
      : ids_(el_num), values_(el_num, kDoubleInfinity), id_to_pos_(el_num) {
    std::iota(ids_.begin(), ids_.end(), 0);
    std::iota(id_to_pos_.begin(), id_to_pos_.end(), 0);
  }

  bool HasElement(int id) const { return id_to_pos_[id] != kIntInfinity; }

  bool Empty() const { return ids_.empty(); }

  int GetMinId() const { return ids_[0]; }

  double GetValue(int id) const {
    assert(HasElement(id));
    return values_[id_to_pos_[id]];
  }

  void Pop() {
    int curr_min = ids_[0];
    Swap(0, ids_.size() - 1);
    values_.pop_back();
    ids_.pop_back();
    id_to_pos_[curr_min] = kIntInfinity;
    SiftDown(0);
  }

  void MoveIdHigher(int id, double new_val) {
    assert(HasElement(id));
    int curr_pos = id_to_pos_[id];
    assert(new_val < values_[curr_pos]);
    values_[curr_pos] = new_val;
    SiftUp(curr_pos);
  }

 private:
  static int Parent(int pos) { return (pos - 1) / 2; }
  static int Left(int pos) { return 2 * pos + 1; }
  static int Right(int pos) { return 2 * pos + 2; }

  void Swap(int l_pos, int r_pos) {
    std::swap(values_[l_pos], values_[r_pos]);
    std::swap(id_to_pos_[ids_[l_pos]], id_to_pos_[ids_[r_pos]]);
    std::swap(ids_[l_pos], ids_[r_pos]);
  }

  void SiftUp(int pos) {
    int parent = Parent(pos);
    while (parent >= 0 && values_[parent] > values_[pos]) {
      Swap(parent, pos);
      pos = parent;
      parent = Parent(pos);
    }
  }

  void SiftDown(int pos) {
    int l_c = Left(pos);
    int r_c = Right(pos);
    if (l_c >= values_.size()) return;
    int min = l_c;
    if (r_c < values_.size() && values_[r_c] < values_[min]) {
      min = r_c;
    }
    if (values_[pos] > values_[min]) {
      Swap(pos, min);
      SiftDown(min);
    }
  }

  std::vector<int> ids_;
  std::vector<double> values_;
  std::vector<int> id_to_pos_;
};

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<int> Prima(const std::vector<Point>& points);
double CalculateSum(const std::vector<Point>& points,
                    const std::vector<int>& parents);
double GetDistance(Point lhs, Point rhs);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int point_num;
  input >> point_num;
  std::vector<Point> points;
  points.reserve(point_num);
  while (point_num--) {
    int x, y;
    input >> x >> y;
    points.push_back({x, y});
  }

  std::vector<int> parents = Prima(points);
  std::cout << CalculateSum(points, parents) << '\n';
}

std::vector<int> Prima(const std::vector<Point>& points) {
  std::vector<int> parents(points.size(), kEmptyId);
  SpecialPriorityQueue queue(points.size());
  queue.MoveIdHigher(/*id=*/0, /*value=*/0);
  while (!queue.Empty()) {
    int top_id = queue.GetMinId();
    queue.Pop();
    for (int i = 0; i < points.size(); ++i) {
      if (i == top_id) continue;
      if (queue.HasElement(i)) {
        double val = GetDistance(points[i], points[top_id]);
        if (val < queue.GetValue(i)) {
          parents[i] = top_id;
          queue.MoveIdHigher(i, val);
        }
      }
    }
  }
  return parents;
}

double CalculateSum(const std::vector<Point>& points,
                    const std::vector<int>& parents) {
  double sum = 0.0;
  if (parents.empty()) return sum;
  std::vector<int> lookup(parents.size());
  for (int id = parents.size() - 1; id >= 0; --id) {
    if (lookup[id]) continue;
    lookup[id] = 1;
    if (parents[id] == kEmptyId) continue;
    sum += GetDistance(points[id], points[parents[id]]);
  }
  return sum;
}

double GetDistance(Point lhs, Point rhs) {
  int x_dif = lhs.x - rhs.x;
  int y_dif = lhs.y - rhs.y;
  return std::sqrt(static_cast<double>(x_dif * x_dif + y_dif * y_dif));
}
void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2
   0 0
   1 1
  )";
    Solution(ss);
    std::cout << "expected = 1.4142135624\n";
  }
  {
    std::stringstream ss;
    ss << R"(5
   0 0
   1 1
   2 2
   3 3
   4 4
  )";
    Solution(ss);
    std::cout << "expected = 5.656854249\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
0 0
1 1
0 1
1 0
)";
    Solution(ss);
    std::cout << "expected = 3.0\n";
  }
}
