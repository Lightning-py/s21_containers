//
// Created by sergey on 11.12.24.
//

#pragma once
#include "linked_list.h"
namespace s21 {
template <typename T>
typename list<T>::const_reference list<T>::ListConstIterator::operator*()
    const {
    return node->data;
}

template <typename T>
typename list<T>::ListConstIterator& list<T>::ListConstIterator::operator++() {
    node = node->next;
    return *this;
}

template <typename T>
typename list<T>::ListConstIterator& list<T>::ListConstIterator::operator--() {
    node = node->prev;
    return *this;
}
template <typename T>
bool list<T>::ListConstIterator::operator==(
    const ListConstIterator& other) const {
    return node == other.node;
}

template <typename T>
bool list<T>::ListConstIterator::operator!=(
    const ListConstIterator& other) const {
    return !(*this == other);
}

template <typename T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator++(
    int) {
    ListConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator--(
    int) {
    ListConstIterator tmp = *this;
    --(*this);
    return tmp;
}

template <typename T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator+(
    int n) const {
    ListConstIterator tmp = *this;
    for (int i = 0; i < n; ++i) ++tmp;
    return tmp;
}

template <typename T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator-(
    int n) const {
    ListConstIterator tmp = *this;
    for (int i = 0; i < n; ++i) --tmp;
    return tmp;
}

template <typename T>
int list<T>::ListConstIterator::operator-(
    const ListConstIterator& other) const {
    ListConstIterator tmp = other;
    size_type counter = 0;
    while (tmp != *this) {
        ++tmp;
        ++counter;
    }

    return static_cast<int>(counter);
}

}  // namespace s21