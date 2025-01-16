#ifndef S21_STACK_TPP
#define S21_STACK_TPP

namespace s21 {
template <class T, class Container>
stack<T, Container>::stack() : container_(){};

template <class T, class Container>
stack<T, Container>::stack(std::initializer_list<value_type> const &items)
    : container_(items){};

template <class T, class Container>
stack<T, Container>::stack(const stack &s) : container_(s.container_){};

template <class T, class Container>
stack<T, Container>::stack(stack &&s) noexcept
    : container_(std::move(s.container_)){};

template <class T, class Container> stack<T, Container>::~stack() {}

template <class T, class Container>
stack<T, Container> &stack<T, Container>::operator=(stack &&s) noexcept {
  if (this != &s) {
    container_ = std::move(s.container_);
  }
  return *this;
}

template <class T, class Container>
typename stack<T, Container>::const_reference stack<T, Container>::top() const {
  return container_.back();
}

template <class T, class Container>
bool stack<T, Container>::empty() const noexcept {
  return container_.empty();
}

template <class T, class Container>
typename stack<T, Container>::size_type
stack<T, Container>::size() const noexcept {
  return container_.size();
}

template <class T, class Container>
void stack<T, Container>::push(const_reference value) {
  container_.push_back(value);
}

template <class T, class Container> void stack<T, Container>::pop() {
  container_.pop_back();
}

template <class T, class Container>
void stack<T, Container>::swap(stack &s) noexcept {
  container_.swap(s.container_);
}

template <class T, class Container>
template <typename... Args>
void stack<T, Container>::insert_many_back(Args &&...args) {
  vector<T> tmp{args...};

  for (auto n : tmp) {
    push(n);
  }
}

}; // namespace s21

#endif // S21_STACK_TPP