#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

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

  bool Delete(const Key& key) { return DeleteNode(FindNode(key)); }
  bool Exists(const Key& key) const { return FindNode(key); }

  Node<Key, Value>* Next(const Key& key) {
    if (!head_) return nullptr;
    auto* parent = head_;
    while (true) {
      if (key < parent->key) {
        if (!parent->left) {
          return parent;
        }
        parent = parent->left;
      } else if (parent->key < key) {
        if (!parent->right) {
          return NextForExisting(parent);
        }
        parent = parent->right;
      } else {
        return NextForExisting(parent);
      }
    }
  }

  Node<Key, Value>* Prev(const Key& key) {
    if (!head_) return nullptr;
    auto* parent = head_;
    while (true) {
      if (key < parent->key) {
        if (!parent->left) {
          return PrevForExisting(parent);
        }
        parent = parent->left;
      } else if (key < parent->key) {
        if (!parent->right) {
          return parent;
        }
        parent = parent->right;
      } else {
        return PrevForExisting(parent);
      }
    }
  }

 private:
  static Node<Key, Value>* NextForExisting(const Node<Key, Value>* node) {
    if (node->right) {
      return FindMinimum(node->right);
    }
    auto* initial = node;
    while (node->parent && node->parent->key < initial->key) {
      node = node->parent;
    }
    return node->parent;
  }

  static Node<Key, Value>* PrevForExisting(const Node<Key, Value>* node) {
    if (node->left) {
      return FindMaximum(node->left);
    }
    auto* initial = node;
    while (node->parent && node->parent->key > initial->key) {
      node = node->parent;
    }
    return node->parent;
  }

  void DeleteLeafNode(Node<Key, Value>* leaf_node) {
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
    assert((node->right && !node->left) || (node->left && !node->right));
    if (!node->parent) {
      head_ = node->left ? node->left : node->right;
      delete node;
      return;
    }
    if (!node->left) {
      if (node->key < node->parent->key) {
        node->parent->left = node->right;
        node->right->parent = node->parent;
      } else {
        node->parent->right = node->right;
        node->right->parent = node->parent;
      }
      delete node;
      return;
    }
    if (!node->right) {
      if (node->key < node->parent->key) {
        node->parent->left = node->left;
        node->left->parent = node->parent;
      } else {
        node->parent->right = node->left;
        node->right->parent = node->parent;
      }
      delete node;
      return;
    }
  }

  void DeleteTreeHead(Node<Key, Value>* node) {
    assert(node->left && node->right);
    auto* min_node = FindMinimum(node->right);

    node->left->parent = min_node;
    min_node->left = node->left;
    node->right->parent = min_node;
    min_node->right = node->right != min_node ? node->right : nullptr;
    if (node->parent) {
      if (node->key < node->parent->key) {
        node->parent->left = min_node;
        min_node->parent = node->parent->left;
      } else {
        node->parent->right = min_node;
        min_node->parent = node->parent->right;
      }
    } else {
      head_ = min_node;
    }
    delete node;
  }

  bool DeleteNode(Node<Key, Value>* node) {
    if (!node) return false;
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
    if (!head_) return nullptr;
    Node<Key, Value>* parent = head_;
    while (true) {
      if (key < parent->key) {
        if (!parent->left) return nullptr;
        parent = parent->left;
      } else if (parent->key < key) {
        if (!parent->right) return nullptr;
        parent = parent->right;
      } else {
        return parent;
      }
    }
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

TEST(SimpleTreeTests, EmptyTree) {
  SimpleSearchTree<int, double> tree;
  EXPECT_FALSE(tree.Delete(10));
  EXPECT_FALSE(tree.Exists(1));
}

TEST(SimpleTreeTests, FillingAndClearing) {
  SimpleSearchTree<int, double> tree;
  EXPECT_FALSE(tree.Exists(1));
  EXPECT_TRUE(tree.Insert(1, 1.0));
  EXPECT_TRUE(tree.Exists(1));
  EXPECT_TRUE(tree.Insert(2, 2.0));
  EXPECT_TRUE(tree.Exists(2));
  EXPECT_TRUE(tree.Insert(0, 2.0));
  EXPECT_TRUE(tree.Exists(0));
  EXPECT_TRUE(tree.Insert(3, 3.0));
  EXPECT_TRUE(tree.Exists(3));
  EXPECT_TRUE(tree.Insert(-3, -3.0));
  EXPECT_TRUE(tree.Exists(-3));
  EXPECT_TRUE(tree.Insert(-2, -2.0));
  EXPECT_TRUE(tree.Exists(-2));
  EXPECT_TRUE(tree.Insert(4, 4.0));
  EXPECT_TRUE(tree.Exists(4));
  EXPECT_TRUE(tree.Insert(-4, -4.0));
  EXPECT_TRUE(tree.Exists(-4));

  EXPECT_TRUE(tree.Delete(4));
  EXPECT_FALSE(tree.Exists(4));
  EXPECT_TRUE(tree.Delete(-3));
  EXPECT_FALSE(tree.Exists(-3));
  EXPECT_TRUE(tree.Delete(1));
  EXPECT_FALSE(tree.Delete(1));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
