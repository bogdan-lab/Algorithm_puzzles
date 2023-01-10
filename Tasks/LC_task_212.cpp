#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

int ToInt(char c) { return static_cast<int>(c) - static_cast<int>('a'); }

struct Node {
  explicit Node(char gc) : c(gc), children(ToInt('z') + 1) {}
  char c;
  bool is_word_end = false;
  std::vector<Node*> children;
};

Node* BuildTrie(const std::vector<std::string>& words) {
  Node* root = new Node('\0');
  for (const auto& word : words) {
    Node* curr = root;
    for (const auto& c : word) {
      int cv = ToInt(c);
      if (!curr->children[cv]) {
        curr->children[cv] = new Node(c);
      }
      curr = curr->children[cv];
    }
    curr->is_word_end = true;
  }
  return root;
}

void DeleteTrie(Node* node) {
  if (!node) return;
  for (int i = 0; i < node->children.size(); ++i) {
    DeleteTrie(node->children[i]);
  }
  delete node;
}

void DFS(const std::vector<std::vector<char>>& board, const Node* node, int i,
         int j, std::unordered_set<std::string>& acc,
         std::vector<std::vector<int>>& lookup, std::string& curr_word) {
  if (!node) return;
  if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) return;
  if (lookup[i][j]) return;
  if (board[i][j] != node->c) return;

  lookup[i][j] = 1;

  curr_word.push_back(node->c);
  if (node->is_word_end) {
    acc.insert(curr_word);
  }

  if (i > 0) {
    char top = board[i - 1][j];
    DFS(board, node->children[ToInt(top)], i - 1, j, acc, lookup, curr_word);
  }
  if (j > 0) {
    char left = board[i][j - 1];
    DFS(board, node->children[ToInt(left)], i, j - 1, acc, lookup, curr_word);
  }
  if (i + 1 < board.size()) {
    char bot = board[i + 1][j];
    DFS(board, node->children[ToInt(bot)], i + 1, j, acc, lookup, curr_word);
  }
  if (j + 1 < board[0].size()) {
    char right = board[i][j + 1];
    DFS(board, node->children[ToInt(right)], i, j + 1, acc, lookup, curr_word);
  }

  lookup[i][j] = 0;
  curr_word.pop_back();
}

void AccumulateWords(const std::vector<std::vector<char>>& board,
                     const Node* root, int i, int j,
                     std::unordered_set<std::string>& acc) {
  std::vector<std::vector<int>> lookup(board.size(),
                                       std::vector<int>(board[0].size()));
  std::string curr_word;
  DFS(board, root->children[ToInt(board[i][j])], i, j, acc, lookup, curr_word);
}

class Solution {
 public:
  std::vector<std::string> findWords(std::vector<std::vector<char>>& board,
                                     std::vector<std::string>& words) {
    Node* trie = BuildTrie(words);
    std::unordered_set<std::string> acc;
    for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board[0].size(); ++j) {
        AccumulateWords(board, trie, i, j, acc);
      }
    }

    DeleteTrie(trie);
    return std::vector<std::string>(acc.begin(), acc.end());
  }
};

void PrintWords(const std::vector<std::string>& data) {
  for (const auto& el : data) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

int main() {
  Solution s;
  {
    std::cout << "NEW CASE\n";
    std::vector<std::vector<char>> board{{'a'}};
    std::vector<std::string> words{"a"};
    PrintWords(s.findWords(board, words));
  }
  {
    std::cout << "NEW CASE\n";
    std::vector<std::vector<char>> board{{'o', 'a', 'a', 'n'},
                                         {'e', 't', 'a', 'e'},
                                         {'i', 'h', 'k', 'r'},
                                         {'i', 'f', 'l', 'v'}};
    std::vector<std::string> words{"oath", "pea", "eat", "rain"};
    PrintWords(s.findWords(board, words));
  }
}
