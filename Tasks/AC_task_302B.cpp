#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

constexpr int kEmpty = -1;
using Table = std::vector<std::string>;
using Graph = std::vector<std::vector<size_t>>;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

size_t GetNodeIndex(size_t row, size_t col, size_t width) {
  return row * width + col;
}

bool Check(char start, char end) {
  switch (start) {
    case 's':
      return end == 'n';
    case 'n':
      return end == 'u';
    case 'u':
      return end == 'k';
    case 'k':
      return end == 'e';
    default:
      return false;
  }
}

void AddToGraph(const Table& data, size_t row, size_t col, Graph& graph,
                size_t width) {
  if (row > 0) {
    if (Check(data[row][col], data[row - 1][col])) {
      graph[GetNodeIndex(row, col, width)].push_back(
          GetNodeIndex(row - 1, col, width));
    }
  }
  if (col > 0) {
    if (Check(data[row][col], data[row][col - 1])) {
      graph[GetNodeIndex(row, col, width)].push_back(
          GetNodeIndex(row, col - 1, width));
    }
  }
  if (row + 1 < data.size()) {
    if (Check(data[row][col], data[row + 1][col])) {
      graph[GetNodeIndex(row, col, width)].push_back(
          GetNodeIndex(row + 1, col, width));
    }
  }
  if (col + 1 < data[row].size()) {
    if (Check(data[row][col], data[row][col + 1])) {
      graph[GetNodeIndex(row, col, width)].push_back(
          GetNodeIndex(row, col + 1, width));
    }
  }
  if (row > 0 && col > 0) {
    if (Check(data[row][col], data[row - 1][col - 1])) {
      graph[GetNodeIndex(row, col, width)].push_back(
          GetNodeIndex(row - 1, col - 1, width));
    }
  }
  if (row > 0 && col + 1 < data[row].size()) {
    if (Check(data[row][col], data[row - 1][col + 1])) {
      graph[GetNodeIndex(row, col, width)].push_back(
          GetNodeIndex(row - 1, col + 1, width));
    }
  }
  if (row + 1 < data.size() && col > 0) {
    if (Check(data[row][col], data[row + 1][col - 1])) {
      graph[GetNodeIndex(row, col, width)].push_back(
          GetNodeIndex(row + 1, col - 1, width));
    }
  }
  if (row + 1 < data.size() && col + 1 < data[row].size()) {
    if (Check(data[row][col], data[row + 1][col + 1])) {
      graph[GetNodeIndex(row, col, width)].push_back(
          GetNodeIndex(row + 1, col + 1, width));
    }
  }
}

void DFS(const Graph& g, size_t i, std::vector<int8_t>& lookup,
         std::vector<size_t>& res) {
  if (res.size() == 5) return;
  if (lookup[i]) return;
  lookup[i] = 1;
  res.push_back(i);

  for (size_t next : g[i]) {
    DFS(g, next, lookup, res);
  }

  if (res.size() < 5) {
    res.pop_back();
  }
  lookup[i] = 0;
}

std::vector<size_t> DoDFS(const Graph& g, const std::vector<size_t>& starts) {
  std::vector<int8_t> lookup(g.size());

  std::vector<size_t> res;
  res.reserve(5);
  for (size_t i : starts) {
    DFS(g, i, lookup, res);
    if (res.size() == 5) break;
  }
  return res;
}

std::vector<size_t> GetStarts(const Table& data) {
  std::vector<size_t> res;
  for (size_t i = 0; i < data.size(); ++i) {
    for (size_t j = 0; j < data[i].size(); ++j) {
      if (data[i][j] == 's') {
        res.push_back(GetNodeIndex(i, j, data[i].size()));
      }
    }
  }
  return res;
}

std::pair<size_t, size_t> FromIndex(size_t index, size_t width) {
  std::pair<size_t, size_t> res;
  res.first = index / width;
  res.second = index - res.first * width;
  return res;
}

std::vector<std::pair<size_t, size_t>> GetAnswer(
    const std::vector<size_t>& path, size_t width) {
  std::vector<std::pair<size_t, size_t>> res;
  res.reserve(path.size());
  for (size_t el : path) {
    res.push_back(FromIndex(el, width));
  }
  return res;
}

bool BuildE(const Table& data, size_t i, size_t j,
            std::vector<std::pair<size_t, size_t>>& res) {
  if (j + 5 > data[i].size()) return false;
  if (data[i][j + 1] == 'n' && data[i][j + 2] == 'u' && data[i][j + 3] == 'k' &&
      data[i][j + 4] == 'e') {
    res.push_back({i, j});
    res.push_back({i, j + 1});
    res.push_back({i, j + 2});
    res.push_back({i, j + 3});
    res.push_back({i, j + 4});
  }
  return res.size() == 5;
}

bool BuildW(const Table& data, size_t i, size_t j,
            std::vector<std::pair<size_t, size_t>>& res) {
  if (j < 4) return false;
  if (data[i][j - 1] == 'n' && data[i][j - 2] == 'u' && data[i][j - 3] == 'k' &&
      data[i][j - 4] == 'e') {
    res.push_back({i, j});
    res.push_back({i, j - 1});
    res.push_back({i, j - 2});
    res.push_back({i, j - 3});
    res.push_back({i, j - 4});
  }
  return res.size() == 5;
}

