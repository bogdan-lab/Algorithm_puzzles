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
    if (!root_) return;
    while (root_->left || root_->right) {
      DeleteFromRoot();
    }
    delete root_;
    root_ = nullptr;
  }
  /**
   * Inserts given pair into the tree. If given key is already present in the
   * tree method does nothing. Returns true if the element was added and false
   * otherwise.
   */
  bool Insert(const Key& key, const Value& value) {
    // Split and create
    if (!root_) {
      root_ = new Node(key, value);
      return true;
    }
    auto [left, right] = SplitImpl(key);
    if (right && !(key < right->key)) {
      root_ = MergeImpl(left, right);
      return false;  // key is already there!
    }
    root_ = new Node(key, value);
    root_->left = left;
    if (left) left->parent = root_;
    root_->right = right;
    if (right) right->parent = root_;
    return true;
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
    DeleteFromRoot();
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
  /**
   * Rotates subtree to the right around given node.
   * In the result of the operation given node becomes parent of its parent
   * and its parent becomes the left child of the node.
   *
   * @warning method expects that node and its parent are not nullptr
   * Also it expects that node is the left child of the parent
   */
  static void RotateRight(Node* node) {
    assert(node && node->parent);
    assert(node == node->parent->left);
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
    if (parent->left) parent->left->parent = parent;
    node->right = parent;
  }
  /**
   * Rotates subtree to the left around given node.
   * In the result of the operation given node becomes parent of its parent
   * and its parent becomes the left child of the node.
   *
   * @warning method expects that node and its parent are not nullptr
   * Also it expects that node is the right child of the parent
   */
  static void RotateLeft(Node* node) {
    assert(node && node->parent);
    assert(node == node->parent->right);
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
    if (parent->right) parent->right->parent = parent;
    node->left = parent;
  }
  /**
   * Moves the given pointer to the tree root and returns it.
   */
  static Node* Splay(Node* node) {
    assert(node);
    Node* parent = node->parent;
    while (parent) {
      bool node_is_left_child = parent->left == node;
      Node* grand = parent->parent;
      if (!grand) {
        if (node_is_left_child) {
          RotateRight(node);
        } else {
          RotateLeft(node);
        }
      } else if (node_is_left_child && grand->left == parent) {
        RotateRight(parent);
        RotateRight(node);
      } else if (!node_is_left_child && grand->right == parent) {
        RotateLeft(parent);
        RotateLeft(node);
      } else if (!node_is_left_child && grand->left == parent) {
        RotateLeft(node);
        RotateRight(node);
      } else {
        RotateRight(node);
        RotateLeft(node);
      }
      parent = node->parent;
    }
    assert(!node->parent);  // we are returnung root
    return node;
  }

  /**
   * Returns the node which ended up in a root. If the requested key was not
   * found, method will return the possible parrent for such key. Note that in
   * this case the parent will end up in tree root after this method!
   * Cannot return nullptr
   */
  static Node* FindImpl(Node* node, const Key& key) {
    assert(node);
    while (true) {
      if (key < node->key && node->left) {
        node = node->left;
      } else if (node->key < key && node->right) {
        node = node->right;
      } else {
        break;
      }
    }
    return Splay(node);
  }
  /**
   * Splits given tree into two, where the first one will have all keys smaller
   * than the given, and the second - all the rest.
   *
   * @warning Method breaks tree into two and the one should be restored
   * explicitly after required work is done!
   * Expects that tree is not empty
   */
  std::pair<Node*, Node*> SplitImpl(const Key& key) {
    assert(root_);
    root_ = FindImpl(root_, key);
    if (root_->key < key) {
      // split with root in the left
      Node* right = root_->right;
      root_->right = nullptr;
      if (right) right->parent = nullptr;
      return {root_, right};
    } else {
      // split with root in the right
      Node* left = root_->left;
      root_->left = nullptr;
      if (left) left->parent = nullptr;
      return {left, root_};
    }
  }
  /**
   * Merges two trees.
   * @warning Assumes that all keys in the left tree are smaller than all keys
   * in the right tree. Left and right pointers are expected to be pointers to
   * the tree roots
   */
  static Node* MergeImpl(Node* left, Node* right) {
    assert(!left || !left->parent);
    assert(!right || !right->parent);
    if (!right) return left;
    if (!left) return right;
    Node* root = FindImpl(right, left->key);
    assert(!root->left);
    root->left = left;
    left->parent = root;
    return root;
  }
  /**
   * Deletes node from the root.
   */
  void DeleteFromRoot() {
    assert(root_);
    Node* left = root_->left;
    if (left) left->parent = nullptr;
    Node* right = root_->right;
    if (right) right->parent = nullptr;
    delete root_;
    root_ = MergeImpl(left, right);
  }

  Node* root_ = nullptr;
};

#endif
