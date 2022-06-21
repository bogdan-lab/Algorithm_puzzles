#include <string>
#include <utility>
#include <vector>

std::vector<std::string> CreateEmptyBoard(int n);
std::vector<std::vector<int>> CreateEmptyMap(int n);

void PlaceQueen(std::vector<std::string>& board,
                std::vector<std::vector<int>>& map, int row, int col);

void BuildBoards(std::vector<std::vector<std::string>>& sol_boards,
                 std::vector<std::string> curr_board,
                 std::vector<std::vector<int>> curr_map, int curr_row,
                 int curr_col);

class Solution {
 public:
  std::vector<std::vector<std::string>> solveNQueens(int n) {
    std::vector<std::vector<std::string>> result;
    for (int col = 0; col < n; ++col) {
      BuildBoards(result, CreateEmptyBoard(n), CreateEmptyMap(n), 0, col);
    }
    return result;
  }
};

std::vector<std::string> CreateEmptyBoard(int n) {
  return std::vector<std::string>(n, std::string(n, '.'));
}

std::vector<std::vector<int>> CreateEmptyMap(int n) {
  return std::vector<std::vector<int>>(n, std::vector<int>(n));
}

void BuildBoards(std::vector<std::vector<std::string>>& sol_boards,
                 std::vector<std::string> curr_board,
                 std::vector<std::vector<int>> curr_map, int curr_row,
                 int curr_col) {
  if (curr_map[curr_row][curr_col]) {
    return;
  }
  PlaceQueen(curr_board, curr_map, curr_row, curr_col);
  if (curr_row == curr_board.size() - 1) {
    sol_boards.push_back(std::move(curr_board));
    return;
  }
  ++curr_row;
  for (int i = 0; i < curr_board.size(); ++i) {
    BuildBoards(sol_boards, curr_board, curr_map, curr_row, i);
  }
}

void PlaceQueen(std::vector<std::string>& board,
                std::vector<std::vector<int>>& map, int row, int col) {
  board[row][col] = 'Q';
  for (int i = 0; i < map.size(); ++i) {
    map[row][i] = 1;
  }
  for (int i = 0; i < map.size(); ++i) {
    map[i][col] = 1;
  }
  int curr_row = row;
  int curr_col = col;
  while (curr_row < map.size() && curr_col < map.size()) {
    map[curr_row][curr_col] = 1;
    ++curr_row;
    ++curr_col;
  }
  curr_row = row;
  curr_col = col;
  while (curr_row >= 0 && curr_col >= 0) {
    map[curr_row][curr_col] = 1;
    --curr_row;
    --curr_col;
  }
  curr_row = row;
  curr_col = col;
  while (curr_row >= 0 && curr_col < map.size()) {
    map[curr_row][curr_col] = 1;
    --curr_row;
    ++curr_col;
  }
  curr_row = row;
  curr_col = col;
  while (curr_row < map.size() && curr_col >= 0) {
    map[curr_row][curr_col] = 1;
    ++curr_row;
    --curr_col;
  }
}