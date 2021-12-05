#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "gtest/gtest.h"
template <typename Key, typename Value>
class SimpleSearchTree {
 public:
  struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    Key key{};
    Value value{};

    Node(Key k, Value v) : key(std::move(k)), value(std::move(v)) {}
  };

  class Iterator {
   public:
    Iterator() = default;
    Iterator(Node* iter_ptr, Node* head) : curr_node_(iter_ptr), head_(head) {}

    Node& operator*() { return *curr_node_; }
    Node* operator->() { return curr_node_; }

    Iterator& operator++() {
      assert(curr_node_);
      if (curr_node_->right) {
        curr_node_ = FindMinimum(curr_node_->right);
      } else {
        auto* prev = curr_node_;
        do {
          prev = curr_node_;
          curr_node_ = curr_node_->parent;
        } while (curr_node_ && curr_node_->key < prev->key);
      }
      return *this;
    }

    Iterator operator++(int) {
      auto* initial = curr_node_;
      ++(*this);
      return {initial, head_};
    }

    Iterator& operator--() {
      assert(head_);
      if (!curr_node_) {
        // end case
        curr_node_ = FindMaximum(head_);
      } else if (curr_node_->left) {
        curr_node_ = FindMaximum(curr_node_->left);
      } else {
        auto* prev = curr_node_;
        do {
          prev = curr_node_;
          curr_node_ = curr_node_->parent;
        } while (curr_node_ && prev->key < curr_node_->key);
      }
      return *this;
    }

    Iterator operator--(int) {
      auto* initial = curr_node_;
      --(*this);
      return {initial, head_};
    }

    bool operator==(const Iterator& other) const {
      return curr_node_ == other.curr_node_;
    }

    bool operator!=(const Iterator& other) const { return !(*this == other); }

   private:
    Node* curr_node_ = nullptr;
    Node* head_ = nullptr;
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
      head_ = new Node(std::move(key), std::move(value));
      return true;
    }
    Node* parent = head_;
    while (true) {
      if (key < parent->key) {
        if (!parent->left) {
          parent->left = new Node(std::move(key), std::move(value));
          parent->left->parent = parent;
          return true;
        }
        parent = parent->left;
      } else if (parent->key < key) {
        if (!parent->right) {
          parent->right = new Node(std::move(key), std::move(value));
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
    Node* node = FindNode(key);
    return node ? DeleteNode(node) : false;
  }
  bool Exists(const Key& key) const { return FindNode(key); }

  Node* Next(const Key& key) {
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

  Node* Prev(const Key& key) {
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

  Iterator begin() {
    if (!head_) return {};
    return {FindMinimum(head_), head_};
  }

  Iterator end() { return {nullptr, head_}; }

 private:
  void DeleteLeafNode(Node* leaf_node) {
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

  void DeleteHalfTreeHead(Node* node) {
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

  static void StickLeftNode(Node* parent, Node* child) {
    assert(parent && child);
    parent->left = child;
    child->parent = parent;
  }

  static void StickRightNode(Node* parent, Node* child) {
    assert(parent && child);
    parent->right = child;
    child->parent = parent;
  }

  void DeleteTreeHead(Node* node) {
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

  bool DeleteNode(Node* node) {
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

  static Node* FindMinimum(Node* head) {
    assert(head);
    while (head->left) {
      head = head->left;
    }
    return head;
  }

  static Node* FindMaximum(Node* head) {
    assert(head);
    while (head->right) {
      head = head->right;
    }
    return head;
  }

  Node* FindNode(const Key& key) const {
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

  Node* head_ = nullptr;
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

TEST(SimpleTreeTests, RangeBasedForTest) {
  std::vector<int> vec{6, 4, 5, 3, 1, 10, 15, 2, 25};
  std::vector<int> expected = vec;
  std::sort(expected.begin(), expected.end());
  SimpleSearchTree<int, int> tree;
  for (const auto& el : vec) {
    tree.Insert(el, el);
  }

  std::vector<int> result;
  result.reserve(vec.size());
  for (const auto& el : tree) {
    result.push_back(el.key);
  }
  EXPECT_EQ(result, expected);
}

TEST(SimpleTreeTests, IteratorStepping) {
  std::vector<int> vec{6, 4, 5, 3, 1, 10, 15, 2, 25};
  SimpleSearchTree<int, int> tree;
  EXPECT_EQ(tree.begin(), tree.end());

  for (const auto& el : vec) {
    tree.Insert(el, el);
  }

  auto it = tree.begin();
  EXPECT_EQ(it->key, 1);
  EXPECT_EQ((++it)->key, 2);
  EXPECT_EQ((it++)->key, 2);
  EXPECT_EQ(it->key, 3);

  it = --tree.end();
  EXPECT_EQ(it->key, 25);
  EXPECT_EQ((--it)->key, 15);
  EXPECT_EQ((it--)->key, 15);
  EXPECT_EQ(it->key, 10);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
