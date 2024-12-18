#pragma once
#include "linked_list.h"

namespace s21 {
template <typename T>
typename list<T>::reference list<T>::ListIterator::operator*() {
    return node->data;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator++() {
    if (node) node = node->next;
    return *this;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator--() {
    if (node) node = node->prev;
    return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator++(int) {
    ListIterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator--(int) {
    ListIterator tmp = *this;
    --(*this);
    return tmp;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator+(int n) {
    for (int i = 0; i < n; ++i) {
        ++(*this);
    }

    return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator-(int n) {
    for (int i = 0; i < n; ++i) {
        ++(*this);
    }

    return *this;
}

// template <typename T>
// int List<T>::ListIterator::operator-(const List<T>::ListIterator& other);

template <typename T>
bool list<T>::ListIterator::operator==(const ListIterator& other) const {
    return (node == other.node);
}

template <typename T>
bool list<T>::ListIterator::operator!=(const ListIterator& other) const {
    return !(node == other.node);
}
}  // namespace s21