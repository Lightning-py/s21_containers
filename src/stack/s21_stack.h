#ifndef S21_STACK_H
#define S21_STACK_H

namespace s21 {
template <class T, class Container = list<T>>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();

  stack &operator=(stack &&s);

  const_reference top() const;

  bool empty() const noexcept;
  size_type size() const noexcept;

  void push(const_reference value);
  void pop();
  void swap(stack &s);

 private:
  Container container_;
};

}  // namespace s21

#include "s21_stack.tpp"

#endif  // S21_STACK_H