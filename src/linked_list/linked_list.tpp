#pragma once
#include "linked_list.h"

namespace s21 {

template <typename T>
void list<T>::push_back(const_reference value) {
    if (size_ == 0) {
        head = new ListNode<T>(value, nullptr, nullptr);
        tail = head;
    } else if (size_ == 1) {
        tail = new ListNode<T>(value, head, nullptr);
        head->next = tail;
    } else {
        tail->next = new ListNode<T>(value, tail, nullptr);
        tail = tail->next;
    }
    size_++;
}

template <typename T>
void list<T>::pop_back() {
    if (size_ == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
        size_ = 0;
    } else if (size_ > 1) {
        ListNode<T>* prev = tail->prev;
        delete tail;
        tail = prev;
        tail->prev = nullptr;
        size_--;
    }
}

template <typename T>
void list<T>::push_front(const_reference value) {
    if (size_ == 0) {
        head = new ListNode<T>(value, nullptr, nullptr);
        tail = head;
    } else if (size_ == 1) {
        head = new ListNode<T>(value, nullptr, tail);
        tail->prev = head;
    } else {
        head = new ListNode<T>(value, nullptr, head);
        head->next->prev = head;
    }

    size_++;
}

template <typename T>
void list<T>::pop_front() {
    if (size_ == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
        size_ = 0;
    } else if (size_ > 1) {
        ListNode<T>* node = head->next;
        delete head;
        head = node;
        head->prev = nullptr;
        size_--;
    }
}

template <typename T>
list<T>::list(size_type n) : head(nullptr), tail(nullptr), size_(0) {
    if (n > 0) {
        ListNode<T>* node = nullptr;
        ListNode<T>* prev = nullptr;
        for (int i = 0; i < n; ++i) {
            node = new ListNode<T>(T(), prev, nullptr);
            if (prev) prev->next = node;
            prev = node;

            if (i == 0) head = node;
        }
        tail = node;
        size_ = n;
    }
}

template <typename T>
list<T>::~list() {
    while (head != nullptr) {
        ListNode<T>* node = head->next;
        delete head;
        head = node;
    }
}

template <typename T>
list<T>::list(std::initializer_list<T> const& items) {
    size_ = 0;
    for (auto item : items) {
        push_back(item);
    }
}

template <typename T>
list<T>::list(const list& other) {
    size_ = other.size_;
    for (auto item : other) {
        push_back(item);
    }
}

template <typename T>
list<T>::list(list&& other) noexcept {
    size_ = other.size_;
    head = other.head;
    tail = other.tail;

    other.head = nullptr;
    other.tail = nullptr;
    other.size_ = 0;
}

template <typename T>
list<T>& list<T>::operator=(list&& other) noexcept {
    size_ = other.size_;
    head = other.head;
    tail = other.tail;

    other.size_ = 0;
    other.head = nullptr;
    other.tail = nullptr;

    return *this;
}

template <typename T>
void list<T>::clear() {
    while (size_ > 0) pop_back();
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
    if (size_ == 0) {
        auto* node = new ListNode<T>(value, nullptr, nullptr);
        head = node;
        tail = node;
        return begin();
    }

    if (pos.pointer() == head) {
        push_front(value);
        return begin();
    }

    auto node = new ListNode<T>(value, pos.pointer()->prev, pos.pointer());
    pos.pointer()->prev->next = node;
    pos.pointer()->prev = node;
    return iterator(node);
}

template <typename T>
void list<T>::erase(iterator pos) {
    if (pos.pointer() == head) {
        if (size_ == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            size_ = 0;
        } else {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
        }
        return;
    }

    if (pos.pointer() == tail) {
        tail = tail->prev;
        delete tail->next;
        return;
    }
    pos.pointer()->prev->next = pos.pointer()->next;
    pos.pointer()->next->prev = pos.pointer()->prev;
    delete pos.pointer();
}

template <typename T>
void list<T>::swap(list& other) noexcept {
    std::swap(size_, other.size_);
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

template <typename T>
void list<T>::merge(list& other) {
    list<T> temp;
    auto iter1 = begin();
    auto iter2 = other.begin();

    while (iter1 != end() && iter2 != other.end()) {
        if (iter1->pointer() >= iter2->pointer()) {
            temp.push_back(*iter1);
            ++iter1;
        } else {
            temp.push_back(*iter2);
            ++iter2;
        }
    }

    while (iter1 != end()) {
        temp.push_back(*iter1);
        ++iter1;
    }

    while (iter2 != other.end()) {
        temp.push_back(*iter2);
        ++iter2;
    }

    clear();
    swap(temp);
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
    if (size_ == 0) return;

    if (other.size_ == 0) {
        if (size_ == 1) {
            swap(other);
        } else if (size_ > 1) {
            pos.pointer()->prev->next = nullptr;
            other.head = pos.pointer()->prev;
            other.tail = tail;
            tail = pos.pointer()->prev;
            pos.pointer()->prev = nullptr;
        }
        return;
    }

    other.tail->next = pos.pointer();
    pos.pointer()->prev = other.tail;
    other.tail = tail;
    tail = pos.pointer()->prev;
}

template <typename T>
void list<T>::reverse() {
    list<T> temp;

    auto iter = rbegin();
    while (iter != rend()) {
        temp.push_back(*iter);
    }

    clear();
    swap(temp);
}

template <typename T>
void list<T>::unique() {
    list<T> temp;
    for (auto iter = begin(); iter != end(); ++iter) {
        bool fine = true;
        for (auto check = temp.begin(); check != temp.end() && fine; ++check) {
            fine = *iter != *check;
        }
        if (fine) {
            push_back(*iter);
        }
    }
}

template <typename T>
void list<T>::mergeSort(list<T>& other) {
    if (other.size_ < 2) return;

    list<T> first;
    list<T> second;

    auto iter = begin();
    int counter = 0;
    while (counter < (other.size_ / 2)) {
        first.push_back(*iter);
        ++iter;
        counter++;
    }

    while (iter != end()) {
        second.push_back(*iter);
        ++iter;
    }

    mergeSort(first);
    mergeSort(second);
    first.merge(second);

    swap(first, other);
}

template <typename T>
void list<T>::sort() {
    mergeSort(*this);
}

}  // namespace s21
