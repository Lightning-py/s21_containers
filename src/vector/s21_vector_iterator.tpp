//
// Created by sergey on 04.12.24.
//
#pragma once

namespace s21 {

template <typename T>
typename vector<T>::reference vector<T>::VectorIterator::operator*() {
    return *ptr_;
}

template <typename T>
typename vector<T>::VectorIterator& vector<T>::VectorIterator::operator++() {
    ++ptr_;
    return *this;
}

template <typename T>
typename vector<T>::VectorIterator& vector<T>::VectorIterator::operator--() {
    --ptr_;
    return *this;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator++(int) {
    VectorIterator tmp = *this;
    ++ptr_;
    return tmp;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator--(int) {
    VectorIterator tmp = *this;
    --ptr_;
    return tmp;
}

template <typename T>
bool vector<T>::VectorIterator::operator==(const VectorIterator& other) const {
    return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator!=(const VectorIterator& other) const {
    return ptr_ != other.ptr_;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator+(int n) {
    return iterator(ptr_ + n);
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator-(int n) {
    return iterator(ptr_ - n);
}

template <typename T>
int vector<T>::VectorIterator::operator-(const VectorIterator& other) {
    return ptr_ - other.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator<(const VectorIterator& other) const {
    return ptr_ < other.ptr_;
}

}  // namespace s21