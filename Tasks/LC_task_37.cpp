#include <algorithm>
#include <vector>

bool CanPut(const std::vector<std::vector<char>>& board, int row, int col,
            char c);

bool FillBoard(std::vector<std::vector<char>>& board, int row, int col);

class Solution {
 public:
  void solveSudoku(std::vector<std::vector<char>>& board) {
    FillBoard(board, 0, 0);
  }
};

bool CanPut(const std::vector<std::vector<char>>& board, int row, int col,
            char c) {
  // Check row
  auto it = std::find(board[row].begin(), board[row].end(), c);
  if (it != board[row].end()) {
    return false;
  }
  // Check column
  for (int i = 0; i < board[row].size(); ++i) {
    if (board[i][col] == c) {
      return false;
    }
  }
  // Check square
  int r_start = (row / 3) * 3;
  int c_start = (col / 3) * 3;
  for (int i = r_start; i < r_start + 3; ++i) {
    for (int j = c_start; j < c_start + 3; ++j) {
      if (board[i][j] == c) {
        return false;
      }
    }
  }
  return true;
}

bool FillBoard(std::vector<std::vector<char>>& board, int row, int col) {
  // We will fill row by row
  if (row == board.size()) return true;
  if (col == board.size()) {
    return FillBoard(board, row + 1, 0);
  }
  if (board[row][col] != '.') {
    return FillBoard(board, row, col + 1);
  }
  // Here we have empty cell - have to put something inside
  for (char c = '1'; c <= '9'; ++c) {
    if (CanPut(board, row, col, c)) {
      board[row][col] = c;
      if (!FillBoard(board, row, col + 1)) {
        board[row][col] = '.';
      } else {
        return true;
      }
    }
  }
  return false;
}

int main() { return 0; }
