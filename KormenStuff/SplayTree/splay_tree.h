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
  void Insert(const Key& key, const Value& value) {
    // Split and create
  }
  void Delete(const Key& key) {
    // Split and merge
  }
  bool Empty() const { return !root_; }
  Value* Find(const Key& key) { return FindImpl(root_, key); }

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

  static void ZigZigRight(Node* node) {
    RotateRight(node->parent);
    RotateRight(node);
  }

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

  static Value* FindImpl(Node* node, const Key& key) {
    if (!node) return node;
    if (key < node->key) {
      return Find(node->left, key);
    } else if (node->key < key) {
      return Find(node->right, key);
    } else {
      return &(node->value);
    }
    // TODO add node propagation!!! use Splay for it
  }

  Node* root_ = nullptr;
};

template <typename Key, typename Value>
class AVLTree {
  struct Node {
    Node(const Key& g_key, const Value& g_val) : key(g_key), value(g_val) {}

    Key key;
    Value value;
    int height = 1;
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
    head_ = InsertImpl(head_, key, val);
  }

  void Delete(const Key& key) { head_ = DeleteImpl(head_, key); }

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

  const Node* Next(const Key& key) const { return NextImpl(head_, key); }
  const Node* Prev(const Key& key) const { return PrevImpl(head_, key); }

  bool Empty() const { return !head_; }

 private:
  static void DeleteTree(Node* tree_head) {
    if (!tree_head) return;
    DeleteTree(tree_head->left);
    DeleteTree(tree_head->right);
    delete tree_head;
  }

  static int GetHeight(Node* node) { return node ? node->height : 0; }

  static int GetFactor(Node* node) {
    return GetHeight(node->right) - GetHeight(node->left);
  }

  static void FixHeight(Node* node) {
    node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
  }

  static Node* RotateRight(Node* head) {
    assert(head);
    Node* new_head = head->left;
    head->left = new_head->right;
    new_head->right = head;
    FixHeight(head);
    FixHeight(new_head);
    return new_head;
  }

  static Node* RotateLeft(Node* head) {
    assert(head);
    Node* new_head = head->right;
    head->right = new_head->left;
    new_head->left = head;
    FixHeight(head);
    FixHeight(new_head);
    return new_head;
  }

  static Node* Balance(Node* node) {
    FixHeight(node);
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
    if (!node) return new Node{key, val};
    if (node->key < key) {
      node->right = InsertImpl(node->right, key, val);
    } else if (key < node->key) {
      node->left = InsertImpl(node->left, key, val);
    } else {
      return node;
    }
    return Balance(node);
  }

  static const Node* NextImpl(const Node* node, const Key& key) {
    const Node* last_left_turn = nullptr;
    while (node) {
      if (key < node->key) {
        last_left_turn = node;
        node = node->left;
      } else if (node->key < key) {
        node = node->right;
      } else {
        if (!node->right) {
          return last_left_turn;
        } else {
          return FindTreeMin(node->right);
        }
      }
    }
    return last_left_turn;
  }

  static const Node* PrevImpl(const Node* node, const Key& key) {
    const Node* last_right_turn = nullptr;
    while (node) {
      if (key < node->key) {
        node = node->left;
      } else if (node->key < key) {
        last_right_turn = node;
        node = node->right;
      } else {
        if (!node->left) {
          return last_right_turn;
        } else {
          return FindTreeMax(node->left);
        }
      }
    }
    return last_right_turn;
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

#endif
