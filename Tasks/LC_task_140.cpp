#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

struct Node {
  Node() = default;
  explicit Node(char gc) : c(gc) {}
  char c = '\0';
  bool is_word_end = false;
  std::vector<Node*> children;
};

Node* BuildTrie(const std::vector<std::string>& wordDict) {
  Node* root = new Node();
  for (const auto& word : wordDict) {
    Node* curr = root;
    for (const auto& c : word) {
      auto it = std::find_if(curr->children.begin(), curr->children.end(),
                             [&](const Node* n) { return c == n->c; });
      if (it == curr->children.end()) {
        curr->children.push_back(new Node(c));
        it = std::prev(curr->children.end());
      }
      curr = *it;
    }
    curr->is_word_end = true;
  }
  return root;
}

std::string AddToPrefix(const std::string& prefix, std::string_view word) {
  if (prefix.empty()) {
    return prefix + std::string(word);
  }
  return prefix + " " + std::string(word);
}

std::vector<std::string> BuildSentences(std::string prefix,
                                        std::string_view suffix, Node* root) {
  std::vector<std::string> res;
  Node* par = root;
  for (int i = 0; i < suffix.size(); ++i) {
    auto it = std::find_if(par->children.begin(), par->children.end(),
                           [&](const Node* n) { return n->c == suffix[i]; });
    if (it == par->children.end()) {
      break;
    } else {
      par = *it;
      if (par->is_word_end && i + 1 < suffix.size()) {
        std::vector<std::string> sub_res =
            BuildSentences(AddToPrefix(prefix, suffix.substr(0, i + 1)),
                           suffix.substr(i + 1, std::string_view::npos), root);
        std::move(sub_res.begin(), sub_res.end(), std::back_inserter(res));
      } else if (par->is_word_end && i + 1 == suffix.size()) {
        res.push_back(AddToPrefix(prefix, suffix));
      }
    }
  }
  return res;
}

class Solution {
 public:
  std::vector<std::string> wordBreak(std::string s,
                                     std::vector<std::string>& wordDict) {
    Node* root = BuildTrie(wordDict);
    return BuildSentences("", s, root);
  }
};
