#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Node {
  char curr_char = '\0';
  std::vector<Node*> next;
  int word_end_id = -1;
};

void Solution(std::istream& input = std::cin);
void RunTests();

Node* BuildBor(const std::vector<std::string>& words);

void CheckBor(const std::string& text, int begin, Node* root,
              std::vector<int>& count);

void DeleteBor(Node* bor);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  std::string text;
  input >> text;
  int n;
  input >> n;
  std::vector<std::string> words(n);
  for (auto& el : words) {
    input >> el;
  }

  Node* bor = BuildBor(words);
  std::vector<int> count(words.size());
  for (int i = 0; i < text.size(); ++i) {
    CheckBor(text, i, bor, count);
  }

  for (const auto& el : count) {
    std::cout << (el ? "Yes\n" : "No\n");
  }

  DeleteBor(bor);
}

void DeleteBor(Node* bor) {
  for (auto* node : bor->next) {
    DeleteBor(node);
  }
  delete bor;
}

void CheckBor(const std::string& text, int begin, Node* root,
              std::vector<int>& count) {
  while (begin < text.size()) {
    auto it = std::lower_bound(
        root->next.begin(), root->next.end(), text[begin],
        [](const Node* n, char c) { return n->curr_char < c; });
    if (it == root->next.end() || (*it)->curr_char != text[begin]) {
      return;
    }
    root = *it;
    if (root->word_end_id != -1) {
      count[root->word_end_id]++;
    }
    ++begin;
  }
}

Node* BuildBor(const std::vector<std::string>& words) {
  Node* root = new Node;
  int word_id = 0;
  for (const auto& w : words) {
    Node* curr_node = root;
    for (char c : w) {
      if (curr_node->next.empty() || curr_node->next.back()->curr_char != c) {
        curr_node->next.push_back(new Node);
        curr_node->next.back()->curr_char = c;
      }
      curr_node = curr_node->next.back();
    }
    curr_node->word_end_id = word_id++;
  }
  return root;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(trololo
3
abacabadabacaba
olo
trol
)";
    Solution(ss);
    std::cout << "expected = No; Yes; Yes\n";
  }
}
