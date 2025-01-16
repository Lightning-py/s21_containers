#pragma once
#include "s21_list.h"

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
typename list<T>::ListIterator list<T>::ListIterator::operator+(int n) const {
  auto tmp = *this;
  for (int i = 0; i < n; ++i) {
    ++(tmp);
  }

  return tmp;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator-(int n) const {
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

template <typename T>
int list<T>::ListIterator::operator-(const ListIterator& other) const {
  ListIterator tmp(other.pointer_());
  size_type counter = 0;

  while (tmp != *this) {
    ++tmp;
    ++counter;
  }

  return static_cast<int>(counter);
}

}  // namespace s21