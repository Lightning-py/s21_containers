#ifndef S21_QUEUE_TPP
#define S21_QUEUE_TPP

namespace s21 {

template <class T, class Container>
queue<T, Container>::queue() : container_(){};

template <class T, class Container>
queue<T, Container>::queue(std::initializer_list<value_type> const& items)
    : container_(items){};

template <class T, class Container>
queue<T, Container>::queue(const queue& q) : container_(q.container_) {}

template <class T, class Container>
queue<T, Container>::queue(queue&& q) noexcept
    : container_(std::move(q.container_)) {}

template <class T, class Container>
queue<T, Container>::~queue() {}

template <class T, class Container>
queue<T, Container>& queue<T, Container>::operator=(queue&& q) noexcept {
    if (this != &q) {
        container_ = std::move(q.container_);
    }
    return *this;
}

template <class T, class Container>
typename queue<T, Container>::const_reference queue<T, Container>::front()
    const noexcept {
    return container_.front();
}

template <class T, class Container>
typename queue<T, Container>::const_reference queue<T, Container>::back()
    const noexcept {
    return container_.back();
}

template <class T, class Container>
bool queue<T, Container>::empty() const noexcept {
    return container_.empty();
}

template <class T, class Container>
typename queue<T, Container>::size_type queue<T, Container>::size()
    const noexcept {
    return container_.size();
}

template <class T, class Container>
void queue<T, Container>::push(const_reference value) {
    container_.push_back(value);
}

template <class T, class Container>
void queue<T, Container>::pop() {
    container_.pop_front();
}

template <class T, class Container>
void queue<T, Container>::swap(queue& q) noexcept {
    container_.swap(q.container_);
}

template <class T, class Container>
template <typename... Args>
void queue<T, Container>::insert_many_back(Args&&... args) {
    vector<T> tmp{args...};

    for (auto n : tmp) {
        container_.push_back(n);
    }
}

template <class T, class Container>
template <typename... Args>
void queue<T, Container>::insert_many_front(Args&&... args) {
    vector<T> tmp{args...};
    std::reverse(tmp.begin(), tmp.end());

    for (auto n : tmp) {
        container_.push_front(n);
    }
}

};  // namespace s21

#endif  // S21_QUEUE_TPP