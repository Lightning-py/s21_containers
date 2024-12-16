#ifndef S21_QUEUE_H
#define S21_QUEUE_H

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
 public:
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();

  operator=(queue && q);

  const_reference front() const noexcept;
  const_reference back() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;

  void push(const_reference value);
  void push(value_type &&value);  // ???
  void pop();
  void swap(queue &q);
};

}  // namespace s21

#endif  // S21_QUEUE_H