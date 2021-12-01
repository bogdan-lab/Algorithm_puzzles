﻿#include <iostream>
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
    //
  }

  bool Insert(Key key, Value value) {
    if (!head_) {
      head_ = new Node<Key, Value>(std::move(key), std::move(value));
      return true;
    }
    Node<Key, Value>* parent = head_;
    while (true) {
      if (parent->key < key) {
        if (!parent->left) {
          parent->left = new Node<Key, Value>(std::move(key), std::move(value));
          parent->left->parent = parent;
          return true;
        } else {
          parent = parent->left;
        }
      } else if (key < parent->key) {
        if (!parent->right) {
          parent->right =
              new Node<Key, Value>(std::move(key), std::move(value));
          parent->right->parent = parent;
        } else {
          parent = parent->right;
        }
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
    auto* initial = node;
    while (node->parent && node->parent->key < initial->key) {
      node = node->parent;
    }
    return node->parent;
  }

  static Node<Key, Value>* PrevForExisting(const Node<Key, Value>* node) {
    auto* initial = node;
    while (node->parent && node->parent->key > initial->key) {
      node = node->parent;
    }
    return node->parent;
  }

  static bool DeleteNode(Node<Key, Value>* node) {
    if (!node) return false;
    if (!node->left) {
      if (node->key < node->parent->key) {
        node->parent->left = node->right;
      } else {
        node->parent->right = node->right;
      }
      delete node;
    } else if (!node->right) {
      if (node->key < node->parent->key) {
        node->parent->left = node->left;
      } else {
        node->parent->right = node->left;
      }
      delete node;
    } else {
      // replace with minimum in right tree
      auto* min_node = FindMinimum(node->right);
      Swap(node, min_node);
      delete min_node;
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

  static void Swap(Node<Key, Value>* lhs, Node<Key, Value>* rhs) noexcept {
    assert(lhs && rhs);
    auto swap_property = [](Node<Key, Value>** lhs_prop,
                            Node<Key, Value>** rhs_prop) {
      auto* tmp = *lhs_prop;
      *lhs_prop = *rhs_prop;
      *rhs_prop = tmp;
    };
    swap_property(&lhs->parent, &rhs->parent);
    swap_property(&lhs->left, &rhs->left);
    swap_property(&lhs->right, &rhs->right);
  }

  Node<Key, Value>* FindNode(const Key& key) const {
    if (!head_) return nullptr;
    Node<Key, Value>* parent = head_;
    while (true) {
      if (parent->key < key) {
        if (!parent->left) return nullptr;
        parent = parent->left;
      } else if (key < parent->key) {
        if (!parent->right) return nullptr;
        parent = parent->right;
      } else {
        return parent;
      }
    }
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
  EXPECT_TRUE(tree.Insert(4, 4.0));
  EXPECT_TRUE(tree.Exists(4));
  EXPECT_TRUE(tree.Insert(-4, -4.0));
  EXPECT_TRUE(tree.Exists(-4));

  EXPECT_TRUE(tree.Delete(4));
  EXPECT_FALSE(tree.Exists(4));
  EXPECT_TRUE(tree.Delete(-4));
  EXPECT_FALSE(tree.Exists(-4));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
