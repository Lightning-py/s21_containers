#pragma once

namespace s21 {
template <typename Key, typename Value>
typename map<Key, Value>::value_type map<Key, Value>::ConstIterator::operator*()
    const {
  return *iterator;
};

template <typename Key, typename Value>
typename map<Key, Value>::ConstIterator&
map<Key, Value>::ConstIterator::operator++() {
  ++iterator;
  return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::ConstIterator&
map<Key, Value>::ConstIterator::operator--() {
  --iterator;
  return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::ConstIterator
map<Key, Value>::ConstIterator::operator++(int) {
  ConstIterator tmp = *this;
  ++iterator;
  return tmp;
}

template <typename Key, typename Value>
typename map<Key, Value>::ConstIterator
map<Key, Value>::ConstIterator::operator--(int) {
  ConstIterator tmp = *this;
  --iterator;
  return tmp;
}

template <typename Key, typename Value>
bool map<Key, Value>::ConstIterator::operator==(
    const ConstIterator& other) const {
  return iterator == other.iterator;
}

template <typename Key, typename Value>
bool map<Key, Value>::ConstIterator::operator!=(
    const ConstIterator& other) const {
  return !(iterator == other.iterator);
}

}  // namespace s21