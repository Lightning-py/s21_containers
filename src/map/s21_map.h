#ifndef MAP_H
#define MAP_H
#include "../binary_tree/binary_tree.h"

namespace s21 {

template <typename Key, typename Value>
class map {
   public:
    class Iterator;
    class ConstIterator;

    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = Iterator;
    using const_iterator = ConstIterator;
    using size_type = size_t;

    // Constructors

    map() = default;
    map(std::initializer_list<value_type> const& items) {
        for (auto const& item : items) {
            insert(item);
        }
    }

    map(const map& m) {
        for (ConstIterator it = m.cbegin(); it != m.cend(); ++it) {
            insert((*it).first, (*it).second);
        }
    }

    map(map&& m) noexcept { tree.swap(m.tree); }
    ~map() = default;
    map& operator=(map&& m) noexcept {
        std::swap(tree, m.tree);
        return *this;
    }

    // Map element access

    mapped_type& at(const key_type& key) {
        auto it = tree.get(key);

        if (it == tree.end()) {
            throw std::out_of_range("key not found");
        }

        return (*it)->value;
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

    iterator begin() { return Iterator(tree.begin()); }
    iterator end() { return Iterator(tree.end()); }

    const_iterator cbegin() const { return const_iterator(tree.cbegin()); }
    const_iterator cend() const { return const_iterator(tree.cend()); }

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
    void erase(key_type key) { tree.remove(key); }
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

    value_type operator*() const {
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

   protected:
    typename BinaryTree<Key, Value>::Iterator iterator;
};

template <typename Key, typename Value>
class map<Key, Value>::ConstIterator {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = map<Key, Value>::value_type;
    using difference_type = std::ptrdiff_t;
    using pointer = TreeNode<Key, Value>*;
    using reference = TreeNode<Key, Value>&;

    ConstIterator() : iterator() {}

    explicit ConstIterator(const TreeNode<Key, Value>* ptr)
        : iterator(BinaryTree<Key, Value>::Iterator(ptr)) {}
    explicit ConstIterator(typename BinaryTree<Key, Value>::ConstIterator itr)
        : iterator(itr) {}

    value_type operator*() const { return *iterator; };

    ConstIterator& operator++() {
        ++iterator;
        return *this;
    }

    ConstIterator& operator--() {
        --iterator;
        return *this;
    }

    ConstIterator operator++(int) {
        ConstIterator tmp = *this;
        ++iterator;
        return tmp;
    }

    ConstIterator operator--(int) {
        ConstIterator tmp = *this;
        --iterator;
        return tmp;
    }

    bool operator==(const ConstIterator& other) const {
        return iterator == other.iterator;
    }

    bool operator!=(const ConstIterator& other) const {
        return !(iterator == other.iterator);
    }

   protected:
    typename BinaryTree<Key, Value>::ConstIterator iterator;
};

}  // namespace s21

#endif  // MAP_H