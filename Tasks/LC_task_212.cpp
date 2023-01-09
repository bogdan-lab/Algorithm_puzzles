#include <string>
#include <utility>
#include <vector>

int ToInt(char c) { return static_cast<int>(c) - static_cast<int>('a'); }

bool DFS(const std::vector<std::vector<char>>& board, const std::string& word,
         int wi, int i, int j, std::vector<std::vector<int>>& lookup) {
  if (wi >= word.size()) return true;
  if (i < 0 || i >= board.size() || j < 0 || j >= board[i].size()) return false;
  if (lookup[i][j] || word[wi] != board[i][j]) return false;

  lookup[i][j] = 1;

  ++wi;
  if (DFS(board, word, wi, i - 1, j, lookup)) {
    return true;
  }
  if (DFS(board, word, wi, i, j + 1, lookup)) {
    return true;
  }
  if (DFS(board, word, wi, i + 1, j, lookup)) {
    return true;
  }
  if (DFS(board, word, wi, i, j - 1, lookup)) {
    return true;
  }
  lookup[i][j] = 0;
  return false;
}

bool IsIn(const std::vector<std::vector<char>>& board, const std::string& w,
          int i, int j) {
  int n = board.size();
  int m = board[0].size();
  std::vector<std::vector<int>> lookup(n, std::vector<int>(m));
  return DFS(board, w, 0, i, j, lookup);
}

class Solution {
 public:
  std::vector<std::string> findWords(std::vector<std::vector<char>>& board,
                                     std::vector<std::string>& words) {
    std::vector<std::vector<std::pair<int, int>>> mp(ToInt('z') + 1);
    for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board[i].size(); ++j) {
        mp[ToInt(board[i][j])].push_back({i, j});
      }
    }

    std::vector<std::string> res;

    for (const auto& w : words) {
      for (const auto& [i, j] : mp[ToInt(w.front())]) {
        if (IsIn(board, w, i, j)) {
          res.push_back(w);
          break;
        }
      }
    }

    return res;
  }
};
