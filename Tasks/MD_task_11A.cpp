#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

struct Point {
  int x = 0;
  int y = 0;
};

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<int> BFS(int field_size, Point start, Point finish);
int GetPointId(int field_size, Point p);
Point GetPointById(int field_size, int id);
bool IsValidPoint(int field_size, Point p);
std::vector<Point> GetNextPoints(Point curr_point, int field_size);

std::vector<int> ExtractPath(const std::vector<int>& pathes, int start_id,
                             int finish_id);

void PrintPath(const std::vector<int>& id_path, int field_size);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int field_size;
  input >> field_size;
  Point start;
  input >> start.x >> start.y;
  --start.x;
  --start.y;
  Point finish;
  input >> finish.x >> finish.y;
  --finish.x;
  --finish.y;
  std::vector<int> pathes = BFS(field_size, start, finish);
  std::vector<int> start_finish_path = ExtractPath(
      pathes, GetPointId(field_size, start), GetPointId(field_size, finish));
  PrintPath(start_finish_path, field_size);
}

int GetPointId(int field_size, Point p) { return p.y * field_size + p.x; }

Point GetPointById(int field_size, int id) {
  return {id % field_size, id / field_size};
}

bool IsValidPoint(int field_size, Point p) {
  return p.x >= 0 && p.x < field_size && p.y >= 0 && p.y < field_size;
}

std::vector<Point> GetNextPoints(Point cp, int field_size) {
  std::vector<Point> result{
      Point{cp.x + 1, cp.y + 2}, Point{cp.x + 2, cp.y + 1},
      Point{cp.x + 2, cp.y - 1}, Point{cp.x + 1, cp.y - 2},
      Point{cp.x - 1, cp.y - 2}, Point{cp.x - 2, cp.y - 1},
      Point{cp.x - 2, cp.y + 1}, Point{cp.x - 1, cp.y + 2}};
  result.erase(std::remove_if(result.begin(), result.end(),
                              [field_size](Point p) {
                                return !IsValidPoint(field_size, p);
                              }),
               result.end());
  return result;
}

std::vector<int> ExtractPath(const std::vector<int>& pathes, int start_id,
                             int finish_id) {
  std::vector<int> id_path;
  int id = finish_id;
  while (id != start_id) {
    id_path.push_back(id);
    id = pathes[id];
  }
  id_path.push_back(id);
  std::reverse(id_path.begin(), id_path.end());
  return id_path;
}

void PrintPath(const std::vector<int>& id_path, int field_size) {
  std::cout << id_path.size() << '\n';
  for (const auto& id : id_path) {
    Point p = GetPointById(field_size, id);
    std::cout << p.x + 1 << ' ' << p.y + 1 << '\n';
  }
}

std::vector<int> BFS(int field_size, Point start, Point finish) {
  std::vector<int> pathes(field_size * field_size);
  std::vector<int> lookup(field_size * field_size);

  std::queue<int> buff;
  int start_id = GetPointId(field_size, start);
  int finish_id = GetPointId(field_size, finish);
  buff.push(start_id);
  lookup[start_id] = 1;
  while (!buff.empty()) {
    int curr_id = buff.front();
    buff.pop();
    Point curr_point = GetPointById(field_size, curr_id);
    std::vector<Point> next_pts = GetNextPoints(curr_point, field_size);
    for (const auto& el : next_pts) {
      int id = GetPointId(field_size, el);
      if (lookup[id]) continue;
      lookup[id] = 1;
      pathes[id] = curr_id;
      buff.push(id);
      if (id == finish_id) return pathes;
    }
  }
  return pathes;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
1 1
3 2
)";
    Solution(ss);
    std::cout << "expected = 2; 1 1; 3 2\n";
  }
}
