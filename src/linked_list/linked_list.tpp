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
        tail->next = nullptr;
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
    size_ = 0;
    head = nullptr;
    tail = nullptr;

    for (auto iter = other.cbegin(); iter != other.cend(); ++iter) {
        push_back(*iter);
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
        push_back(value);
        return begin();
    }

    if (pos.pointer_() == head) {
        push_front(value);
        return begin();
    }

    auto node = new ListNode<T>(value, pos.pointer_()->prev, pos.pointer_());
    pos.pointer_()->prev->next = node;
    pos.pointer_()->prev = node;
    return iterator(node);
}

// template <typename T>
// typename list<T>::iterator list<T>::insert(const_iterator pos,
//                                            const_reference value) {
//     if (size_ == 0) {
//         push_back(value);
//         return begin();
//     }
//
//     if (pos.pointer_() == head) {
//         push_front(value);
//         return begin();
//     }
//
//     auto node = new ListNode<T>(value, pos.pointer_()->prev, pos.pointer_());
//     pos.pointer_()->prev->next = node;
//     pos.pointer_()->prev = node;
//     return iterator(node);
// }

template <typename T>
void list<T>::erase(iterator pos) {
    if (size_ == 1) {
        delete pos.pointer_();
        size_ = 0;
        head = nullptr;
        tail = nullptr;
    } else if (size_ > 1) {
        if (pos.pointer_() == head) {
            auto node = pos.pointer_()->next;
            delete head;
            head = node;
            node->prev = nullptr;

            if (size_ == 2) {
                tail = head;
            }
            size_--;
        } else if (pos.pointer_() == tail) {
            auto node = pos.pointer_()->prev;
            delete tail;
            tail = node;
            node->next = nullptr;

            if (size_ == 2) {
                tail = head;
            }
            size_--;
        } else {
            auto prev = pos.pointer_()->prev;
            auto next = pos.pointer_()->next;

            delete pos.pointer_();
            prev->next = next;
            next->prev = prev;
            size_--;
        }
    }
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
        if (iter1.pointer_()->data <= iter2.pointer_()->data) {
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
    if (this != &other) {
        for (auto itr = other.begin(); itr != other.end(); ++itr) {
            // insert(ListIterator(pos.pointer_()), *itr);
            // ListNode<T>* it = pos.pointer_();
            insert(begin() + (pos - cbegin()), *itr);
        }
        other.clear();
    }
}

template <typename T>
void list<T>::reverse() {
    list<T> temp;

    auto iter = rbegin();
    while (iter != rend()) {
        temp.push_back(*iter);
        --iter;
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
            temp.push_back(*iter);
        }
    }

    swap(temp);
}

template <typename T>
void list<T>::mergeSort(list<T>& other) {
    if (other.size_ < 2) return;

    list<T> first;
    list<T> second;

    auto iter = other.begin();
    int counter = 0;
    while (counter < (other.size_ / 2)) {
        first.push_back(*iter);
        ++iter;
        counter++;
    }

    while (iter != other.end()) {
        second.push_back(*iter);
        ++iter;
    }

    mergeSort(first);
    mergeSort(second);
    first.merge(second);

    other.swap(first);
}

template <typename T>
void list<T>::sort() {
    mergeSort(*this);
}

}  // namespace s21