bool BuildN(const Table& data, size_t i, size_t j,
            std::vector<std::pair<size_t, size_t>>& res) {
  if (i < 4) return false;
  if (data[i - 1][j] == 'n' && data[i - 2][j] == 'u' && data[i - 3][j] == 'k' &&
      data[i - 4][j] == 'e') {
    res.push_back({i, j});
    res.push_back({i - 1, j});
    res.push_back({i - 2, j});
    res.push_back({i - 3, j});
    res.push_back({i - 4, j});
  }
  return res.size() == 5;
}

bool BuildNW(const Table& data, size_t i, size_t j,
             std::vector<std::pair<size_t, size_t>>& res) {
  if (i < 4 || j < 4) return false;
  if (data[i - 1][j - 1] == 'n' && data[i - 2][j - 2] == 'u' &&
      data[i - 3][j - 3] == 'k' && data[i - 4][j - 4] == 'e') {
    res.push_back({i, j});
    res.push_back({i - 1, j - 1});
    res.push_back({i - 2, j - 2});
    res.push_back({i - 3, j - 3});
    res.push_back({i - 4, j - 4});
  }
  return res.size() == 5;
}

bool BuildNE(const Table& data, size_t i, size_t j,
             std::vector<std::pair<size_t, size_t>>& res) {
  if (i < 4 || j + 5 > data.size()) return false;
  if (data[i - 1][j + 1] == 'n' && data[i - 2][j + 2] == 'u' &&
      data[i - 3][j + 3] == 'k' && data[i - 4][j + 4] == 'e') {
    res.push_back({i, j});
    res.push_back({i - 1, j + 1});
    res.push_back({i - 2, j + 2});
    res.push_back({i - 3, j + 3});
    res.push_back({i - 4, j + 4});
  }
  return res.size() == 5;
}

bool BuildS(const Table& data, size_t i, size_t j,
            std::vector<std::pair<size_t, size_t>>& res) {
  if (i + 5 > data.size()) return false;
  if (data[i + 1][j] == 'n' && data[i + 2][j] == 'u' && data[i + 3][j] == 'k' &&
      data[i + 4][j] == 'e') {
    res.push_back({i, j});
    res.push_back({i + 1, j});
    res.push_back({i + 2, j});
    res.push_back({i + 3, j});
    res.push_back({i + 4, j});
  }
  return res.size() == 5;
}

bool BuildSE(const Table& data, size_t i, size_t j,
             std::vector<std::pair<size_t, size_t>>& res) {
  if (i + 5 > data.size() || j + 5 > data.size()) return false;
  if (data[i + 1][j + 1] == 'n' && data[i + 2][j + 2] == 'u' &&
      data[i + 3][j + 3] == 'k' && data[i + 4][j + 4] == 'e') {
    res.push_back({i, j});
    res.push_back({i + 1, j + 1});
    res.push_back({i + 2, j + 2});
    res.push_back({i + 3, j + 3});
    res.push_back({i + 4, j + 4});
  }
  return res.size() == 5;
}

bool BuildSW(const Table& data, size_t i, size_t j,
             std::vector<std::pair<size_t, size_t>>& res) {
  if (i + 5 > data.size() || j < 4) return false;
  if (data[i + 1][j - 1] == 'n' && data[i + 2][j - 2] == 'u' &&
      data[i + 3][j - 3] == 'k' && data[i + 4][j - 4] == 'e') {
    res.push_back({i, j});
    res.push_back({i + 1, j - 1});
    res.push_back({i + 2, j - 2});
    res.push_back({i + 3, j - 3});
    res.push_back({i + 4, j - 4});
  }
  return res.size() == 5;
}

std::vector<std::pair<size_t, size_t>> BuildWord(const Table& data) {
  std::vector<std::pair<size_t, size_t>> res;
  res.reserve(5);
  for (size_t i = 0; i < data.size(); ++i) {
    for (size_t j = 0; j < data[i].size(); ++j) {
      if (data[i][j] == 's') {
        if (BuildE(data, i, j, res)) {
          return res;
        }
        if (BuildW(data, i, j, res)) {
          return res;
        }
        if (BuildN(data, i, j, res)) {
          return res;
        }
        if (BuildS(data, i, j, res)) {
          return res;
        }
        if (BuildNW(data, i, j, res)) {
          return res;
        }
        if (BuildNE(data, i, j, res)) {
          return res;
        }
        if (BuildSE(data, i, j, res)) {
          return res;
        }
        if (BuildSW(data, i, j, res)) {
          return res;
        }
        res.clear();
      }
    }
  }
  return res;
}

void Solution(std::istream& input) {
  int h, w;
  input >> h >> w;
  Table table(h);
  for (auto& el : table) {
    input >> el;
  }

  //   Graph graph(h * w);
  //   for (size_t r = 0; r < h; ++r) {
  //     for (size_t c = 0; c < w; ++c) {
  //       AddToGraph(table, r, c, graph, w);
  //     }
  //   }

  //   std::vector<size_t> path = DoDFS(graph, GetStarts(table));
  //   std::vector<std::pair<size_t, size_t>> ans = GetAnswer(path, w);

  auto ans = BuildWord(table);

  for (const auto& el : ans) {
    std::cout << el.first + 1 << ' ' << el.second + 1 << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6 6
vgxgpu
amkxks
zhkbpp
hykink
esnuke
zplvfj
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(5 5
ezzzz
zkzzz
ezuzs
zzznz
zzzzs
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(10 10
kseeusenuk
usesenesnn
kskekeeses
nesnusnkkn
snenuuenke
kukknkeuss
neunnennue
sknuessuku
nksneekknk
neeeuknenk
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
