//
// Created by sergey on 21.12.24.
//

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

namespace s21 {

template <typename T, typename F>
struct Node {
    T key;
    F value;
    Node<T, F>* left;
    Node<T, F>* right;

    Node<T, F>(T key, F&& value)
        : key(key), value(value), left(nullptr), right(nullptr) {}

    Node<T, F>(T key, F value)
        : key(key), value(value), left(nullptr), right(nullptr) {}

    ~Node() = default;
};

template <typename T, typename F>
class Tree {
   private:
    Node<T, F>* root;
    size_t size;

    F get_(Node<T, F>* node, T key) {
        if (node == nullptr) return F();

        if (node->key > key) return get_(node->left, key);
        if (node->key < key) return get_(node->right, key);
        return node->value;
    }

    Node<T, F>* insert_(Node<T, F>* node, T key, F value) {
        if (node == nullptr) {
            node = new Node<T, F>(key, value);
            size++;
            return node;
        }

        if (node->key > key)
            node->left = insert_(node->left, key, value);
        else
            node->right = insert_(node->right, key, value);
        return node;
    }

    Node<T, F>* getmin(Node<T, F>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node<T, F>* delete_(Node<T, F>* node, T key) {
        if (node == nullptr) return nullptr;
        if (node->key > key) {
            node->left = delete_(node->left, key);
            return node;
        }
        if (node->key < key) {
            node->right = delete_(node->right, key);
            return node;
        }

        // ключ найден, удаляем
        if (node->left == nullptr && node->right == nullptr) {
            size--;
            delete node;
            return nullptr;
        }

        if (node->left == nullptr) {
            Node<T, F>* temp = node->right;
            size--;
            delete node;
            return temp;
        }

        if (node->right == nullptr) {
            Node<T, F>* temp = node->left;
            size--;
            delete node;
            return temp;
        }

        Node<T, F>* min = getmin(node->right);
        node->key = min->key;
        node->value = min->value;

        node->right = delete_(node->right, node->key);
        return node;
    }

    void print_(Node<T, F>* node) {
        if (node != nullptr) {
            print_(node->left);
            std::cout << node->key << "\t" << node->value << std::endl;
            print_(node->right);
        }
    }

   public:
    Tree() : root(nullptr), size(0) {}
    ~Tree() {
        while (size) remove(root->key);
    }

    void insert(T key, F value) noexcept { root = insert_(root, key, value); }
    F get(T key) noexcept { return get_(root, key); }
    void print() const noexcept { print_(root); }
    void remove(T key) { root = delete_(root, key); }
    size_t getSize() const noexcept { return size; }
};

} // namespace s21

#endif //BINARY_TREE_H
