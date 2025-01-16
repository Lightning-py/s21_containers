

#pragma once

namespace s21 {

// Constructors

template <typename Key, typename Value>
map<Key, Value>::map(std::initializer_list<value_type> const& items) {
  for (auto const& item : items) {
    insert(item);
  }
}

template <typename Key, typename Value>
map<Key, Value>::map(const map& m) {
  for (ConstIterator it = m.cbegin(); it != m.cend(); ++it) {
    insert((*it).first, (*it).second);
  }
}

template <typename Key, typename Value>
map<Key, Value>::map(map&& m) noexcept {
  tree.swap(m.tree);
}

template <typename Key, typename Value>
typename map<Key, Value>::map& map<Key, Value>::operator=(map&& m) noexcept {
  std::swap(tree, m.tree);
  return *this;
}

// Map element access

template <typename Key, typename Value>
typename map<Key, Value>::mapped_type& map<Key, Value>::at(
    const key_type& key) {
  auto it = tree.get(key);

  if (it == tree.end()) {
    throw std::out_of_range("key not found");
  }

  return (*it)->value;
}

template <typename Key, typename Value>
typename map<Key, Value>::mapped_type& map<Key, Value>::operator[](
    const key_type& key) {
  auto node = tree.get(key);

  if (node == tree.end()) {
    tree.insert(key, mapped_type());
    node = tree.get(key);
  }

  return (*node)->value;
}

// Map iterators

template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::begin() {
  return Iterator(tree.begin());
}

template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::end() {
  return Iterator(tree.end());
}

template <typename Key, typename Value>
typename map<Key, Value>::const_iterator map<Key, Value>::cbegin() const {
  return const_iterator(tree.cbegin());
}
template <typename Key, typename Value>
typename map<Key, Value>::const_iterator map<Key, Value>::cend() const {
  return const_iterator(tree.cend());
}

// Map Capacity
template <typename Key, typename Value>
[[nodiscard]] bool map<Key, Value>::empty() const {
  return tree.size() == 0;
}

template <typename Key, typename Value>
[[nodiscard]] typename map<Key, Value>::size_type map<Key, Value>::size()
    const {
  return tree.size();
}

template <typename Key, typename Value>
[[nodiscard]] typename map<Key, Value>::size_type map<Key, Value>::max_size() {
  return std::numeric_limits<size_type>::max();
}

// Map Modifiers

template <typename Key, typename Value>
void map<Key, Value>::clear() {
  tree.clear();
}

template <typename Key, typename Value>
std::pair<typename map<Key, Value>::iterator, bool> map<Key, Value>::insert(
    const value_type& value) {
  return insert(value.first, value.second);
}

template <typename Key, typename Value>
std::pair<typename map<Key, Value>::iterator, bool> map<Key, Value>::insert(
    const key_type& key, const mapped_type& value) {
  auto node = tree.get(key);

  if (node != tree.end() && (*node)->value == value) {
    return std::make_pair(iterator(node), false);
  }

  tree.insert(key, value);
  node = tree.get(key);
  return std::make_pair(iterator(node), true);
}

template <typename Key, typename Value>
std::pair<typename map<Key, Value>::iterator, bool>
map<Key, Value>::insert_or_assign(const key_type& key,
                                  const mapped_type& value) {
  return insert(key, value);
}

template <typename Key, typename Value>
void map<Key, Value>::erase(iterator pos) {
  tree.remove((*pos).first);
}

template <typename Key, typename Value>
void map<Key, Value>::erase(key_type key) {
  tree.remove(key);
}

template <typename Key, typename Value>
void map<Key, Value>::swap(map& other) noexcept {
  tree.swap(other.tree);
}

template <typename Key, typename Value>
void map<Key, Value>::merge(map& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }

  other.clear();
}

template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::find(const key_type& key) {
  auto it = tree.get(key);
  if (it == tree.end()) {
    return end();
  }
  return iterator(it);
}

template <typename Key, typename Value>
bool map<Key, Value>::contains(const key_type& key) const {
  return tree.get(key) != tree.end();
}

template <typename Key, typename Value>
template <typename... Args>
vector<std::pair<typename map<Key, Value>::iterator, bool>>
map<Key, Value>::insert_many(Args&&... args) {
  // vector<value_type> tmp = {std::forward<Args>(args)...};
  // (tmp.push_back(std::forward<Args>(args)), ...);

  vector<std::pair<typename map<Key, Value>::iterator, bool>> result;

  for (const auto& pair : {args...}) {
    result.push_back(insert(pair.first, pair.second));
  }

  return result;
}

}  // namespace s21