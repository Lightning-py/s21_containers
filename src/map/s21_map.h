#ifndef MAP_H
#define MAP_H
#include "../binary_tree/binary_tree.h"

namespace s21 {

template <typename Key, typename Value>
class map {
   public:
    class Iterator;

    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = Iterator;
    using size_type = size_t;

    // Constructors

    map() = default;
    map(std::initializer_list<value_type> const& items) {
        for (auto const& item : items) {
            insert(item);
        }
    }

    map(const map& m) {
        for (Iterator it = m.begin(); it != m.end(); ++it) {
            insert(*it);
        }
    }

    map(map&& m) noexcept { std::swap(m.tree, tree); }
    ~map() = default;
    map& operator=(map&& m) noexcept {
        std::swap(tree, m.tree);
        return *this;
    }

    // Map element access

    mapped_type& at(const key_type& key) {
        auto it = find(key);

        if (it == tree.end()) {
            throw std::out_of_range("key not found");
        }

        return it->second;
    }

    mapped_type& operator[](const key_type& key) {
        auto node = tree.get(key);

        if (node == tree.end()) {
            tree.insert(key, mapped_type());
            node = tree.get(key);
        }

        return (*node)->value;
    }

    // Map iterators

    Iterator begin() { return Iterator(tree.begin()); }
    Iterator end() { return Iterator(tree.end()); }

    // Map Capacity

    [[nodiscard]] bool empty() const { return tree.size() == 0; }
    [[nodiscard]] size_type size() const { return tree.size(); }
    [[nodiscard]] static size_type max_size() {
        return std::numeric_limits<size_type>::max();
    }

    // Map Modifiers

    void clear() { tree.clear(); }
    std::pair<iterator, bool> insert(const value_type& value) {
        return insert(value.first, value.second);
    }

    std::pair<iterator, bool> insert(const key_type& key,
                                     const mapped_type& value) {
        auto node = tree.get(key);

        if (node != tree.end() && (*node)->value == value) {
            return std::make_pair(iterator(node), false);
        }

        tree.insert(key, value);
        node = tree.get(key);
        return std::make_pair(iterator(node), true);
    }

    std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                               const mapped_type& value) {
        return insert(key, value);
    }

    void erase(iterator pos) { tree.remove((*pos).first); }
    void erase(key_type key) { tree.erase(key); }
    void swap(map& other) noexcept { tree.swap(other.tree); }
    void merge(map& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            insert(*it);
        }

        other.clear();
    }

    bool contains(const key_type& key) const {
        return tree.get(key) != tree.end();
    }

   private:
    BinaryTree<key_type, mapped_type> tree;
};

template <typename Key, typename Value>
class map<Key, Value>::Iterator {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = map<Key, Value>::value_type;
    using difference_type = std::ptrdiff_t;
    using pointer = TreeNode<Key, Value>*;
    using reference = TreeNode<Key, Value>&;

    Iterator() : iterator() {}

    explicit Iterator(const TreeNode<Key, Value>* ptr)
        : iterator(BinaryTree<Key, Value>::Iterator(ptr)) {}
    explicit Iterator(typename BinaryTree<Key, Value>::Iterator itr)
        : iterator(itr) {}

    reference operator*() const {
        return std::make_pair((*iterator)->key, (*iterator)->value);
    };

    Iterator& operator++() {
        ++iterator;
        return *this;
    }

    Iterator& operator--() {
        --iterator;
        return *this;
    }

    Iterator operator++(int) {
        Iterator tmp = *this;
        ++iterator;
        return tmp;
    }

    Iterator operator--(int) {
        Iterator tmp = *this;
        --iterator;
        return tmp;
    }

    bool operator==(const Iterator& other) const {
        return iterator == other.iterator;
    }

    bool operator!=(const Iterator& other) const {
        return !(iterator == other.iterator);
    }

   private:
    typename BinaryTree<Key, Value>::Iterator iterator;
};

}  // namespace s21

#endif  // MAP_H