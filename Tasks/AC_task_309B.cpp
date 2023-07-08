#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

constexpr int kFinalValue = 2;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

int DoFirstRow(int curr_val, int row, int col,
               std::vector<std::vector<int>>& data) {
  while (col < data.size()) {
    std::swap(data[row][col], curr_val);
    ++col;
  }
  return curr_val;
}

int DoRightColumn(int curr_val, int row, int col,
                  std::vector<std::vector<int>>& data) {
  while (row < data.size()) {
    std::swap(data[row][col], curr_val);
    ++row;
  }
  return curr_val;
}

int DoBottomRow(int curr_val, int row, int col,
                std::vector<std::vector<int>>& data) {
  while (col > 0) {
    std::swap(data[row][col], curr_val);
    --col;
  }
  return curr_val;
}

int DoLeftColumn(int curr_val, int row, int col,
                 std::vector<std::vector<int>>& data) {
  while (row >= 0) {
    std::swap(data[row][col], curr_val);
    --row;
  }
  return curr_val;
}

void Solution(std::istream& input) {
  int n;
  input >> n;

  std::vector<std::string> tmp(n);
  for (auto& el : tmp) {
    input >> el;
  }

  std::vector<std::vector<int>> data(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      data[i][j] = tmp[i][j] == '0' ? 0 : 1;
    }
  }

  int curr_val = data[0][0];
  data[0][0] = kFinalValue;

  curr_val = DoFirstRow(curr_val, 0, 1, data);
  curr_val = DoRightColumn(curr_val, 1, data.size() - 1, data);
  curr_val = DoBottomRow(curr_val, data.size() - 1, data.size() - 2, data);
  curr_val = DoLeftColumn(curr_val, data.size() - 1, 0, data);

  for (const auto& row : data) {
    for (const auto& el : row) {
      std::cout << el;
    }
    std::cout << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
