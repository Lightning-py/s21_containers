#ifndef SHARED
#define SHARED

#include <initializer_list>

namespace s21 {

template <typename Input, typename Output>
void copy(Input begin, Input end, Output dest) {
    while (begin != end) {
        *dest = *begin;
        ++begin;
        ++dest;
    }
}

}  // namespace s21

#endif  // SHARED
