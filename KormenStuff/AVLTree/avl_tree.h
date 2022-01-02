#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <cassert>

template <typename Key, typename Value>
class AVLTree {
  struct Node {
    Node(const Key& g_key, const Value& g_val) : key(g_key), value(g_val) {}

    Key key;
    Value value;
    int height = 1;
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
    node->parent = parent;
    UpdateHeight(node, 1);
    return true;
  }

  bool Delete(const Key& key) {
    if (Empty()) return false;
    Node* current = head_;
    while (current) {
      if (key < current->key) {
        current = current->left;
      } else if (current->key < key) {
        current = current->right;
      } else {
        if (current == head_) {
          DeleteHead();
        } else {
          DeleteNode(current);
        }
        return true;
      }
    }
    return false;
  }

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

  static void DeleteLeafNode(Node* leaf) {
    assert(!leaf->left && !leaf->right);
    assert(leaf->parent);
    if (leaf->parent->key < leaf->key) {
      leaf->parent->right = nullptr;
    } else {
      leaf->parent->left = nullptr;
    }
    UpdateHeight(leaf, 0);
    delete leaf;
  }

  static Node* DeleteInsideNode(Node* node) {
    assert(node->left || node->right);
    Node* replacement = nullptr;
    if (node->right) {
      replacement = FindTreeMin(node->right);
    } else {
      replacement = FindTreeMax(node->left);
    }
    int new_replacement_h = replacement->parent->height - 1;
    int alternative = replacement->parent->key < replacement->key
                          ? GetHeight(replacement->parent->left)
                          : GetHeight(replacement->parent->right);
    UpdateHeight(replacement->parent, std::max(new_replacement_h, alternative));
    ExtractOneLinkNode(replacement);
    ReplaceNode(node, replacement);
    delete node;
    return replacement;
  }

  static void ExtractOneLinkNode(Node* node) {
    assert(node);
    assert(!(node->right && node->left));
    Node* filler = node->left ? node->left : node->right;
    if (node->parent) {
      if (node->parent->key < node->key) {
        node->parent->right = filler;
      } else {
        node->parent->left = filler;
      }
    }
    if (filler) {
      filler->parent = node->parent;
    }
  }

  static void ReplaceNode(Node* target, Node* source) {
    assert(source && target);
    if (target->parent) {
      if (target->parent->key < target->key) {
        target->parent->right = source;
      } else {
        target->parent->left = source;
      }
    }
    source->parent = target->parent;

    if (target->left && target->left != source) {
      source->left = target->left;
      target->left->parent = source;
    } else {
      source->left = nullptr;
    }
    if (target->right && target->right != source) {
      source->right = target->right;
      target->right->parent = source;
    } else {
      source->right = nullptr;
    }
    source->height = target->height;
  }

  static void DeleteNode(Node* tree_head) {
    if (!tree_head->left && !tree_head->right) {
      DeleteLeafNode(tree_head);
    } else {
      DeleteInsideNode(tree_head);
    }
  }

  static int GetHeight(Node* node) { return node ? node->height : 0; }

  static void UpdateHeight(Node* bot_node, int new_height) {
    assert(bot_node);
    bot_node->height = new_height;
    Node* parent = bot_node->parent;
    while (parent) {
      parent->height =
          std::max(GetHeight(parent->right), GetHeight(parent->left)) + 1;
      parent = parent->parent;
    }
  }

  static void RotateLeft(Node* head) {
    Node* new_head = head->right;
    head->right = new_head->left;
    if (new_head->left) {
      new_head->left->parent = head;
    }
    new_head->parent = head->parent;
    if (head->parent) {
      if (head->parent->key < head->key) {
        head->parent->right = new_head;
      } else {
        head->parent->left = new_head;
      }
    }
    new_head->left = head;
    head->parent = new_head;
  }

  static void RotateRight(Node* head) {
    Node* new_head = head->left;
    head->left = new_head->right;
    if (new_head->right) {
      new_head->right->parent = head;
    }
    new_head->parent = head->parent;
    if (head->parent) {
      if (head->parent->key < head->key) {
        head->parent->right = new_head;
      } else {
        head->parent->left = new_head;
      }
    }
    new_head->right = head;
    head->parent = new_head;
  }

  void DeleteHead() {
    if (!head_->right && !head_->left) {
      delete head_;
      head_ = nullptr;
      return;
    };
    head_ = DeleteInsideNode(head_);
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
