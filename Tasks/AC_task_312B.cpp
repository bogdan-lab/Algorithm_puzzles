#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //   RunTests();
  Solution(std::cin);
  return 0;
}

bool CheckColor(size_t itl, size_t jtl, size_t ibr, size_t jbr,
                const std::vector<std::string>& data, char color) {
  for (size_t i = itl; i <= ibr; ++i) {
    for (size_t j = jtl; j <= jbr; ++j) {
      if (data[i][j] != color) {
        return false;
      }
    }
  }

  return true;
}

bool CheckTopLeft(size_t i, size_t j, const std::vector<std::string>& data) {
  if (i + 8 >= data.size()) {
    return false;
  }
  if (j + 8 >= data.front().size()) {
    return false;
  }

  if (!CheckColor(i, j, i + 2, j + 2, data, '#')) {
    return false;
  }

  if (!CheckColor(i + 3, j, i + 3, j + 3, data, '.')) {
    return false;
  }

  if (!CheckColor(i, j + 3, i + 3, j + 3, data, '.')) {
    return false;
  }

  size_t ni = i + 6;
  size_t nj = j + 6;
  if (!CheckColor(ni, nj, ni + 2, nj + 2, data, '#')) {
    return false;
  }

  if (!CheckColor(ni - 1, nj - 1, ni - 1, nj + 2, data, '.')) {
    return false;
  }

  if (!CheckColor(ni - 1, nj - 1, ni + 2, nj - 1, data, '.')) {
    return false;
  }

  return true;
}

void Solution(std::istream& input) {
  int n, m;
  input >> n >> m;

  std::vector<std::string> data(n);
  for (auto& el : data) {
    input >> el;
  }

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      if (CheckTopLeft(i, j, data)) {
        std::cout << i + 1 << ' ' << j + 1 << '\n';
      }
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(19 18
###......###......
###......###......
###..#...###..#...
..............#...
..................
..................
......###......###
......###......###
......###......###
.###..............
.###......##......
.###..............
............###...
...##.......###...
...##.......###...
.......###........
.......###........
.......###........
........#.........
    )";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
