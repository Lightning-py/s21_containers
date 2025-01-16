#ifndef S21_QUEUE_H
#define S21_QUEUE_H

namespace s21 {
template <class T, class Container = list<T>> class queue {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

public:
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q) noexcept;
  ~queue();

  queue &operator=(queue &&q) noexcept;

  const_reference front() const noexcept;
  const_reference back() const noexcept;

  [[nodiscard]] bool empty() const noexcept;
  [[nodiscard]] size_type size() const noexcept;

  void push(const_reference value);
  void pop();
  void swap(queue &q) noexcept;

  template <typename... Args> void insert_many_back(Args &&...args);

private:
  Container container_;
};

} // namespace s21

#include "s21_queue.tpp"

#endif // S21_QUEUE_H