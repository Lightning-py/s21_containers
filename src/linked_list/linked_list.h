//
// Created by sergey on 09.12.24.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../shared/shared.cpp"
#include "node.h"

namespace s21 {

template <typename T>
class list {
   public:
    class ListIterator;
    class ListConstIterator;

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = ListIterator;
    using const_iterator = ListConstIterator;
    using size_type = size_t;
    using pointer = T*;
    using const_pointer = const T*;

    list() : head(nullptr), tail(nullptr), size_(0) {}
    explicit list(size_type n);
    list(std::initializer_list<value_type> const& items);
    list(const list& other);
    list(list&& other) noexcept;
    list& operator=(list&& other) noexcept;
    ~list();

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }  // always returns a nullptr

    const_iterator cbegin() const { return const_iterator(head); }
    const_iterator cend() const {
        return const_iterator(tail->next);
    }  // always returns a nullptr

    iterator rbegin() { return iterator(tail); }
    iterator rend() { return iterator(nullptr); }

    const_reference front() const { return head->data; }
    const_reference back() const { return tail->data; }

    [[nodiscard]] bool empty() const { return size_ == 0; }

    void clear();
    iterator insert(iterator pos, const_reference value);
    iterator insert(const_iterator pos, const_reference value);
    void erase(iterator pos);
    void push_back(const_reference value);
    void pop_back();
    void push_front(const_reference value);
    void pop_front();

    void swap(list& other) noexcept;
    void merge(list& other);
    void splice(const_iterator pos, list& other);
    void reverse();
    void unique();
    void sort();

    [[nodiscard]] size_type size() const { return size_; }

   protected:
    ListNode<T>* head;
    ListNode<T>* tail;
    size_type size_;

    void mergeSort(list<T>& other);
};

template <typename T>
class list<T>::ListIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = list<T>::value_type;
    using difference_type = std::ptrdiff_t;
    using pointer = ListNode<T>*;
    using reference = list<T>::reference;

    ListIterator() : node(nullptr) {}
    explicit ListIterator(pointer node) : node(node) {}
    explicit ListIterator(ListConstIterator& other) : node(other.node) {}

    reference operator*();
    ListIterator& operator++();
    ListIterator& operator--();
    ListIterator operator++(int);
    ListIterator operator--(int);
    ListIterator operator+(int n) const;
    ListIterator operator-(int n) const;
    int operator-(const ListIterator& other) const;
    bool operator==(const ListIterator& other) const;
    bool operator!=(const ListIterator& other) const;

    pointer pointer_() { return node; }

   protected:
    pointer node;
};

template <typename T>
class list<T>::ListConstIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = list<T>::value_type;
    using difference_type = std::ptrdiff_t;
    using pointer = const ListNode<T>*;
    using reference = list<T>::const_reference;

    explicit ListConstIterator(const pointer node) : node(node) {}
    explicit ListConstIterator(const ListIterator& other) : node(other.node) {}

    const_reference operator*() const;
    ListConstIterator& operator++();
    ListConstIterator& operator--();
    ListConstIterator operator++(int);
    ListConstIterator operator--(int);
    ListConstIterator operator+(int n) const;
    ListConstIterator operator-(int n) const;
    int operator-(const ListConstIterator& other) const;
    bool operator==(const ListConstIterator& other) const;
    bool operator!=(const ListConstIterator& other) const;

    pointer pointer_() const { return node; }

   protected:
    pointer node;
};

}  // namespace s21

#include "linked_list.tpp"
#include "linked_list_const_iterator.tpp"
#include "linked_list_iterator.tpp"

#endif  // LINKED_LIST_H
