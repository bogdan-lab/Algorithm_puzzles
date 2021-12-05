#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

void Solution(std::istream& input = std::cin);
void RunTests();

template <typename Key, typename Value>
class SimpleSearchTree {
 public:
  template <typename K, typename V>
  struct Node {
    Node<K, V>* left = nullptr;
    Node<K, V>* right = nullptr;
    Node<K, V>* parent = nullptr;
    K key{};
    V value{};

    Node(K k, V v) : key(std::move(k)), value(std::move(v)) {}
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

  bool Insert(Key key, Value value) {
    if (!head_) {
      head_ = new Node<Key, Value>(std::move(key), std::move(value));
      return true;
    }
    Node<Key, Value>* parent = head_;
    while (true) {
      if (key < parent->key) {
        if (!parent->left) {
          parent->left = new Node<Key, Value>(std::move(key), std::move(value));
          parent->left->parent = parent;
          return true;
        }
        parent = parent->left;
      } else if (parent->key < key) {
        if (!parent->right) {
          parent->right =
              new Node<Key, Value>(std::move(key), std::move(value));
          parent->right->parent = parent;
          return true;
        }
        parent = parent->right;
      } else {
        return false;
      }
    }
  }

  bool Delete(const Key& key) {
    Node<Key, Value>* node = FindNode(key);
    return node ? DeleteNode(node) : false;
  }
  bool Exists(const Key& key) const { return FindNode(key); }

  Node<Key, Value>* Next(const Key& key) {
    auto* curr_node = head_;
    Node<Key, Value>* max_node = nullptr;
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

  Node<Key, Value>* Prev(const Key& key) {
    auto* curr_node = head_;
    Node<Key, Value>* min_node = nullptr;
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
  void DeleteLeafNode(Node<Key, Value>* leaf_node) {
    assert(leaf_node);
    assert(!leaf_node->left && !leaf_node->right);
    if (leaf_node->parent) {
      if (leaf_node->key < leaf_node->parent->key) {
        leaf_node->parent->left = nullptr;
      } else {
        leaf_node->parent->right = nullptr;
      }
    } else {
      head_ = nullptr;
    }
    delete leaf_node;
  }

  void DeleteHalfTreeHead(Node<Key, Value>* node) {
    assert(node);
    assert((node->right && !node->left) || (node->left && !node->right));
    if (!node->parent) {
      head_ = node->left ? node->left : node->right;
      head_->parent = nullptr;
      delete node;
      return;
    }
    if (node->key < node->parent->key) {
      StickLeftNode(node->parent, node->left ? node->left : node->right);
    } else {
      StickRightNode(node->parent, node->left ? node->left : node->right);
    }
    delete node;
    return;
  }

  static void StickLeftNode(Node<Key, Value>* parent, Node<Key, Value>* child) {
    assert(parent && child);
    parent->left = child;
    child->parent = parent;
  }

  static void StickRightNode(Node<Key, Value>* parent,
                             Node<Key, Value>* child) {
    assert(parent && child);
    parent->right = child;
    child->parent = parent;
  }

  void DeleteTreeHead(Node<Key, Value>* node) {
    assert(node);
    assert(node->left && node->right);
    auto* min_node = FindMinimum(node->right);
    StickLeftNode(min_node, node->left);
    if (node->right != min_node) {
      StickRightNode(min_node, node->right);
    }
    if (node->parent) {
      if (node->key < node->parent->key) {
        StickLeftNode(node->parent, min_node);
      } else {
        StickRightNode(node->parent, min_node);
      }
    } else {
      head_ = min_node;
      min_node->parent = nullptr;
    }
    delete node;
  }

  bool DeleteNode(Node<Key, Value>* node) {
    assert(node);
    if (!node->left && !node->right) {
      DeleteLeafNode(node);
    } else if (!node->left || !node->right) {
      DeleteHalfTreeHead(node);
    } else {
      DeleteTreeHead(node);
    }
    return true;
  }

  static Node<Key, Value>* FindMinimum(Node<Key, Value>* head) {
    assert(head);
    while (head->left) {
      head = head->left;
    }
    return head;
  }

  static Node<Key, Value>* FindMaximum(Node<Key, Value>* head) {
    assert(head);
    while (head->right) {
      head = head->right;
    }
    return head;
  }

  Node<Key, Value>* FindNode(const Key& key) const {
    Node<Key, Value>* parent = head_;
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

  static void DeleteTree(Node<Key, Value>* head) {
    assert(head);
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

  Node<Key, Value>* head_ = nullptr;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  SimpleSearchTree<int, int> tree;
  std::string command;
  while (input >> command) {
    int value;
    input >> value;
    if (command == "insert") {
      tree.Insert(value, value);
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
