//
// Created by sergey on 04.12.24.
//

#ifndef VECTOR_H
#define VECTOR_H

#include "../shared/shared.cpp"

namespace s21 {

template <typename T>
class vector {
   public:
    class VectorIterator;
    class VectorConstIterator;

    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = VectorIterator;
    using const_iterator = VectorConstIterator;
    using size_type = size_t;
    using pointer = T*;
    using const_pointer = const pointer;

   private:
    size_type size_;
    size_type capacity_;
    value_type* data_;

   public:
    // Конструкторы и операторы
    explicit vector() : size_(0), capacity_(1), data_(new value_type[1]) {}
    explicit vector(const size_type n)
        : size_(n),
          capacity_(n == 0 ? 1 : n),
          data_(new value_type[n == 0 ? 1 : n]) {}
    vector(std::initializer_list<value_type> const& items);
    vector(const vector& v);
    vector(vector&& v) noexcept;
    ~vector();
    vector& operator=(vector&& v) noexcept;

    // Методы доступа
    reference at(size_type pos);
    reference operator[](size_type pos);
    const_reference front();
    const_reference back();
    pointer data() const;

    // Методы размера
    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_type size() const;
    [[nodiscard]] size_type max_size() const;
    void reserve(size_type size);
    [[nodiscard]] size_type capacity() const;
    void shrink_to_fit();

    iterator begin() { return iterator(data_); }
    iterator end() { return iterator(data_ + size_); }

    const_iterator cbegin() const { return VectorConstIterator(data_); }
    const_iterator cend() const { return VectorConstIterator(data_ + size_); };
    // методы работы с элементами
    void clear();
    iterator insert(iterator pos, const_reference value);
    void erase(iterator pos);
    void push_back(const_reference value);
    void pop_back();
    void swap(vector& other) noexcept;

    template <typename... Args>
    iterator insert_many(const_iterator pos, Args&&... args);

    template <typename... Args>
    void insert_many_back(Args&&... args);
};

template <typename T>
class vector<T>::VectorIterator {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = typename vector<T>::value_type;
    using difference_type = std::ptrdiff_t;
    using pointer = vector<T>::pointer;
    using reference = vector<T>::reference;

    VectorIterator() : ptr_(nullptr) {}
    explicit VectorIterator(const pointer ptr) : ptr_(ptr) {}

    reference operator*();
    VectorIterator& operator++();
    VectorIterator& operator--();
    VectorIterator operator++(int);
    VectorIterator operator--(int);
    VectorIterator operator+(int n);
    VectorIterator operator-(int n);
    bool operator<(const VectorIterator& other) const;
    int operator-(const VectorIterator& other);
    bool operator==(const VectorIterator& other) const;
    bool operator!=(const VectorIterator& other) const;

   private:
    pointer ptr_;
};

template <typename T>
class vector<T>::VectorConstIterator {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = typename vector<T>::value_type;
    using difference_type = std::ptrdiff_t;
    using pointer = vector<T>::pointer;
    using reference = vector<T>::reference;

    explicit VectorConstIterator(const pointer ptr) : ptr_(ptr) {}

    const_reference operator*() const;
    VectorConstIterator operator++();
    VectorConstIterator operator--();
    VectorConstIterator operator++(int);
    VectorConstIterator operator--(int);
    VectorConstIterator operator+(int n);
    VectorConstIterator operator-(int n);
    size_type operator-(const VectorConstIterator& other);

    bool operator==(const VectorConstIterator& other) const;
    bool operator!=(const VectorConstIterator& other) const;

   private:
    pointer ptr_;
};

}  // namespace s21

#include "./s21_vector.tpp"
#include "./s21_vector_const_iterator.tpp"
#include "./s21_vector_iterator.tpp"

#endif  // VECTOR_H
