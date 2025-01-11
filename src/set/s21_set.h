#ifndef S21_SET_H
#define S21_SET_H

#include <utility>

#include "../map/s21_map.h"

namespace s21 {

template <typename Key>
class set {
   private:
    map<Key, std::monostate> map_;

   public:
    set() = default;
    ~set() = default;

    void insert(const Key& key) { map_.insert({key, std::monostate()}); }

    void remove(const Key key) { map_.erase(key); }

    bool contains(const Key& key) const { return map_.contains(key); }

    size_t size() const { return map_.size(); }

    bool empty() const { return map_.empty(); }

    void clear() { map_.clear(); }

    using Iterator = typename map<Key, std::monostate>::Iterator;

    Iterator begin() { return map_.begin(); }

    Iterator end() { return map_.end(); }

    bool operator==(set& other) {
        if (size() != other.size()) return false;
        for (auto it = begin(), otherIt = other.begin(); it != end();
             ++it, ++otherIt) {
            if (*it != *otherIt) return false;
        }
        return true;
    }
};

}  // namespace s21

#endif  // S21_SET_H
