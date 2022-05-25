#include <algorithm>
#include <bitset>
#include <iostream>
#include <limits>
#include <vector>

constexpr int kEmptyValue = 0;

class Cell {
 public:
  Cell() { count_map.flip(); }
  Cell(int val) : value(val) { count_map.flip(value - 1); }

  void CrossValue(int val) {
    if (IsDefined()) return;
    --val;
    if (!count_map.test(val)) return;
    count_map.set(val, false);
    TrySetValue(count_map);
  }

  bool TrySetValue(std::bitset<9> map) {
    if (map.count() != 1) return false;
    count_map = map;
    value = 0;
    while (!count_map.test(value)) {
      ++value;
    }
    ++value;  // since index starts from 0
    return true;
  }

  // true points to the number which CAN be placed in the cell
  std::bitset<9> GetCountMap() const { return count_map; }
  int GetValue() const { return value; }
  bool IsDefined() const { return value != kEmptyValue; }

 private:
  int value = kEmptyValue;
  std::bitset<9> count_map;
};

int ToInt(char ch);
char ToChar(int val);
std::vector<std::vector<Cell>> ParseBoard(
    const std::vector<std::vector<char>>& board);
std::vector<std::vector<int>> CreateChecked();
void CheckValue(std::vector<std::vector<Cell>>& data, int i, int j,
                std::vector<std::vector<int>>& checked, int& count);
bool CheckCrossection(std::vector<std::vector<Cell>>& data, int row, int col);
std::vector<std::vector<char>> ConvertToChar(
    const std::vector<std::vector<Cell>>& board);

class Solution {
 public:
  void solveSudoku(std::vector<std::vector<char>>& board) {
    std::vector<std::vector<Cell>> parsed = ParseBoard(board);
    std::vector<std::vector<int>> checked = CreateChecked();

    int count = 0;
    // Check all defined values
    for (size_t i = 0; i < parsed.size(); ++i) {
      for (size_t j = 0; j < parsed[i].size(); ++j) {
        CheckValue(parsed, i, j, checked, count);
      }
    }
    while (count < 81) {
      // Check undefined
      for (size_t i = 0; i < parsed.size(); ++i) {
        for (size_t j = 0; j < parsed[i].size(); ++j) {
          if (!checked[i][j]) {
            if (CheckCrossection(parsed, i, j)) {
              CheckValue(parsed, i, j, checked, count);
            }
          }
        }
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
                std::vector<std::vector<int>>& checked, int& count) {
  if (checked[row][col] || !data[row][col].IsDefined()) return;
  checked[row][col] = 1;
  ++count;
  // check in the column
  for (size_t i = 0; i < data.size(); ++i) {
    data[i][col].CrossValue(data[row][col].GetValue());
    CheckValue(data, i, col, checked, count);
  }
  // check in the row
  for (size_t j = 0; j < data[row].size(); ++j) {
    data[row][j].CrossValue(data[row][col].GetValue());
    CheckValue(data, row, j, checked, count);
  }
  // check in square
  int s_row = row / 3;
  int s_col = col / 3;
  for (int i = s_row * 3; i < s_row * 3 + 3; ++i) {
    for (int j = s_col * 3; j < s_col * 3 + 3; ++j) {
      data[i][j].CrossValue(data[row][col].GetValue());
      CheckValue(data, i, j, checked, count);
    }
  }
}

// Should be called only for not checked cells!
bool CheckCrossection(std::vector<std::vector<Cell>>& data, int row, int col) {
  std::bitset<9> remainder;
  for (size_t i = 0; i < data.size(); ++i) {
    if (i != row) {
      remainder |= data[i][col].GetCountMap();
    }
  }
  remainder.flip();
  auto curr = data[row][col].GetCountMap();
  if (data[row][col].TrySetValue(curr & remainder)) {
    return true;
  }
  remainder.reset();
  for (size_t j = 0; j < data.size(); ++j) {
    if (j != col) {
      remainder |= data[row][j].GetCountMap();
    }
  }
  remainder.flip();
  if (data[row][col].TrySetValue(curr & remainder)) {
    return true;
  }
  remainder.reset();
  int s_row = row / 3;
  int s_col = col / 3;
  for (int i = s_row * 3; i < s_row * 3 + 3; ++i) {
    for (int j = s_col * 3; j < s_col * 3 + 3; ++j) {
      if (i != row || j != col) {
        remainder |= data[i][j].GetCountMap();
      }
    }
  }
  remainder.flip();
  if (data[row][col].TrySetValue(curr & remainder)) {
    return true;
  }
  return false;
}

std::vector<std::vector<char>> ConvertToChar(
    const std::vector<std::vector<Cell>>& board) {
  std::vector<std::vector<char>> result;
  result.reserve(board.size());
  for (size_t i = 0; i < board.size(); ++i) {
    result.emplace_back();
    result.back().reserve(board[i].size());
    for (size_t j = 0; j < board[i].size(); ++j) {
      result.back().push_back(ToChar(board[i][j].GetValue()));
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
