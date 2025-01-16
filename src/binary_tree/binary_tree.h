//
// Created by sergey on 08.01.25.
//

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "../shared/shared.cpp"

namespace s21 {

template <typename Key, typename Value>
struct TreeNode {
  Key key;
  Value value;
  TreeNode<Key, Value>* left = nullptr;
  TreeNode<Key, Value>* right = nullptr;
  TreeNode<Key, Value>* parent = nullptr;

  TreeNode(Key k, Value v) : key(k), value(v) {}
};

template <typename Key, typename Value>
class BinaryTree {
 private:
  TreeNode<Key, Value>* root = nullptr;
  size_t treeSize = 0;

  TreeNode<Key, Value>* insert_(TreeNode<Key, Value>* node, const Key& key,
                                Value value,
                                TreeNode<Key, Value>* parent = nullptr) {
    if (!node) {
      ++treeSize;
      auto* newNode = new TreeNode<Key, Value>(key, value);
      newNode->parent = parent;
      return newNode;
    }
    if (node->key == key) {
      node->value = value;
    } else if (key < node->key) {
      node->left = insert_(node->left, key, value, node);
    } else if (key > node->key) {
      node->right = insert_(node->right, key, value, node);
    }
    return node;
  }

  static TreeNode<Key, Value>* findMin(TreeNode<Key, Value>* node) {
    while (node && node->left) {
      node = node->left;
    }
    return node;
  }

  TreeNode<Key, Value>* remove_(TreeNode<Key, Value>* node, const Key& key) {
    if (!node) return nullptr;

    if (key < node->key) {
      node->left = remove_(node->left, key);
    } else if (key > node->key) {
      node->right = remove_(node->right, key);
    } else {
      if (!node->left) {
        TreeNode<Key, Value>* right = node->right;
        delete node;
        --treeSize;
        return right;
      }
      if (!node->right) {
        TreeNode<Key, Value>* left = node->left;
        delete node;
        --treeSize;
        return left;
      }
      TreeNode<Key, Value>* successor = findMin(node->right);
      node->key = successor->key;
      node->value = successor->value;
      node->right = remove_(node->right, successor->key);
    }
    return node;
  }

  TreeNode<Key, Value>* get_(TreeNode<Key, Value>* node, const Key& key) const {
    if (!node) return nullptr;
    if (key < node->key) return get_(node->left, key);
    if (key > node->key) return get_(node->right, key);
    return node;
  }

  void clear_(TreeNode<Key, Value>* node) {
    if (node) {
      clear_(node->left);
      clear_(node->right);
      delete node;
    }
  }

 public:
  class Iterator;
  class ConstIterator;

  BinaryTree() = default;
  ~BinaryTree() { clear_(root); }

  Iterator begin() { return Iterator(findMin(root)); }
  Iterator end() const { return Iterator(nullptr); }

  ConstIterator cbegin() const { return ConstIterator(findMin(root)); }
  ConstIterator cend() const { return ConstIterator(nullptr); }

  Iterator insert(const Key& key, const Value& value) {
    root = insert_(root, key, value, nullptr);
    return get(key);
  }

  void remove(const Key& key) { root = remove_(root, key); }
  Iterator get(const Key& key) const { return Iterator(get_(root, key)); }
  void clear() {
    clear_(root);
    root = nullptr;
    treeSize = 0;
  }
  [[nodiscard]] size_t size() const { return treeSize; }
  // BinaryTree(const BinaryTree<Key, Value>& other) {
  //     for (auto it = other.cbegin(); it != other.cend(); ++it) {
  //         insert((*it)->key, (*it)->value);
  //     }
  // }

  BinaryTree& operator=(const BinaryTree<Key, Value>& other) {
    if (this == &other) return *this;

    clear();
    root = other.root;
    treeSize = other.treeSize;
    return *this;
  }

  void swap(BinaryTree<Key, Value>& other) noexcept {
    std::swap(root, other.root);
    std::swap(treeSize, other.treeSize);
  }
};

template <typename Key, typename Value>
class BinaryTree<Key, Value>::Iterator {
 private:
  TreeNode<Key, Value>* node;

 public:
  Iterator() : node(nullptr) {}
  explicit Iterator(TreeNode<Key, Value>* node) : node(node) {}

  Iterator& operator++() {
    if (node->right) {
      node = node->right;
      while (node->left) {
        node = node->left;
      }
    } else {
      while (node->parent &&
             (node->parent ? node == node->parent->right : false)) {
        node = node->parent;
      }
      node = node->parent;
    }

    return *this;
  }

  Iterator& operator--() {
    if (node->left) {
      node = node->left;
      while (node->right) {
        node = node->right;
      }
    } else {
      while (node->parent &&
             (node->parent ? node == node->parent->left : false)) {
        node = node->parent;
      }
      node = node->parent;
    }

    return *this;
  }

  bool operator==(const Iterator& other) const { return node == other.node; }
  bool operator!=(const Iterator& other) const { return node != other.node; }

  TreeNode<Key, Value>* operator*() const { return node; }
};

template <typename Key, typename Value>
class BinaryTree<Key, Value>::ConstIterator {
 private:
  const TreeNode<Key, Value>* node;

 public:
  ConstIterator() : node(nullptr) {}
  explicit ConstIterator(const TreeNode<Key, Value>* node) : node(node) {}

  ConstIterator& operator++() {
    if (node->right) {
      node = node->right;
      while (node->left) {
        node = node->left;
      }
    } else {
      while (node->parent &&
             (node->parent ? node == node->parent->right : false)) {
        node = node->parent;
      }
      node = node->parent;
    }

    return *this;
  }

  ConstIterator& operator--() {
    if (node->left) {
      node = node->left;
      while (node->right) {
        node = node->right;
      }
    } else {
      while (node->parent &&
             (node->parent ? node == node->parent->left : false)) {
        node = node->parent;
      }
      node = node->parent;
    }

    return *this;
  }

  bool operator==(const ConstIterator& other) const {
    return node == other.node;
  }
  bool operator!=(const ConstIterator& other) const {
    return node != other.node;
  }

  std::pair<Key, Value> operator*() const {
    return std::make_pair(node->key, node->value);
  }
};

}  // namespace s21
#endif  // BINARY_TREE_H
