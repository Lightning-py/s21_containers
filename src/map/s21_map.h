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
    map(std::initializer_list<value_type> const& items);

    map(const map& m);

    map(map&& m) noexcept;
    ~map() = default;
    map& operator=(map&& m) noexcept;

    // Map element access

    mapped_type& at(const key_type& key);
    mapped_type& operator[](const key_type& key);

    // Map iterators

    iterator begin();
    iterator end();

    const_iterator cbegin() const;
    const_iterator cend() const;

    // Map Capacity

    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_type size() const;
    [[nodiscard]] static size_type max_size();

    // Map Modifiers

    void clear();

    std::pair<iterator, bool> insert(const value_type& value);
    std::pair<iterator, bool> insert(const key_type& key,
                                     const mapped_type& value);
    std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                               const mapped_type& value);

    void erase(iterator pos);
    void erase(key_type key);
    void swap(map& other) noexcept;
    void merge(map& other);

    iterator find(const key_type& key);

    bool contains(const key_type& key) const;

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

    value_type operator*() const;

    Iterator& operator++();
    Iterator& operator--();
    Iterator operator++(int);
    Iterator operator--(int);

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

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

    value_type operator*() const;

    ConstIterator& operator++();
    ConstIterator& operator--();
    ConstIterator operator++(int);
    ConstIterator operator--(int);

    bool operator==(const ConstIterator& other) const;
    bool operator!=(const ConstIterator& other) const;

   protected:
    typename BinaryTree<Key, Value>::ConstIterator iterator;
};

}  // namespace s21

#include "./s21_map.tpp"
#include "./s21_map_const_iterator.tpp"
#include "./s21_map_iterator.tpp"

#endif  // MAP_H