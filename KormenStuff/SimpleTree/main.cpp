#include <algorithm>
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

TEST(SimpleTreeTests, SearchingNextAndPrevExisting) {
  std::vector<int> vec(15);
  std::iota(vec.begin(), vec.end(), 0);
  std::mt19937 rnd(42);
  size_t count = 10000;
  while (count--) {
    std::vector<int> rand_vec = vec;
    std::shuffle(rand_vec.begin(), rand_vec.end(), rnd);
    SimpleSearchTree<int, int> tree;
    for (const auto& el : rand_vec) {
      EXPECT_TRUE(tree.Insert(el, el));
    }
    for (const auto& el : vec) {
      if (el != vec.back()) {
        EXPECT_EQ(tree.Next(el)->key, el + 1);
      } else {
        EXPECT_FALSE(tree.Next(el));
      }
    }
    for (const auto& el : vec) {
      if (el != vec.front()) {
        EXPECT_EQ(tree.Prev(el)->key, el - 1);
      } else {
        EXPECT_FALSE(tree.Prev(el));
      }
    }
  }
}

TEST(SimpleTreeTests, SearchingNextAndPrevAbsent) {
  std::vector<int> vec{1,  3,  5,  7,  9,  11, 13, 15, 17,
                       19, 21, 23, 25, 27, 29, 31, 33};
  std::vector<int> req{0,  2,  4,  6,  8,  10, 12, 14, 16,
                       18, 20, 22, 24, 26, 28, 30, 32, 34};
  std::mt19937 rnd(42);
  size_t count = 10000;
  while (count--) {
    std::shuffle(vec.begin(), vec.end(), rnd);
    SimpleSearchTree<int, int> tree;
    for (const auto& el : vec) {
      EXPECT_TRUE(tree.Insert(el, el));
    }
    for (const auto& el : req) {
      if (el != req.back()) {
        EXPECT_EQ(tree.Next(el)->key, el + 1);
      } else {
        EXPECT_FALSE(tree.Next(el));
      }
    }
    for (const auto& el : req) {
      if (el != req.front()) {
        EXPECT_EQ(tree.Prev(el)->key, el - 1);
      } else {
        EXPECT_FALSE(tree.Prev(el));
      }
    }
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
