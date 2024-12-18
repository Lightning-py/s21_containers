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
}

template <typename T>
list<T>::ListConstIterator& list<T>::ListConstIterator::operator--() {
    node = node->prev;
}

}  // namespace s21