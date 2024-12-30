#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <optional>
#include <stdexcept>
#include <stack>
#include <vector>

namespace s21 {

    template<typename Key, typename Value>
    struct TreeNode {
        Key key;
        Value value;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
        TreeNode* parent = nullptr;

        TreeNode(Key k, Value v) : key(k), value(v) {}
    };

    template<typename Key, typename Value>
    class Map {
    private:
        TreeNode<Key, Value>* root = nullptr;
        size_t treeSize = 0;

        TreeNode<Key, Value>* insert_(TreeNode<Key, Value>* node, const Key& key, Value value, TreeNode<Key, Value>* parent = nullptr) {
            if (!node) {
                ++treeSize;
                TreeNode<Key, Value>* newNode = new TreeNode<Key, Value>(key, value);
                newNode->parent = parent;
                return newNode;
            }
            if (key < node->key) {
                node->left = insert_(node->left, key, value, node);
            } else if (key > node->key) {
                node->right = insert_(node->right, key, value, node);
            }
            return node;
        }

        TreeNode<Key, Value>* findMin_(TreeNode<Key, Value>* node) {
            while (node && node->left) {
                node = node->left;
            }
            return node;
        }

        TreeNode<Key, Value>* find_(TreeNode<Key, Value>* node, const Key& key) const {
            if (!node) return nullptr;
            if (key < node->key) return find_(node->left, key);
            if (key > node->key) return find_(node->right, key);
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
                } else if (!node->right) {
                    TreeNode<Key, Value>* left = node->left;
                    delete node;
                    --treeSize;
                    return left;
                }
                TreeNode<Key, Value>* successor = findMin_(node->right);
                node->key = successor->key;
                node->value = successor->value;
                node->right = remove_(node->right, successor->key);
            }
            return node;
        }

        std::optional<Value> get_(TreeNode<Key, Value>* node, const Key& key) const {
            if (!node) return std::nullopt;
            if (key < node->key) return get_(node->left, key);
            if (key > node->key) return get_(node->right, key);
            return node->value;
        }

        void clear_(TreeNode<Key, Value>* node) {
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
            TreeNode<Key, Value>* node = find_(root, key);
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
            TreeNode<Key, Value>* node = find_(root, key);
            if (!node) {
                throw std::out_of_range("Key not found");
            }
            return node->value;
        }

        const Value& get(const Key& key) const {
            TreeNode<Key, Value>* node = find_(root, key);
            if (!node) {
                throw std::out_of_range("Key not found");
            }
            return node->value;
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

        class Iterator {
        private:
            TreeNode<Key, Value>* current;

            TreeNode<Key, Value>* findNext(TreeNode<Key, Value>* node) {
                if (node->right) {
                    node = node->right;
                    while (node->left) {
                        node = node->left;
                    }
                } else {
                    while (node->parent && node == node->parent->right) {
                        node = node->parent;
                    }
                    node = node->parent;
                }
                return node;
            }

        public:
            explicit Iterator(TreeNode<Key, Value>* start = nullptr) : current(start) {
                if (current) {
                    while (current->left) {
                        current = current->left;
                    }
                }
            }

            std::pair<const Key&, Value&> operator*() const {
                return {current->key, current->value};
            }

            Iterator& operator++() {
                if (current) {
                    current = findNext(current);
                }
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
            return Iterator(nullptr);
        }
    };

}

#endif // MAP_H