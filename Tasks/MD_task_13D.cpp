#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_set>
#include <vector>

constexpr int kEmptyElement = -1;

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<int> BFS(const std::vector<std::unordered_set<int>>& data,
                     int start, int end, std::vector<int> lookup);
std::vector<int> GetPath(const std::vector<int>& parents, int start, int end);
void AddEdge(std::vector<std::unordered_set<int>>& data, int l, int r,
             int curr_add_id);
void CalcFlux(std::vector<std::unordered_set<int>>& data, int start, int end,
              std::vector<std::unordered_set<int>>& actual_flux);
std::vector<std::vector<int>> SearchPathes(
    const std::vector<std::unordered_set<int>>& data, int start, int end);

void PrintPath(const std::vector<int>& path, int max_id);

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
  std::vector<std::unordered_set<int>> data(vertex_num);
  int curr_add_id = vertex_num;
  while (edge_num--) {
    int l, r;
    input >> l >> r;
    if (l == r) continue;
    --l;
    --r;
    AddEdge(data, l, r, curr_add_id);
    ++curr_add_id;
  }
  std::vector<std::unordered_set<int>> actual_flux(data.size());
  CalcFlux(data, start, end, actual_flux);
  // Here we try to find path using DFS on actual_flux
  // If we cannot do that -> there is not chance for two players to reach the
  // finish on different pathes.
  std::vector<std::vector<int>> pathes = SearchPathes(actual_flux, start, end);
  if (pathes.size() < 2) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
    PrintPath(pathes[0], vertex_num);
    PrintPath(pathes[1], vertex_num);
  }
}

void PrintPath(const std::vector<int>& path, int max_id) {
  for (const auto& el : path) {
    if (el < max_id) {
      std::cout << el + 1 << ' ';
    }
  }
  std::cout << '\n';
}

std::vector<std::vector<int>> SearchPathes(
    const std::vector<std::unordered_set<int>>& data, int start, int end) {
  std::vector<int> lookup(data.size());
  std::vector<int> parents = BFS(data, start, end, lookup);
  if (parents[end] == kEmptyElement) return {};
  std::vector<int> path_1 = GetPath(parents, start, end);
  for (size_t i = 1; i < path_1.size() - 1; ++i) {
    lookup[path_1[i]] = 1;
  }
  parents = BFS(data, start, end, lookup);
  if (parents[end] == kEmptyElement) return {};
  return {path_1, GetPath(parents, start, end)};
}

void DFS(const std::vector<std::unordered_set<int>>& data, int id, int end,
         std::vector<int>& lookup, std::vector<int>& parents) {
  lookup[id] = 1;
  if (id == end) return;
  for (const auto& el : data[id]) {
    if (lookup[el]) continue;
    parents[el] = id;
    DFS(data, el, end, lookup, parents);
  }
}

void CalcFlux(std::vector<std::unordered_set<int>>& data, int start, int end,
              std::vector<std::unordered_set<int>>& actual_flux) {
  std::vector<int> parents =
      BFS(data, start, end, std::vector<int>(data.size()));
  if (parents[end] == kEmptyElement) return;
  std::vector<int> path = GetPath(parents, start, end);
  // Now we push flux
  auto s = path.begin();
  auto e = std::next(s);
  while (e != path.end()) {
    // Remove capacity from positive direction
    data[*s].erase(*e);
    // Add capacity to negative direction
    data[*e].insert(*s);
    // Create actual flux or delete if the opposite exists
    auto op_it = actual_flux[*e].find(*s);
    if (op_it == actual_flux[*e].end()) {
      actual_flux[*s].insert(*e);
    } else {
      actual_flux[*e].erase(op_it);
    }
    ++s;
    ++e;
  }
  CalcFlux(data, start, end, actual_flux);
}

void AddEdge(std::vector<std::unordered_set<int>>& data, int l, int r,
             int curr_add_id) {
  data.resize(curr_add_id + 1);
  data[l].insert(curr_add_id);
  data[curr_add_id].insert(r);
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

std::vector<int> BFS(const std::vector<std::unordered_set<int>>& data,
                     int start, int end, std::vector<int> lookup) {
  std::vector<int> parents(data.size(), kEmptyElement);
  std::queue<int> buff;
  buff.push(start);
  lookup[start] = 1;
  while (!buff.empty()) {
    int top_id = buff.front();
    if (top_id == end) break;
    buff.pop();
    for (const auto& el : data[top_id]) {
      if (!lookup[el]) {
        lookup[el] = 1;
        buff.push(el);
        parents[el] = top_id;
      }
    }
  }
  return parents;
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
