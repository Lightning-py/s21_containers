#ifndef S21_SET_H
#define S21_SET_H

#include <utility>

#include "../map/s21_map.h"

namespace s21 {

template <typename Key>
class set {
 public:
  class Iterator;
  class ConstIterator;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  set() = default;
  set(std::initializer_list<value_type> const &items) {
    for (auto const &item : items) {
      map_.insert(item, true);
    }
  }

  set(const set &other) {
    for (auto iter = other.cbegin(); iter != other.cend(); ++iter) {
      insert(*iter);
    }
  }

  set(set &&s) noexcept {
    map_.clear();
    map_.swap(s.map_);
  }

  ~set() = default;
  set &operator=(set &&s) noexcept {
    map_ = s.map_;
    s.map_ = map<Key, bool>();
    return *this;
  }

  iterator begin() { return iterator(map_.begin()); }
  iterator end() { return iterator(map_.end()); }
  const_iterator cbegin() const { return const_iterator(map_.cbegin()); }
  const_iterator cend() const { return const_iterator(map_.cend()); }

  [[nodiscard]] bool empty() const { return map_.empty(); }
  [[nodiscard]] size_type size() const { return map_.size(); }
  [[nodiscard]] size_type max_size() const { return map_.max_size(); }

  void clear() { map_.clear(); }
  std::pair<iterator, bool> insert(const value_type &value) {
    return std::make_pair(iterator(map_.insert(value, true).first), true);
  }

  void erase(iterator pos) {
    map_.erase(static_cast<typename map<Key, bool>::iterator>(pos));
  }

  void swap(set &other) noexcept { map_.swap(other.map_); }
  void merge(set &other) { map_.merge(other.map_); }

  iterator find(const key_type &key) {
    if (map_.contains(key)) {
      return iterator(map_.find(key));
    }

    return end();
  }

  bool contains(const key_type &key) const { return map_.contains(key); }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    vector<std::pair<iterator, bool>> result;

    for (const auto item : {args...}) {
      result.push_back(insert(item));
    }

    return result;
  }

 private:
  map<Key, bool> map_;
};

template <typename Key>
class set<Key>::Iterator : public map<Key, bool>::iterator {
 public:
  explicit Iterator() = default;
  explicit Iterator(typename map<Key, bool>::iterator const &it)
      : map<Key, bool>::iterator(it) {}

  set<Key>::key_type operator*() const {
    return map<Key, bool>::iterator::operator*().first;
  }
};

template <typename Key>
class set<Key>::ConstIterator : public map<Key, bool>::const_iterator {
 public:
  explicit ConstIterator() = default;
  explicit ConstIterator(typename map<Key, bool>::const_iterator const &it)
      : map<Key, bool>::const_iterator(it) {}

  set<Key>::key_type operator*() const {
    return map<Key, bool>::const_iterator::operator*().first;
  }
};
}  // namespace s21

#endif  // S21_SET_H
