#include <algorithm>
#include <bitset>
#include <limits>
#include <vector>

constexpr int kEmptyValue = 0;

struct Cell {
  Cell() { count_map.flip(); }
  Cell(int val) : count(1), value(val) { count_map.flip(value - 1); }

  void CrossValue(int val) {
    --val;
    if (!count_map.test(val)) return;
    count_map.flip(val);
    --count;
    if (count == 1) {
      value = 0;
      while (!count_map.test(value)) {
        ++value;
      }
      ++value;  // since index starts from 0
    }
  }

  int count = 9;
  int value = kEmptyValue;
  std::bitset<9> count_map;
};

int ToInt(char ch);
char ToChar(int val);
std::vector<std::vector<Cell>> ParseBoard(
    const std::vector<std::vector<char>>& board);
std::vector<std::vector<int>> CreateChecked();
void CheckValue(std::vector<std::vector<Cell>>& data, int i, int j,
                std::vector<std::vector<int>>& checked);
std::vector<std::vector<char>> ConvertToChar(
    const std::vector<std::vector<Cell>>& board);

class Solution {
 public:
  void solveSudoku(std::vector<std::vector<char>>& board) {
    std::vector<std::vector<Cell>> parsed = ParseBoard(board);
    std::vector<std::vector<int>> checked = CreateChecked();

    for (size_t i = 0; i < parsed.size(); ++i) {
      for (size_t j = 0; j < parsed[i].size(); ++j) {
        CheckValue(parsed, i, j, checked);
      }
    }

    board = ConvertToChar(parsed);
  }
};

int ToInt(char ch) { return static_cast<int>(ch) - static_cast<int>('0'); }
char ToChar(int val) { return static_cast<char>(static_cast<int>('0') + val); }

std::vector<std::vector<Cell>> ParseBoard(
    const std::vector<std::vector<char>>& board) {
  std::vector<std::vector<Cell>> result;
  result.reserve(board.size());
  for (size_t i = 0; i < board.size(); ++i) {
    result.push_back({});
    result.back().reserve(board[i].size());
    for (size_t j = 0; j < board[i].size(); ++j) {
      if (board[i][j] == '.') {
        result.back().push_back(Cell{});
      } else {
        result.back().push_back(Cell{ToInt(board[i][j])});
      }
    }
  }
  return result;
}

std::vector<std::vector<int>> CreateChecked() {
  std::vector<std::vector<int>> result(9);
  for (auto& el : result) {
    el.resize(9);
  }
  return result;
}

void CheckValue(std::vector<std::vector<Cell>>& data, int row, int col,
                std::vector<std::vector<int>>& checked) {
  if (checked[row][col] || data[row][col].value == kEmptyValue) return;
  checked[row][col] = 1;
  // check in the column
  for (size_t i = 0; i < data.size(); ++i) {
    data[i][col].CrossValue(data[row][col].value);
    CheckValue(data, i, col, checked);
  }
  // check in the row
  for (size_t j = 0; j < data[row].size(); ++j) {
    data[row][j].CrossValue(data[row][col].value);
    CheckValue(data, row, j, checked);
  }
  // check in square
  int s_row = row / 3;
  int s_col = col / 3;
  for (int i = s_row * 3; i < s_row * 3 + 3; ++i) {
    for (int j = s_col * 3; j < s_col * 3 + 3; ++j) {
      data[i][j].CrossValue(data[row][col].value);
      CheckValue(data, i, j, checked);
    }
  }
}

std::vector<std::vector<char>> ConvertToChar(
    const std::vector<std::vector<Cell>>& board) {
  std::vector<std::vector<char>> result;
  result.reserve(board.size());
  for (size_t i = 0; i < board.size(); ++i) {
    result.emplace_back();
    result.back().reserve(board[i].size());
    for (size_t j = 0; j < board[i].size(); ++j) {
      result.back().push_back(ToChar(board[i][j].value));
    }
  }
  return result;
}

int main() {
  std::vector<std::vector<char>> input{
      {'.', '.', '9', '7', '4', '8', '.', '.', '.'},
      {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '2', '.', '1', '.', '9', '.', '.', '.'},
      {'.', '.', '7', '.', '.', '.', '2', '4', '.'},
      {'.', '6', '4', '.', '1', '.', '5', '9', '.'},
      {'.', '9', '8', '.', '.', '.', '3', '.', '.'},
      {'.', '.', '.', '8', '.', '3', '.', '2', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '6'},
      {'.', '.', '.', '2', '7', '5', '9', '.', '.'}};
  Solution().solveSudoku(input);
  return 0;
}
