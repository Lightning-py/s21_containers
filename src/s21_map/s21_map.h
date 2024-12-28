#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <optional>
#include <stdexcept>
#include <stack>
#include <vector>

namespace s21 {

    template<typename Key, typename Value>
    struct Node {
        Key key;
        Value value;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(Key k, Value v) : key(k), value(v) {}
    };

    template<typename Key, typename Value>
    class Map {
    private:
        Node<Key, Value>* root = nullptr;
        size_t treeSize = 0;

        Node<Key, Value>* insert_(Node<Key, Value>* node, const Key& key, Value value) {
            if (!node) {
                ++treeSize;
                return new Node<Key, Value>(key, value);
            }
            if (key < node->key) {
                node->left = insert_(node->left, key, value);
            } else if (key > node->key) {
                node->right = insert_(node->right, key, value);
            }
            return node;
        }

        Node<Key, Value>* findMin_(Node<Key, Value>* node) {
            while (node && node->left) {
                node = node->left;
            }
            return node;
        }

        Node<Key, Value>* find_(Node<Key, Value>* node, const Key& key) const {
            if (!node) return nullptr;
            if (key < node->key) return find_(node->left, key);
            if (key > node->key) return find_(node->right, key);
            return node;
        }

        Node<Key, Value>* remove_(Node<Key, Value>* node, const Key& key) {
            if (!node) return nullptr;

            if (key < node->key) {
                node->left = remove_(node->left, key);
            } else if (key > node->key) {
                node->right = remove_(node->right, key);
            } else {
                if (!node->left) {
                    Node<Key, Value>* right = node->right;
                    delete node;
                    --treeSize;
                    return right;
                } else if (!node->right) {
                    Node<Key, Value>* left = node->left;
                    delete node;
                    --treeSize;
                    return left;
                }
                Node<Key, Value>* successor = findMin_(node->right);
                node->key = successor->key;
                node->value = successor->value;
                node->right = remove_(node->right, successor->key);
            }
            return node;
        }

        std::optional<Value> get_(Node<Key, Value>* node, const Key& key) const {
            if (!node) return std::nullopt;
            if (key < node->key) return get_(node->left, key);
            if (key > node->key) return get_(node->right, key);
            return node->value;
        }

        void clear_(Node<Key, Value>* node) {
            if (node) {
                clear_(node->left);
                clear_(node->right);
                delete node;
            }
        }

    public:
        Map() = default;

        ~Map() {
            clear_(root);
        }

        Value &operator[](const Key &key) {
            Node<Key, Value>* node = find_(root, key);
            if (node) {
                return node->value;
            }

            root = insert_(root, key, Value());
            node = find_(root, key);
            return node->value;
        }

        void insert(const std::pair<Key, Value> pair) {
            root = insert_(root, pair.first, pair.second);
        }

        void remove(const Key& key) {
            root = remove_(root, key);
        }

        Value& get(const Key& key) {
            auto result = get_(root, key);
            if (!result) throw std::out_of_range("Key not found");
            return *result;
        }

        const Value& get(const Key& key) const {
            auto result = get_(root, key);
            if (!result) throw std::out_of_range("Key not found");
            return *result;
        }

        size_t size() const {
            return treeSize;
        }

        bool empty() const {
            return treeSize == 0;
        }

        bool contains(const Key& key) const {
            return find_(root, key) != nullptr;
        }

        void clear() {
            clear_(root);
            root = nullptr;
            treeSize = 0;
        }

        void swap(Map& other) {
            std::swap(root, other.root);
            std::swap(treeSize, other.treeSize);
        }

        Value getOrDefault(const Key& key, const Value& defaultValue) const {
            auto result = get_(root, key);
            return result ? *result : defaultValue;
        }

        std::vector<Value> values() const {
            std::vector<Value> result;
            for (auto it = begin(); it != end(); ++it) {
                result.push_back(it->second);
            }
            return result;
        }

        std::vector<Key> keys() const {
            std::vector<Key> result;
            for (auto it = begin(); it != end(); ++it) {
                result.push_back(it->first);
            }
            return result;
        }

        class Iterator {
        private:
            Node<Key, Value>* current;
            std::stack<Node<Key, Value>*> stack;

            void pushLeft(Node<Key, Value>* node) {
                while (node) {
                    stack.push(node);
                    node = node->left;
                }
            }

        public:
            Iterator(Node<Key, Value>* root = nullptr) : current(nullptr) {
                if (root) pushLeft(root);
                if (!stack.empty()) current = stack.top();
            }

            std::pair<const Key&, Value&> operator*() {
                return {current->key, current->value};
            }

            Iterator& operator++() {
                if (stack.empty()) {
                    current = nullptr;
                    return *this;
                }
                Node<Key, Value>* node = stack.top();
                stack.pop();
                if (node->right) pushLeft(node->right);
                current = stack.empty() ? nullptr : stack.top();
                return *this;
            }

            bool operator==(const Iterator& other) const {
                return current == other.current;
            }

            bool operator!=(const Iterator& other) const {
                return current != other.current;
            }
        };

        Iterator begin() {
            return Iterator(root);
        }

        Iterator end() {
            return Iterator();
        }
    };

}

#endif // MAP_H