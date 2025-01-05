#ifndef MULTISET_H
#define MULTISET_H

#include "../map/s21_map.h"
#include "../shared/shared.cpp"

namespace s21 {

template <typename T>
class multiset {
   public:
    class Iterator;
    class ConstIterator;

    using key_type = T;
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = Iterator;
    using const_iterator = ConstIterator;
    using size_type = size_t;

    // constructors

    multiset() = default;
    multiset(std::initializer_list<value_type> const &items) {
        for (auto const &item : items) {
            insert(item);
        }
    }

    multiset(const multiset &ms) {
        for (auto const &item : ms) {
            insert(item);
        }
    }

    multiset(multiset &&ms) noexcept { std::swap(ms.map_, map_); }
    ~multiset() = default;
    multiset &operator=(multiset &&ms) noexcept {
        std::swap(ms.map_, map_);
        return *this;
    }

    // Multiset Iterators

    iterator begin() { return iterator(map_.begin(), 1); }
    iterator end() { return iterator(map_.end(), 1); }

    // Multiset Capacity

    [[nodiscard]] bool empty() const { return map_.empty(); }
    [[nodiscard]] size_type size() const { return map_.size(); }
    [[nodiscard]] size_type max_size() const { return map_.max_size(); }

    // Multiset Modifiers

    void clear() { map_.clear(); }

    iterator insert(value_type &value) {
        size_type how_many = 0;

        if (map_.contains(value)) how_many = map_.get(value);
        how_many++;

        return iterator(map_.insertGet(value, how_many), how_many);
    }

    iterator insert(value_type value) {
        size_type how_many = 0;

        if (map_.contains(value)) how_many = map_.get(value);
        how_many++;

        return iterator(map_.insertGet(value, how_many), how_many);
    }

    void erase(iterator pos) {
        value_type value = *(pos.it_).first;

        if (map_[value] == 0) return;

        if (map_[value] == 1) {
            map_.erase(value);
        } else {
            map_[value] = map_[value]--;
        }
    }

    void swap(multiset &ms) noexcept { std::swap(ms.map_, map_); }
    void merge(multiset &ms) {
        for (auto const &item : ms) {
            insert(item);
        }

        ms.clear();
    }

    size_type count(value_type value) { return map_[value]; }
    iterator find(const key_type &key) { return map_.find(key); }
    bool contains(value_type value) { return map_.contains(value); }
    std::pair<iterator, iterator> equal_range(const key_type &key) {
        auto range = map_.find(key);
        auto lower = Iterator(range, 1);
        auto upper = Iterator(range, map_[key]);

        return std::make_pair(lower, upper);
    }

   private:
    map<key_type, size_type> map_;
};

template <typename T>
class multiset<T>::Iterator {
   public:
    using size_type = multiset<T>::size_type;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = multiset<T>::key_type;
    using difference_type = std::ptrdiff_t;
    using pointer = typename map<T, size_type>::Iterator;
    using reference = T &;

    explicit Iterator(typename map<T, size_type>::Iterator it) {
        it_ = it;
        index_ = 1;
    }

    Iterator(typename map<T, size_type>::Iterator it, size_type index) {
        it_ = it;
        index_ = index;
    }

    reference operator*() { return it_->first; }
    Iterator &operator++() {
        if (index_ < it_->second)
            index_++;
        else {
            ++it_;
            index_ = 1;
        }

        return *this;
    }

    Iterator &operator--() {
        if (index_ > 0)
            index_--;
        else {
            --it_;
            index_ = 1;
        }

        return *this;
    }

    Iterator operator++(int) {
        Iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    Iterator operator--(int) {
        Iterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const Iterator &other) const {
        return it_ == other.it_ && index_ == other.index_;
    }

    bool operator!=(const Iterator &other) const {
        return it_ != other.it_ || index_ != other.index_;
    }

    typename map<T, multiset<T>::size_type>::Iterator it_;
    size_type index_;
};

}  // namespace s21

#endif  // MULTISET_H