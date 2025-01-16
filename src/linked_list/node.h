//
// Created by sergey on 10.12.24.
//

#ifndef NODE_H
#define NODE_H

namespace s21 {
template <typename T>
class ListNode {
 public:
  ListNode() = default;
  explicit ListNode(T data, ListNode<T>* prev = nullptr,
                    ListNode<T>* next = nullptr)
      : data(data), next(next), prev(prev) {}
  // explicit ListNode(T& data, ListNode<T>* prev = nullptr,
  //                   ListNode<T>* next = nullptr)
  //     : data(data), next(next), prev(prev) {}
  //
  // explicit ListNode(T&& data, ListNode<T>* prev = nullptr,
  //                   ListNode<T>* next = nullptr)
  //     : data(data), next(next), prev(prev) {}

  ~ListNode() = default;

  T data;
  ListNode<T>* next;
  ListNode<T>* prev;
};
}  // namespace s21
#endif  // NODE_H
