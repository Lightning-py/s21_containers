#ifndef S21_SET_H
#define S21_SET_H

#include "../map/map.h"
#include <utility>

namespace s21 {

    template<typename Key>
    class Set {
    private:
        Map<Key, std::monostate> map;

    public:
        Set() = default;
        ~Set() = default;

        void insert(const Key& key) {
            map.insert({key, std::monostate()});
        }

        void remove(const Key& key) {
            map.remove(key);
        }

        bool contains(const Key& key) const {
            return map.contains(key);
        }

        size_t size() const {
            return map.size();
        }

        bool empty() const {
            return map.empty();
        }

        void clear() {
            map.clear();
        }

        using Iterator = typename Map<Key, std::monostate>::Iterator;

        Iterator begin() {
            return map.begin();
        }

        Iterator end() {
            return map.end();
        }

        bool operator==(Set& other) {
            if (size() != other.size()) return false;
            for (auto it = begin(), otherIt = other.begin(); it != end(); ++it, ++otherIt) {
                if (*it != *otherIt) return false;
            }
            return true;
        }
    };

}

#endif //S21_SET_H
