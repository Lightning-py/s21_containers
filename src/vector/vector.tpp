//
// Created by sergey on 04.12.24.
//
#pragma once

namespace s21 {

template <typename T>
vector<T>::vector(std::initializer_list<T> const &items)
    : size_(items.size()),
      capacity_(items.size()),
      data_(new value_type[items.size()]) {
    copy(items.begin(), items.end(), begin());
}

template <typename T>
vector<T>::vector(const vector &v) : size_(v.size()) {
    data_ = new value_type[v.capacity_];
    capacity_ = v.capacity_;
    // memcpy(data_, v.data_, size_ * sizeof(value_type));
    copy(v.cbegin(), v.cend(), begin());
}

template <typename T>
vector<T>::vector(vector &&v) noexcept
    : size_(v.size()), capacity_(v.capacity()), data_(v.data()) {
    v.data_ = nullptr;
    v.capacity_ = 0;
    v.size_ = 0;
}

template <typename T>
vector<T>::~vector() {
    delete[] data_;
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&v) noexcept {
    if (this != &v) {
        delete[] data_;
        data_ = v.data_;
        capacity_ = v.capacity_;
        size_ = v.size_;

        v.data_ = nullptr;
        v.size_ = 0;
        v.capacity_ = 0;
    }

    return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
    if (pos >= size_) {
        throw std::out_of_range("Vector Error: Index out of range");
    }

    return data_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
    return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
    if (size_ > 0) return data_[0];

    throw std::out_of_range("Vector Error: Index out of range");
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
    if (size_ > 0) return data_[size_ - 1];
    throw std::out_of_range("Vector Error: Index out of range");
}

template <typename T>
typename vector<T>::pointer vector<T>::data() const {
    return data_;
}

template <typename T>
bool vector<T>::empty() const {
    return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
    return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
    return capacity_;
}

template <typename T>
void vector<T>::reserve(const size_type size) {
    if (size < capacity_) return;

    auto new_data = new value_type[size];
    // memcpy(new_data, data_, size_ * sizeof(value_type));
    copy(begin(), end(), new_data);
    delete[] data_;
    data_ = new_data;
    capacity_ = size;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
    return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
    if (size_ < capacity_) {
        auto new_data = new value_type[size_];
        copy(this->begin(), this->end(), new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = size_;
    }
}

template <typename T>
void vector<T>::clear() {
    for (int i = 0; i < size_; ++i) this->data_[i] = T();
    size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
    int index = pos - this->begin();
    if (index >= capacity_) this->reserve(index + 1);

    for (int i = size_; i > index; --i) {
        data_[i] = data_[i - 1];
    }

    data_[index] = value;

    size_ = std::max(size_ + 1, static_cast<size_type>(index) + 1);

    return iterator(data_ + index);
}

template <typename T>
void vector<T>::erase(iterator pos) {
    int index = pos - this->begin();

    if (index >= size_)
        throw std::out_of_range("Vector Error: Index out of range");

    int i = index;
    while (i < size_ - 1) {
        data_[i] = data_[i + 1];
        i++;
    }

    size_--;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
    if (size_ == capacity_) {
        reserve(capacity_ * 2);
    }

    data_[size_] = value;
    size_++;
}

template <typename T>
void vector<T>::pop_back() {
    if (size_ == 0) throw std::out_of_range("Vector Error: Index out of range");
    data_[size_ - 1] = T();
    size_--;
}

template <typename T>
void vector<T>::swap(vector &other) {
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
}
}  // namespace s21
