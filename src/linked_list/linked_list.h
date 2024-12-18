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

    list() : head(nullptr), tail(nullptr), size_(0) {}
    explicit list(size_type n);
    list(std::initializer_list<value_type> const& items);
    list(const list& other);
    list(list&& other) noexcept;
    list& operator=(list&& other) noexcept;
    ~list();

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(tail->next); }  // always returns a nullptr

    iterator rbegin() { return iterator(tail); }
    iterator rend() { return iterator(nullptr); }

    const_reference front() const { return head->value; }
    const_reference back() const { return tail->value; }

    bool empty() const { return size_ == 0; }

    void clear();
    iterator insert(iterator pos, const_reference value);
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

    size_type size() const { return size_; }

   private:
    ListNode<T>* head;
    ListNode<T>* tail;
    size_type size_;

    void mergeSort(list<T>& other);
};

template <typename T>
class list<T>::ListIterator {
   public:
    ListIterator() : node(nullptr) {}
    explicit ListIterator(ListNode<T>* node) : node(node) {}

    reference operator*();
    ListIterator& operator++();
    ListIterator& operator--();
    ListIterator operator++(int);
    ListIterator operator--(int);
    ListIterator operator+(int n);
    ListIterator operator-(int n);
    int operator-(const ListIterator& other);
    bool operator==(const ListIterator& other) const;
    bool operator!=(const ListIterator& other) const;

    ListNode<T>* pointer() { return node; }

   private:
    ListNode<T>* node;
};

template <typename T>
class list<T>::ListConstIterator {
   public:
    explicit ListConstIterator(ListNode<T> node) : node(node) {}

    const_reference operator*() const;
    ListConstIterator& operator++();
    ListConstIterator& operator--();

    const ListNode<T>* pointer() const { return node; }

   private:
    const ListNode<T>* node;
};

}  // namespace s21

#include "linked_list.tpp"
#include "linked_list_const_iterator.tpp"
#include "linked_list_iterator.tpp"

#endif  // LINKED_LIST_H
