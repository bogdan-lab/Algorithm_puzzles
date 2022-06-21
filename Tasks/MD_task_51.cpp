#include <string>
#include <utility>
#include <vector>

std::vector<std::string> CreateEmptyBoard(int n);
bool CheckPos(const std::vector<std::string>& board, int row, int col);

void BuildBoards(std::vector<std::vector<std::string>>& sol_boards,
                 std::vector<std::string>& curr_board, int curr_row,
                 int curr_col);

class Solution {
 public:
  std::vector<std::vector<std::string>> solveNQueens(int n) {
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> initial_board = CreateEmptyBoard(n);
    for (int col = 0; col < n; ++col) {
      BuildBoards(result, initial_board, 0, col);
    }
    return result;
  }
};

std::vector<std::string> CreateEmptyBoard(int n) {
  return std::vector<std::string>(n, std::string(n, '.'));
}

void BuildBoards(std::vector<std::vector<std::string>>& sol_boards,
                 std::vector<std::string>& curr_board, int curr_row,
                 int curr_col) {
  if (!CheckPos(curr_board, curr_row, curr_col)) {
    return;
  }
  curr_board[curr_row][curr_col] = 'Q';
  if (curr_row == curr_board.size() - 1) {
    sol_boards.push_back(curr_board);
  } else {
    int new_row = curr_row + 1;
    for (int i = 0; i < curr_board.size(); ++i) {
      BuildBoards(sol_boards, curr_board, new_row, i);
    }
  }
  curr_board[curr_row][curr_col] = '.';
}

bool CheckPos(const std::vector<std::string>& board, int row, int col) {
  // I know the order of recursion -> use it
  for (int i = 0; i < row; ++i) {
    if (board[i][col] == 'Q') return false;
  }
  int curr_row = row - 1;
  int curr_col = col - 1;
  while (curr_row >= 0 && curr_col >= 0) {
    if (board[curr_row][curr_col] == 'Q') return false;
    --curr_row;
    --curr_col;
  }
  curr_row = row - 1;
  curr_col = col + 1;
  while (curr_row >= 0 && curr_col < board.size()) {
    if (board[curr_row][curr_col] == 'Q') return false;
    --curr_row;
    ++curr_col;
  }
  return true;
}