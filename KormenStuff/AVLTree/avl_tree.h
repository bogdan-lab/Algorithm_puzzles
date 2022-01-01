#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <cassert>

template <typename Key, typename Value>
class AVLTree {
  struct Node {
    Node(const Key& g_key, const Value& g_val) : key(g_key), value(g_val) {}

    Key key;
    Value value;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
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

  bool Insert(const Key& key, const Value& value) {
    if (Empty()) {
      head_ = new Node{key, value};
      return true;
    }
    Node* current = head_;
    Node* parent = nullptr;
    while (current) {
      parent = current;
      if (current->key < key) {
        current = current->right;
      } else if (key < current->key) {
        current = current->left;
      } else {
        return false;
      }
    }
    Node* node = new Node{key, value};
    if (parent->key < key) {
      parent->right = node;
    } else {
      parent->left = node;
    }
    node->parent = node;
    return true;
  }

  bool Delete(const Key& key) { return false; }

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

  const Node* Next(const Key& key) { return NextImpl(key); }

  const Node* Prev(const Key& key) { return PrevImpl(key); }

 private:
  static void DeleteTree(Node* tree_head) {
    if (!tree_head) return;
    DeleteTree(tree_head->left);
    DeleteTree(tree_head->right);
    delete tree_head;
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

  Node* NextImpl(const Key& key) {
    if (Empty()) return nullptr;
    Node* last_left_turn = nullptr;
    Node* current = head_;
    while (current) {
      if (key < current->key) {
        last_left_turn = current;
        current = current->left;
      } else if (current->key < key) {
        current = current->right;
      } else {
        if (!current->right) {
          return last_left_turn;
        } else {
          return FindTreeMin(current->right);
        }
      }
    }
    return last_left_turn;
  }

  Node* PrevImpl(const Key& key) {
    if (Empty()) return nullptr;
    Node* last_right_turn = nullptr;
    Node* current = head_;
    while (current) {
      if (key < current->key) {
        current = current->left;
      } else if (current->key < key) {
        last_right_turn = current;
        current = current->right;
      } else {
        if (!current->left) {
          return last_right_turn;
        } else {
          return FindTreeMax(current->left);
        }
      }
    }
    return last_right_turn;
  }

  Node* head_ = nullptr;
};

#endif
