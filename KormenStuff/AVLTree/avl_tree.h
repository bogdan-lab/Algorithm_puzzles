#ifndef AVL_TREE_H
#define AVL_TREE_H

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
      parent = current->parent;
      if (current->key < key) {
        current = current->right;
      } else if (key < current->key) {
        current = current->left;
      } else {
        return false;
      }
    }
    if (parent->key < key) {
      parent->right = new Node{key, value};
    } else {
      parent->left = new Node{key, value};
    }
    return false;
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

  const Node* Next() const { return nullptr; }

  const Node* Prev() const { return nullptr; }

 private:
  static void DeleteTree(Node* tree_head) {
    if (!tree_head) return;
    DeleteTree(tree_head->left);
    DeleteTree(tree_head->right);
    delete tree_head;
  }

  Node* head_ = nullptr;
};

#endif
