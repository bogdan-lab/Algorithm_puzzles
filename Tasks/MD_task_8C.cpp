#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

void Solution(std::istream& input = std::cin);
void RunTests();

template <typename Key, typename Value>
class AVLTree {
  struct Node {
    Node(const Key& g_key, const Value& g_val) : key(g_key), value(g_val) {}

    Key key;
    Value value;
    int height = 1;
    int child_num = 1;
    Node* left = nullptr;
    Node* right = nullptr;
  };

 public:
  AVLTree() = default;
  AVLTree(const AVLTree&) = delete;
  AVLTree(AVLTree&&) = delete;
  AVLTree& operator=(const AVLTree&) = delete;
  AVLTree& operator=(AVLTree&&) = delete;

  ~AVLTree() {
    DeleteTree(head_);
    head_ = nullptr;
  }

  void Insert(const Key& key, const Value& val) {
    if (Exists(key)) return;
    head_ = InsertImpl(head_, key, val);
  }

  void Delete(const Key& key) {
    if (!Exists(key)) return;
    head_ = DeleteImpl(head_, key);
  }

  bool Exists(const Key& key) const {
    Node* current = head_;
    while (current) {
      if (current->key < key) {
        current = current->right;
      } else if (key < current->key) {
        current = current->left;
      } else {
        return true;
      }
    }
    return false;
  }

  bool Empty() const { return !head_; }

  const Node* GetKthMax(int k_max) const {
    if (!head_) return nullptr;
    int k_min = GetChildNum(head_) - k_max + 1;
    Node* node = head_;
    while (node) {
      int curr_min = GetChildNum(node->left) + 1;
      if (k_min < curr_min) {
        node = node->left;
      } else if (k_min > curr_min) {
        k_min -= curr_min;
        node = node->right;
      } else {
        return node;
      }
    }
    return nullptr;
  }

 private:
  static void DeleteTree(Node* tree_head) {
    if (!tree_head) return;
    DeleteTree(tree_head->left);
    DeleteTree(tree_head->right);
    delete tree_head;
  }

  static int GetHeight(Node* node) { return node ? node->height : 0; }

  static int GetFactor(Node* node) {
    assert(node);
    return GetHeight(node->right) - GetHeight(node->left);
  }

  static void FixHeight(Node* node) {
    assert(node);
    node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
  }

  static int GetChildNum(Node* node) { return node ? node->child_num : 0; }

  static void FixChildNum(Node* node) {
    assert(node);
    node->child_num = GetChildNum(node->left) + GetChildNum(node->right) + 1;
  }

  static Node* RotateRight(Node* head) {
    assert(head);
    Node* new_head = head->left;
    head->left = new_head->right;
    new_head->right = head;
    FixHeight(head);
    FixChildNum(head);
    FixHeight(new_head);
    FixChildNum(new_head);
    return new_head;
  }

  static Node* RotateLeft(Node* head) {
    assert(head);
    Node* new_head = head->right;
    head->right = new_head->left;
    new_head->left = head;
    FixHeight(head);
    FixChildNum(head);
    FixHeight(new_head);
    FixChildNum(new_head);
    return new_head;
  }

  static Node* Balance(Node* node) {
    FixHeight(node);
    FixChildNum(node);
    int factor = GetFactor(node);
    if (factor == 2) {
      if (GetFactor(node->right) < 0) {
        node->right = RotateRight(node->right);
      }
      return RotateLeft(node);
    }
    if (factor == -2) {
      if (GetFactor(node->left) > 0) {
        node->left = RotateLeft(node->left);
      }
      return RotateRight(node);
    }
    return node;
  }

  static Node* InsertImpl(Node* node, const Key& key, const Value& val) {
    // Expect that key is not present in the tree
    if (!node) return new Node{key, val};
    if (node->key < key) {
      node->right = InsertImpl(node->right, key, val);
    } else {
      node->left = InsertImpl(node->left, key, val);
    }
    return Balance(node);
  }

  static Node* FindTreeMin(Node* tree_head) {
    assert(tree_head);
    while (tree_head->left) {
      tree_head = tree_head->left;
    }
    return tree_head;
  }

  static Node* FindTreeMax(Node* tree_head) {
    assert(tree_head);
    while (tree_head->right) {
      tree_head = tree_head->right;
    }
    return tree_head;
  }

  static Node* RemoveMin(Node* node) {
    if (!node->left) return node->right;
    node->left = RemoveMin(node->left);
    return Balance(node);
  }

  static Node* DeleteImpl(Node* node, const Key& key) {
    // Expect that I will delete only the node which is in the tree
    if (!node) return nullptr;
    if (key < node->key) {
      node->left = DeleteImpl(node->left, key);
    } else if (node->key < key) {
      node->right = DeleteImpl(node->right, key);
    } else {
      Node* left = node->left;
      Node* right = node->right;
      delete node;
      if (!right) return left;
      Node* min = FindTreeMin(right);
      min->right = RemoveMin(right);
      min->left = left;
      return Balance(min);
    }
    return Balance(node);
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
  int n;
  input >> n;
  AVLTree<int, int> data;
  while (n--) {
    int c = 0;
    int val = 0;
    input >> c >> val;
    switch (c) {
      case 1: {
        data.Insert(val, val);
        break;
      }
      case 0: {
        std::cout << data.GetKthMax(val)->key << '\n';
        break;
      }
      case -1: {
        data.Delete(val);
        break;
      }
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(24
1 5
1 3
1 7
0 1
0 2
0 3
-1 5
1 10
0 1
0 2
0 3
1 25
1 35
1 4
1 2
1 6
0 1
0 2
0 3
0 4
0 5
0 6
0 7
0 8
)";
    Solution(ss);
    std::cout << "expected = 7; 5; 3; 10; 7; 3; 35; 25; 10; 7; 6; 4; 3; 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(4
1 5
1 3
0 1
0 2)";
    Solution(ss);
    std::cout << "expected = 5; 3\n";
  }
  {
    std::stringstream ss;
    ss << R"(2
1 5
0 1)";
    Solution(ss);
    std::cout << "expected = 5\n";
  }
  {
    std::stringstream ss;
    ss << R"(8
1 5
1 3
-1 5
-1 3
1 7
1 4
0 1
0 2)";
    Solution(ss);
    std::cout << "expected = 7; 4\n";
  }
}
