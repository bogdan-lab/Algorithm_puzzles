#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <vector>

constexpr int kEmptyElement = -1;

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<int> BFS(const std::vector<std::unordered_map<int, int>>& data,
                     int start, int end);
std::vector<int> GetPath(const std::vector<int>& parents, int start, int end);
void CalcFlux(std::vector<std::unordered_map<int, int>>& data, int start,
              int end, std::vector<std::unordered_map<int, int>>& actual_flux);
int GetMinFlux(const std::vector<std::unordered_map<int, int>>& data,
               const std::vector<int>& path);
std::vector<std::vector<int>> SearchPathes(
    std::vector<std::unordered_map<int, int>>& data, int start, int end);
void RemovePath(std::vector<std::unordered_map<int, int>>& data,
                const std::vector<int>& path, int min_flux);

void PrintPath(const std::vector<int>& path, int max_id);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int vertex_num, edge_num, start, end;
  input >> vertex_num >> edge_num >> start >> end;
  --start;
  --end;
  std::vector<std::unordered_map<int, int>> data(vertex_num);
  while (edge_num--) {
    int l, r;
    input >> l >> r;
    if (l == r) continue;
    --l;
    --r;
    data[l][r] += 1;
  }
  std::vector<std::unordered_map<int, int>> actual_flux(data.size());
  CalcFlux(data, start, end, actual_flux);
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
    std::vector<std::unordered_map<int, int>>& data, int start, int end) {
  std::vector<int> parents = BFS(data, start, end);
  if (parents[end] == kEmptyElement) return {};
  std::vector<int> path_1 = GetPath(parents, start, end);
  // Check path flux. if it is grater than 1 return 2 copies of itself.
  // otherwise need to find another flux
  int min_flux = GetMinFlux(data, path_1);
  if (min_flux > 1) {
    return {path_1, path_1};
  }
  RemovePath(data, path_1, min_flux);
  parents = BFS(data, start, end);
  if (parents[end] == kEmptyElement) return {};
  return {path_1, GetPath(parents, start, end)};
}

void RemovePath(std::vector<std::unordered_map<int, int>>& data,
                const std::vector<int>& path, int min_flux) {
  auto s = path.begin();
  auto e = std::next(s);
  while (e != path.end()) {
    data[*s][*e] -= min_flux;
    if (!data[*s][*e]) {
      data[*s].erase(*e);
    }
    ++s;
    ++e;
  }
}

void CalcFlux(std::vector<std::unordered_map<int, int>>& data, int start,
              int end, std::vector<std::unordered_map<int, int>>& actual_flux) {
  std::vector<int> parents = BFS(data, start, end);
  if (parents[end] == kEmptyElement) return;
  std::vector<int> path = GetPath(parents, start, end);
  int min_flux = GetMinFlux(data, path);

  // Now we push flux
  auto s = path.begin();
  auto e = std::next(s);
  while (e != path.end()) {
    // Remove capacity from positive direction
    data[*s][*e] -= min_flux;
    if (!data[*s][*e]) {
      data[*s].erase(*e);
    }
    // Add capacity to negative direction
    data[*e][*s] += min_flux;
    // Add flux or remove it if the opposite exists
    auto op_it = actual_flux[*e].find(*s);
    if (op_it == actual_flux[*e].end()) {
      actual_flux[*s][*e] += min_flux;
    } else {
      op_it->second -= min_flux;
      if (!op_it->second) {
        actual_flux[*e].erase(op_it);
      } else if (op_it->second < 0) {
        int remainder = -op_it->second;
        actual_flux[*e].erase(op_it);
        actual_flux[*s][*e] += remainder;
      }
    }
    ++s;
    ++e;
  }
  CalcFlux(data, start, end, actual_flux);
}

int GetMinFlux(const std::vector<std::unordered_map<int, int>>& data,
               const std::vector<int>& path) {
  int min_change = std::numeric_limits<int>::max();
  auto s = path.begin();
  auto e = std::next(s);
  while (e != path.end()) {
    min_change = std::min(min_change, data[*s].at(*e));
    ++s;
    ++e;
  }
  return min_change;
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

std::vector<int> BFS(const std::vector<std::unordered_map<int, int>>& data,
                     int start, int end) {
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
      if (!lookup[el.first]) {
        lookup[el.first] = 1;
        buff.push(el.first);
        parents[el.first] = top_id;
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
