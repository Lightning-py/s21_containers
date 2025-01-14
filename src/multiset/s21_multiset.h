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
        copies = 0;
        for (auto const item : items) {
            insert_(item);
        }
    }

    multiset(const multiset &ms) {
        copies = 0;
        for (auto iter = ms.cbegin(); iter != ms.cend(); ++iter) {
            insert_(*iter);
        }
    }

    multiset(multiset &&ms) noexcept {
        map_.swap(ms.map_);
        std::swap(copies, ms.copies);
    }
    ~multiset() = default;
    multiset &operator=(multiset &&ms) noexcept {
        std::swap(ms.map_, map_);
        return *this;
    }

    // Multiset Iterators

    iterator begin() { return iterator(map_.begin(), 1); }
    iterator end() { return iterator(map_.end(), 1); }
    const_iterator cbegin() const { return const_iterator(map_.cbegin(), 1); }
    const_iterator cend() const { return const_iterator(map_.cend(), 1); }

    // Multiset Capacity

    [[nodiscard]] bool empty() const { return map_.empty(); }
    [[nodiscard]] size_type size() const { return map_.size() + copies; }
    [[nodiscard]] size_type max_size() const { return map_.max_size(); }

    // Multiset Modifiers

    void clear() {
        map_.clear();
        copies = 0;
    }

    iterator insert(value_type &value) {
        size_type how_many = 0;

        if (map_.contains(value)) {
            how_many = map_[value];
            copies++;
        }
        how_many++;

        return iterator(map_.insert(value, how_many).first, how_many);
    }

    iterator insert_(value_type value) {
        // return insert(value);
        size_type how_many = 0;

        if (map_.contains(value)) {
            how_many = map_[value];
            copies++;
        }
        how_many++;

        return iterator(map_.insert(value, how_many).first, how_many);
    }

    void erase(iterator pos) {
        value_type value = (*pos.it_).first;

        if (map_[value] == 1) {
            map_.erase(value);
        } else {
            map_[value] = map_[value]--;
            copies--;
        }
    }

    void swap(multiset &ms) noexcept {
        map_.swap(ms.map_);
        std::swap(copies, ms.copies);
    }

    void merge(multiset &ms) {
        for (auto iter = ms.cbegin(); iter != ms.cend(); ++iter) {
            insert_(*iter);
        }

        ms.clear();
    }

    size_type count(value_type value) { return map_[value]; }
    iterator find(const key_type &key) { return iterator(map_.find(key), 1); }
    bool contains(value_type value) { return map_.contains(value); }
    std::pair<iterator, iterator> equal_range(const key_type &key) {
        auto range = map_.find(key);
        auto lower = Iterator(range, 1);
        auto upper = Iterator(range, map_[key]);

        return std::make_pair(lower, upper);
    }

    iterator lower_bound(const key_type &key) {
        key_type lower = key_type();
        iterator result = end();
        for (auto it = begin(); it != end(); ++it) {
            if (*it < key && *it >= lower) {
                lower = *it;
                result = it;
            }
        }

        return result;
    }

    iterator upper_bound(const key_type &key) {
        key_type upper = key_type();
        iterator result = end();
        for (auto it = begin(); it != end(); ++it) {
            if (*it > key && *it <= upper) {
                upper = *it;
                result = it;
            }
        }

        return result;
    }

   private:
    map<key_type, size_type> map_;
    size_type copies{};
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

    Iterator(typename map<T, size_type>::Iterator it, const size_type index) {
        it_ = it;
        index_ = index;
    }

    value_type operator*() { return (*it_).first; }
    Iterator &operator++() {
        if (index_ < (*it_).second)
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

template <typename T>
class multiset<T>::ConstIterator {
   public:
    using size_type = multiset<T>::size_type;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = multiset<T>::key_type;
    using difference_type = std::ptrdiff_t;
    using pointer = typename map<T, size_type>::ConstIterator;
    using reference = T &;

    explicit ConstIterator(typename map<T, size_type>::ConstIterator it) {
        it_ = it;
        index_ = 1;
    }

    ConstIterator(typename map<T, size_type>::ConstIterator it,
                  const size_type index) {
        it_ = it;
        index_ = index;
    }

    value_type operator*() { return (*it_).first; }
    ConstIterator &operator++() {
        if (index_ < (*it_).second)
            index_++;
        else {
            ++it_;
            index_ = 1;
        }

        return *this;
    }

    ConstIterator &operator--() {
        if (index_ > 0)
            index_--;
        else {
            --it_;
            index_ = 1;
        }

        return *this;
    }

    ConstIterator operator++(int) {
        ConstIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    ConstIterator operator--(int) {
        ConstIterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const ConstIterator &other) const {
        return it_ == other.it_ && index_ == other.index_;
    }

    bool operator!=(const ConstIterator &other) const {
        return it_ != other.it_ || index_ != other.index_;
    }

    typename map<T, multiset<T>::size_type>::ConstIterator it_;
    size_type index_;
};

}  // namespace s21

#endif  // MULTISET_H