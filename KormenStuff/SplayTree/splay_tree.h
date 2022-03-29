#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <algorithm>
#include <cassert>
#include <utility>

template <typename Key, typename Value>
class SplayTree {
  struct Node {
    Node(const Key& g_key, const Value& g_value) : key(g_key), value(g_value) {}

    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    Key key;
    Value value;
  };

 public:
  SplayTree() = default;
  ~SplayTree() {
    DeleteImpl(root_);
    root_ = nullptr;
  }
  bool Insert(const Key& key, const Value& value) {
    // Split and create
    if (!root_) {
      root_ = new Node(key, value);
      return true;
    }
    auto [left, right] = SplitImpl(root_, key);
    if (!(key < right->key)) {
      return false;  // key is already there!
    }
    root_ = new Node(key, value);
    root_->left = left;
    left->parent = root_;
    root_->right = right;
    right->parent = root_;
  }
  /**
   * Deletes element with given key from the tree.
   * Tree will be rebalanced in the splay way when this method is called,
   * regardless the presence of the given key in the tree.
   * Returns true if key was deleted, false if there is no element with given
   * key.
   */
  bool Delete(const Key& key) {
    if (Empty()) return false;
    root_ = FindImpl(root_, key);
    if (key < root_->key || root_->key < key) {
      return false;
    }
    Node* left = root_->left;
    left->parent = nullptr;
    Node* right = root_->right;
    right->parent = nullptr;
    delete root_;
    root_ = MergeImpl(left, right);
    return true;
  }
  /**Returns true if tree is empty*/
  bool Empty() const { return !root_; }
  /**
   * Returns pointer to the value which is stored with the given key.
   * If the given key is absent - returns nullptr.
   * Rebalance the tree in the way that key (or its parent), which we were
   * looking for, ends up in the root. Tree is rebalances even in the case when
   * we are searching for the absent key.
   */
  Value* Find(const Key& key) {
    if (Empty()) return nullptr;
    root_ = FindImpl(root_, key);
    if (!(root_->key < key) && !(key < root_->key)) {
      return &root_->value;
    }
    return nullptr;
  }

 private:
  static void DeleteImpl(Node* node) {
    if (!node) return;
    if (node->right) DeleteImpl(node->right);
    if (node->left) DeleteImpl(node->left);
    delete node;
  }
  /**Call when node is left child*/
  static void RotateRight(Node* node) {
    assert(node && node->parent);
    Node* parent = node->parent;
    // parent connection
    Node* grand = parent->parent;
    node->parent = grand;
    if (grand) {
      if (grand->left == parent) {
        grand->left = node;
      } else {
        grand->right = node;
      }
    }
    parent->parent = node;
    // child connection
    parent->left = node->right;
    parent->left->parent = parent;
    node->right = parent;
  }
  /**Call when node is right child*/
  static void RotateLeft(Node* node) {
    assert(node && node->parent);
    Node* parent = node->parent;
    // parent connection
    Node* grand = parent->parent;
    node->parent = grand;
    if (grand) {
      if (grand->left == parent) {
        grand->left = node;
      } else {
        grand->right = node;
      }
    }
    parent->parent = node;
    // child connection
    parent->right = node->left;
    parent->right->parent = parent;
    node->left = parent;
  }
  /**
   * Moves the given pointer to the tree root.
   */
  static void Splay(Node* node) {
    Node* parent = node->parent;
    if (!parent) return;
    Node* grand = parent->parent;
    if (!grand) {
      if (node == parent->left) {
        RotateRight(node);
      } else {
        RotateLeft(node);
      }
      return;
    }
    // Here we have grandparent
    if (parent->left == node && grand->left == parent) {
      RotateRight(node->parent);
      RotateRight(node);
      Splay(node);
      return;
    }
    if (parent->right == node && grand->right == parent) {
      RotateLeft(node->parent);
      RotateLeft(node);
      Splay(node);
      return;
    }
    if (parent->right == node && grand->left == parent) {
      RotateLeft(node);
      RotateRight(node);
      Splay(node);
      return;
    }
    if (parent->left == node && grand->right == parent) {
      RotateRight(node);
      RotateLeft(node);
      Splay(node);
      return;
    }
  }
  /**
   * Returns the node which ended up in a root. If the requested key was not
   * found, method will return the possible parrent for such key. Note that in
   * this case the parent will end up in tree root after this method!
   * Cannot return nullptr
   */
  static Node* FindImpl(Node* node, const Key& key) {
    assert(node);
    if (key < node->key && node->lfet) {
      return Find(node->left, key);
    } else if (node->key < key && node->right) {
      return Find(node->right, key);
    }
    Splay(node);
    return node;
  }
  /**
   * Splits given tree into two, where the first one will have all keys smaller
   * than the given, and the second - all the rest.
   */
  static std::pair<Node*, Node*> SplitImpl(Node* root, const Key& key) {
    assert(root);
    root = FindImpl(root, key);
    if (root->key < key) {
      // split with root in the left
      Node* right = root->right;
      root->right = nullptr;
      right->parent = nullptr;
      return {root, right};
    } else {
      // split with root in the right
      Node* left = root->left;
      root->left = nullptr;
      left->parent = nullptr;
      return {left, root};
    }
  }

  /**
   * Merges two trees. Assumes that all keys in the left tree are smaller than
   * all keys in the right tree.
   * left and right pointers are expected to be pointers to the tree roots
   */
  static Node* MergeImpl(Node* left, Node* right) {
    assert(!left->parent);
    assert(!right->parent);
    if (!right) return left;
    if (!left) return right;
    Node* root = FindImpl(right, left->key);
    assert(!root->left);
    root->left = left;
    left->parent = root->left;
    return root;
  }

  Node* root_ = nullptr;
};

#endif
