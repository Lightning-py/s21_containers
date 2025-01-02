//
// Created by sergey on 02.01.25.
//

#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "../map/s21_map.h"

namespace s21 {

template <typename T>
class multiset {
   public:
    class MultisetIterator;
    class MultisetConstIterator;

    using key_type = T;
    using value_type = size_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = MultisetIterator<T>;
    using const_iterator = MultisetConstIterator<T>;
    using size_type = size_t;

   private:
    map<key_type, size_type> map_;
};

}  // namespace s21

#endif  // S21_MULTISET_H
