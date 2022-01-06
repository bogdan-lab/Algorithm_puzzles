#include <cassert>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

constexpr int kTheLowest = std::numeric_limits<int>::min();
constexpr int kTheHighest = std::numeric_limits<int>::max();

void Solution(std::istream& input = std::cin);
void RunTests();

class AVLTree {
  struct Node {
    Node(int g_key) : key(g_key), tree_sum(g_key) {}

    int key;
    int height = 1;
    uint64_t tree_sum = 0;
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

  void Insert(int key) {
    if (Exists(key)) return;
    head_ = InsertImpl(head_, key);
  }

  uint64_t Sum(int left, int right) const {
    return SumImpl(head_, kTheLowest, kTheHighest, left, right);
  }

  bool Exists(int key) const {
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

 private:
  static void DeleteTree(Node* tree_head) {
    if (!tree_head) return;
    DeleteTree(tree_head->left);
    DeleteTree(tree_head->right);
    delete tree_head;
  }

  static uint64_t SumImpl(Node* node, int tree_low, int tree_high, int left,
                          int right) {
    if (!node) return 0;
    if (tree_low > right) return 0;
    if (tree_high < left) return 0;
    if (left <= tree_low && tree_high <= right) {
      return node->tree_sum;
    }
    uint64_t sum = left <= node->key && node->key <= right ? node->key : 0;
    if (node->left) {
      sum += SumImpl(node->left, tree_low, node->key, left, right);
    }
    if (node->right) {
      sum += SumImpl(node->right, node->key, tree_high, left, right);
    }
    return sum;
  }

  static int GetHeight(Node* node) { return node ? node->height : 0; }

  static int GetFactor(Node* node) {
    assert(node);
    return GetHeight(node->right) - GetHeight(node->left);
  }

  static void FixHeight(Node* node) {
    node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
  }

  static uint64_t GetTreeSum(Node* node) { return node ? node->tree_sum : 0; }

  static void FixTreeSum(Node* node) {
    node->tree_sum =
        GetTreeSum(node->left) + GetTreeSum(node->right) + node->key;
  }

  static Node* RotateRight(Node* head) {
    assert(head);
    Node* new_head = head->left;
    head->left = new_head->right;
    new_head->right = head;
    FixHeight(head);
    FixTreeSum(head);
    FixHeight(new_head);
    FixTreeSum(new_head);
    return new_head;
  }

  static Node* RotateLeft(Node* head) {
    assert(head);
    Node* new_head = head->right;
    head->right = new_head->left;
    new_head->left = head;
    FixHeight(head);
    FixTreeSum(head);
    FixHeight(new_head);
    FixTreeSum(new_head);
    return new_head;
  }

  static Node* Balance(Node* node) {
    FixHeight(node);
    FixTreeSum(node);
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

  static Node* InsertImpl(Node* node, int key) {
    if (!node) return new Node{key};
    if (node->key < key) {
      node->right = InsertImpl(node->right, key);
    } else if (key < node->key) {
      node->left = InsertImpl(node->left, key);
    } else {
      return node;
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

  static Node* LowerBound(Node* node, int key) {
    Node* last_left_turn = nullptr;
    while (node) {
      if (node->key < key) {
        node = node->right;
      } else if (key < node->key) {
        last_left_turn = node;
        node = node->left;
      } else {
        return node;
      }
    }
    return last_left_turn;
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
  AVLTree data;
  int n = 0;
  input >> n;
  std::string command;
  uint64_t prev_val = 0;
  while (n--) {
    input >> command;
    if (command == "+") {
      uint64_t val = 0;
      input >> val;
      data.Insert((val + prev_val) % 1'000'000'000);
      prev_val = 0;
    } else {
      int left = 0;
      int right = 0;
      input >> left >> right;
      uint64_t res = data.Sum(left, right);
      prev_val = res;
      std::cout << res << '\n';
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
+ 1
+ 3
+ 3
? 2 4
+ 1
? 2 4
)";
    Solution(ss);
    std::cout << "expected = 3; 7\n";
  }
}
