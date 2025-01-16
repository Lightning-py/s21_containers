
namespace s21 {

template <typename Key, typename Value>
typename map<Key, Value>::value_type
map<Key, Value>::Iterator::operator*() const {
  return std::make_pair((*iterator)->key, (*iterator)->value);
};

template <typename Key, typename Value>
typename map<Key, Value>::Iterator &map<Key, Value>::Iterator::operator++() {
  ++iterator;
  return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::Iterator &map<Key, Value>::Iterator::operator--() {
  --iterator;
  return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::Iterator map<Key, Value>::Iterator::operator++(int) {
  Iterator tmp = *this;
  ++iterator;
  return tmp;
}

template <typename Key, typename Value>
typename map<Key, Value>::Iterator map<Key, Value>::Iterator::operator--(int) {
  Iterator tmp = *this;
  --iterator;
  return tmp;
}

template <typename Key, typename Value>
bool map<Key, Value>::Iterator::operator==(const Iterator &other) const {
  return iterator == other.iterator;
}

template <typename Key, typename Value>
bool map<Key, Value>::Iterator::operator!=(const Iterator &other) const {
  return !(iterator == other.iterator);
}

} // namespace s21
