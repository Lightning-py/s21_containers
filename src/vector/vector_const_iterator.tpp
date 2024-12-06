//
// Created by sergey on 05.12.24.
//

#include "vector.h"

namespace s21 {

template <typename T>
typename vector<T>::const_reference vector<T>::VectorConstIterator::operator*()
    const {
    return *ptr_;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator++() {
    ++ptr_;
    return *this;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator--() {
    --ptr_;
    return *this;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator++(int) {
    VectorConstIterator tmp = *this;
    ++ptr_;
    return tmp;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator--(int) {
    VectorConstIterator tmp = *this;
    --ptr_;
    return tmp;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator==(
    const VectorConstIterator& other) const {
    return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator!=(
    const VectorConstIterator& other) const {
    return ptr_ != other.ptr_;
}

}  // namespace s21