#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

constexpr int NEG_INF = std::numeric_limits<int>::min();

struct Point {
  size_t row = 0;
  size_t col = 0;
};

template <typename T>
using Grid = std::vector<std::vector<T>>;

template <typename T>
Grid<T> MakeGrid(size_t row_num, size_t col_num, T value) {
  Grid<T> result(row_num);
  for (auto& el : result) {
    el.resize(col_num, value);
  }
  return result;
}

void Solution(std::istream& input = std::cin);
void RunTests();

std::string GetPath(const Grid<Point>& parents);

int main() {
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n;
  int m;
  input >> n >> m;
  Grid<int> prices = MakeGrid(n, m, 0);
  for (auto& row : prices) {
    for (auto& el : row) {
      input >> el;
    }
  }
  Grid<int> max_income = MakeGrid(n, m, 0);
  Grid<Point> parents = MakeGrid(n, m, Point());

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      int prev_price = NEG_INF;
      if (j > 0 && prev_price < max_income[i][j - 1]) {
        prev_price = max_income[i][j - 1];
        parents[i][j] = {.row = i, .col = j - 1};
      }
      if (i > 0 && prev_price < max_income[i - 1][j]) {
        prev_price = max_income[i - 1][j];
        parents[i][j] = {.row = i - 1, .col = j};
      }
      if (prev_price == NEG_INF) {
        prev_price = 0;
      }
      max_income[i][j] = prev_price + prices[i][j];
    }
  }

  std::cout << max_income.back().back() << '\n' << GetPath(parents) << '\n';
}

std::string GetPath(const Grid<Point>& parents) {
  std::string result(parents.size() + parents.front().size() - 2, '\0');
  Point prev_value{parents.size() - 1, parents.front().size() - 1};
  Point curr_value = parents.back().back();
  for (auto& el : result) {
    el = prev_value.row == curr_value.row ? 'R' : 'D';
    prev_value = curr_value;
    curr_value = parents[curr_value.row][curr_value.col];
  }
  std::reverse(result.begin(), result.end());
  return result;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 3
0 2 -3
2 -5 7
1 2 0
)";
    Solution(ss);
    std::cout << "expected = 6; RRDD\n";
  }
  {
    std::stringstream ss;
    ss << R"(4 5
4 5 3 2 9
4 6 7 5 9
5 2 5 -3 -10
3 5 2 9 3
)";
    Solution(ss);
    std::cout << "expected = 41; RDRDDRR\n";
  }
}
