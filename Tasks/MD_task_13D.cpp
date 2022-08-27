#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

constexpr int kEmptyElement = -1;

struct Edge {
  int start = kEmptyElement;
  int end = kEmptyElement;
  int count = 0;
};

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<int> BFS(const std::vector<std::vector<Edge>>& data, int start,
                     int end);
std::vector<int> GetPath(const std::vector<int>& parents, int start, int end);
void DeletePath(std::vector<std::vector<Edge>>& data,
                const std::vector<int>& path);

void AccumulateInplace(std::vector<Edge>& data);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int vertex_num, edge_num, start, end;
  input >> vertex_num >> edge_num >> start >> end;
  --start;
  --end;
  std::vector<std::vector<Edge>> data(vertex_num);
  while (edge_num--) {
    int l, r;
    input >> l >> r;
    --l;
    --r;
    if (l == r) continue;
    data[l].push_back({l, r, 1});
  }

  for (auto& el : data) {
    std::sort(el.begin(), el.end(),
              [](Edge l, Edge r) { return l.end < r.end; });
    AccumulateInplace(el);
  }

  // Find the first path
  std::vector<int> parents = BFS(data, start, end);
  if (parents[end] == kEmptyElement) {
    std::cout << "NO\n";
    return;
  }
  std::vector<int> path_1 = GetPath(parents, start, end);
  DeletePath(data, path_1);
  // Find the second path
  parents = BFS(data, start, end);
  if (parents[end] == kEmptyElement) {
    std::cout << "NO\n";
    return;
  }
  std::vector<int> path_2 = GetPath(parents, start, end);

  std::cout << "YES\n";
  for (const auto& el : path_1) {
    std::cout << el + 1 << ' ';
  }
  std::cout << '\n';
  for (const auto& el : path_2) {
    std::cout << el + 1 << ' ';
  }
  std::cout << '\n';
}

void DeletePath(std::vector<std::vector<Edge>>& data,
                const std::vector<int>& path) {
  auto f = path.begin();
  auto e = std::next(f);
  while (e != path.end()) {
    auto it = std::lower_bound(data[*f].begin(), data[*f].end(), *e,
                               [](Edge edge, int id) { return edge.end < id; });
    it->count -= 1;
    ++f;
    ++e;
  }
}

std::vector<int> GetPath(const std::vector<int>& parents, int start, int end) {
  std::vector<int> res;
  int c = end;
  while (c != start) {
    res.push_back(c);
    c = parents[c];
  }
  res.push_back(c);
  std::reverse(res.begin(), res.end());
  return res;
}

std::vector<int> BFS(const std::vector<std::vector<Edge>>& data, int start,
                     int end) {
  std::vector<int> parents(data.size(), kEmptyElement);
  std::vector<int> lookup(data.size());
  std::queue<int> buff;
  buff.push(start);
  lookup[start] = 1;
  while (!buff.empty()) {
    int top_id = buff.front();
    if (top_id == end) break;
    buff.pop();
    for (const auto& el : data[top_id]) {
      if (el.count && !lookup[el.end]) {
        lookup[el.end] = 1;
        buff.push(el.end);
        parents[el.end] = top_id;
      }
    }
  }
  return parents;
}

void AccumulateInplace(std::vector<Edge>& data) {
  if (data.empty()) return;
  auto f = data.begin();
  auto c = std::next(f);
  while (c != data.end()) {
    if (c->end == f->end) {
      f->count += c->count;
      ++c;
    } else {
      ++f;
      if (f != c) {
        std::swap(*f, *c);
      }
      ++c;
    }
  }
  data.erase(++f, data.end());
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 3 1 3
   1 2
   1 3
   2 3
  )";
    Solution(ss);
    std::cout << "expected = YES; 1 3; 1 2 3\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 4 1 3
   1 2
   1 2
   2 3
   2 3
  )";
    Solution(ss);
    std::cout << "expected = YES; 1 2 3; 1 2 3\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 7 1 3
   1 2
   3 3
   1 2
   2 3
   2 2
   2 3
   1 1
  )";
    Solution(ss);
    std::cout << "expected = YES; 1 2 3; 1 2 3\n";
  }
  {
    std::stringstream ss;
    ss << R"(3 2 1 3
1 2
2 3
)";
    Solution(ss);
    std::cout << "expected = NO\n";
  }
  {
    std::stringstream ss;
    ss << R"(5 5 1 4
1 2
2 3
3 4
1 5
5 3
)";
    Solution(ss);
    std::cout << "expected = NO\n";
  }
  {
    std::stringstream ss;
    ss << R"(8 9 1 4
1 2
2 3
3 4
1 5
5 3
4 6
6 7
4 8
8 7
)";
    Solution(ss);
    std::cout << "expected = NO\n";
  }
  {
    std::stringstream ss;
    ss << R"(2 2 1 2
1 2
1 2
)";
    Solution(ss);
    std::cout << "expected = YES; 1 2; 1 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(8 10 1 7
1 2
2 3
3 4
3 4
1 5
5 3
4 6
6 7
4 8
8 7
)";
    Solution(ss);
    std::cout << "expected = YES; 1 2 3 4 6 7; 1 5 3 4 8 7\n";
  }
}
