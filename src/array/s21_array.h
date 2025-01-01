#ifndef S21_ARRAY_H
#define S21_ARRAY_H

namespace s21 {

template <typename T, size_t N>
class array {
   public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = size_t;

   private:
    T elements_[N];

   public:
    array() = default;

    array(std::initializer_list<value_type> const &items) {
        if (items.size() > N) {
            throw std::out_of_range("Array Error: Initializer list too large");
        }
        auto it = items.begin();
        for (size_type i = 0; i < items.size(); ++i) {
            elements_[i] = *it++;
        }

        for (size_type i = items.size(); i < N; ++i) {
            elements_[i] = T();
        }
    }

    array(const array &other) {
        for (size_type i = 0; i < N; ++i) {
            elements_[i] = other.elements_[i];
        }
    }

    array(array &&other)

        noexcept {
        for (size_type i = 0; i < N; ++i) {
            elements_[i] = std::move(other.elements_[i]);
        }
    }

    array &operator=(array &&other)

        noexcept {
        if (this != &other) {
            for (size_type i = 0; i < N; ++i) {
                elements_[i] = std::move(other.elements_[i]);
            }
        }
        return *this;
    }

    ~array() = default;

    reference at(size_type pos) {
        if (pos >= N) {
            throw std::out_of_range("Array Error: Index out of range");
        }
        return elements_[pos];
    }

    reference operator[](size_type pos) { return elements_[pos]; }

    const_reference front() const { return elements_[0]; }

    const_reference back() const { return elements_[N - 1]; }

    iterator data() { return elements_; }

    iterator begin() { return elements_; }

    iterator end() { return elements_ + N; }

    const_iterator begin() const { return elements_; }

    const_iterator end() const { return elements_ + N; }

    bool empty() const { return N == 0; }

    size_type size() const { return N; }

    size_type max_size() const { return N; }

    void swap(array &other)

        noexcept {
        for (size_type i = 0; i < N; ++i) {
            std::swap(elements_[i], other.elements_[i]);
        }
    }

    void fill(const_reference value) {
        for (size_type i = 0; i < N; ++i) {
            elements_[i] = value;
        }
    }
};

}  // namespace s21

#endif