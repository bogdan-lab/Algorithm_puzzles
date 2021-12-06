#include <iostream>
#include <limits>
#include <sstream>
#include <string>

void Solution(std::istream& input = std::cin);
void RunTests();

class SimpleSearchTree {
 public:
  struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    int key;

    Node(int k) : key(k) {}
  };

  SimpleSearchTree() = default;
  SimpleSearchTree(const SimpleSearchTree&) = delete;
  SimpleSearchTree& operator=(const SimpleSearchTree&) = delete;
  SimpleSearchTree(SimpleSearchTree&&) = delete;
  SimpleSearchTree& operator=(SimpleSearchTree&&) = delete;
  ~SimpleSearchTree() {
    if (!head_) return;
    DeleteTree(head_);
  }

  bool Insert(int key) {
    if (!head_) {
      head_ = new Node(key);
      return true;
    }
    Node* curr_node = head_;
    while (true) {
      if (key < curr_node->key) {
        if (!curr_node->left) {
          curr_node->left = new Node(key);
          return true;
        }
        curr_node = curr_node->left;
      } else if (curr_node->key < key) {
        if (!curr_node->right) {
          curr_node->right = new Node(key);
          return true;
        }
        curr_node = curr_node->right;
      } else {
        return false;
      }
    }
  }

  bool Delete(int key) {
    Node* parent = nullptr;
    auto* curr_node = head_;
    while (curr_node) {
      auto* tmp = curr_node;
      if (key < curr_node->key) {
        curr_node = curr_node->left;
      } else if (curr_node->key < key) {
        curr_node = curr_node->right;
      } else {
        return DeleteNode(parent, curr_node);
      }
      parent = tmp;
    }
    return false;
  }

  bool Exists(const int& key) const { return FindNode(key); }

  Node* Next(const int& key) {
    auto* curr_node = head_;
    Node* max_node = nullptr;
    while (curr_node) {
      if (key < curr_node->key) {
        max_node = curr_node;
        curr_node = curr_node->left;
      } else if (curr_node->key < key) {
        curr_node = curr_node->right;
      } else {
        return curr_node->right ? FindMinimum(curr_node->right) : max_node;
      }
    }
    return max_node;
  }

  Node* Prev(const int& key) {
    auto* curr_node = head_;
    Node* min_node = nullptr;
    while (curr_node) {
      if (key < curr_node->key) {
        curr_node = curr_node->left;
      } else if (curr_node->key < key) {
        min_node = curr_node;
        curr_node = curr_node->right;
      } else {
        return curr_node->left ? FindMaximum(curr_node->left) : min_node;
      }
    }
    return min_node;
  }

 private:
  void DeleteLeafNode(Node* parent, Node* leaf_node) {
    if (leaf_node != head_) {
      if (leaf_node->key < parent->key) {
        parent->left = nullptr;
      } else {
        parent->right = nullptr;
      }
    } else {
      head_ = nullptr;
    }
    delete leaf_node;
  }

  void DeleteHalfTreeHead(Node* parent, Node* node) {
    auto* rest = node->left ? node->left : node->right;
    if (!parent) {
      head_ = rest;
      delete node;
      return;
    }
    if (node->key < parent->key) {
      parent->left = rest;
    } else {
      parent->right = rest;
    }
    delete node;
    return;
  }

  void DeleteTreeHead(Node* parent, Node* node) {
    auto* min_node = FindMinimum(node->right);
    min_node->left = node->left;
    if (node->right != min_node) {
      min_node->right = node->right;
    }
    if (parent) {
      if (node->key < parent->key) {
        parent->left = min_node;
      } else {
        parent->right = min_node;
      }
    } else {
      head_ = min_node;
    }
    delete node;
  }

  bool DeleteNode(Node* parent, Node* node) {
    if (!node->left && !node->right) {
      DeleteLeafNode(parent, node);
    } else if (!node->left || !node->right) {
      DeleteHalfTreeHead(parent, node);
    } else {
      DeleteTreeHead(parent, node);
    }
    return true;
  }

  static Node* FindMinimum(Node* head) {
    while (head->left) {
      head = head->left;
    }
    return head;
  }

  static Node* FindMaximum(Node* head) {
    while (head->right) {
      head = head->right;
    }
    return head;
  }

  Node* FindNode(const int& key) const {
    Node* parent = head_;
    while (parent) {
      if (key < parent->key) {
        parent = parent->left;
      } else if (parent->key < key) {
        parent = parent->right;
      } else {
        return parent;
      }
    }
    return nullptr;
  }

  static void DeleteTree(Node* head) {
    if (head->left) {
      DeleteTree(head->left);
      head->left = nullptr;
    }
    if (head->right) {
      DeleteTree(head->right);
      head->right = nullptr;
    }
    delete head;
  }

  Node* head_ = nullptr;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  SimpleSearchTree tree;
  std::string command;
  while (input >> command) {
    int value;
    input >> value;
    if (command == "insert") {
      tree.Insert(value);
    } else if (command == "delete") {
      tree.Delete(value);
    } else if (command == "exists") {
      std::cout << (tree.Exists(value) ? "true\n" : "false\n");
    } else if (command == "next") {
      auto* ptr = tree.Next(value);
      std::cout << (ptr ? std::to_string(ptr->key) : "none") << '\n';
    } else {
      auto* ptr = tree.Prev(value);
      std::cout << (ptr ? std::to_string(ptr->key) : "none") << '\n';
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(insert 2
insert 5
insert 3
exists 2
exists 4
next 4
prev 4
delete 5
next 4
prev 4
)";
    Solution(ss);
    std::cout << "expected = true; false; 5; 3; none; 3\n";
  }
}
