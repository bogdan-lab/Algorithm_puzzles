#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

int ToInt(char c) { return static_cast<int>(c) - static_cast<int>('a'); }

struct Node {
  Node() : children(ToInt('z') + 1, nullptr) {}
  bool is_word_end = false;
  std::vector<Node*> children;
};

Node* BuildTrie(const std::vector<std::string>& wordDict) {
  Node* root = new Node();
  for (const auto& word : wordDict) {
    Node* curr = root;
    for (const auto& c : word) {
      int index = ToInt(c);
      if (!curr->children[index]) {
        curr->children[index] = new Node();
      }
      curr = curr->children[index];
    }
    curr->is_word_end = true;
  }
  return root;
}

std::string AddToPrefix(const std::string& prefix, std::string_view word) {
  std::string res;
  if (prefix.empty()) {
    res = std::string(word);
  } else {
    res.reserve(prefix.size() + word.size() + 1);
    res = prefix + " " + std::string(word);
  }
  return res;
}

std::vector<std::string> BuildSentences(std::string prefix,
                                        std::string_view suffix, Node* root) {
  std::vector<std::string> res;
  Node* par = root;
  for (int i = 0; i < suffix.size(); ++i) {
    int index = ToInt(suffix[i]);
    if (!par->children[index]) {
      break;
    } else {
      par = par->children[index];
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
    return BuildSentences("", s, BuildTrie(wordDict));
  }
};
