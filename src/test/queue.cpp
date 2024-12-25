#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(QUEUE, default_constructor) {
  s21::queue<int> queue;

  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);
}

TEST(QUEUE, constructor_with_initializer_list) {
  s21::queue<int> queue({1, 2, 3});

  EXPECT_FALSE(queue.empty());
  EXPECT_EQ(queue.size(), 3);
}

TEST(QUEUE, copy_constructor) {
  s21::queue<int> queue1({1, 2, 3});
  s21::queue<int> queue2(queue1);

  EXPECT_EQ(queue1.size(), queue2.size());
  EXPECT_EQ(queue1.front(), queue2.front());
  EXPECT_EQ(queue1.back(), queue2.back());
}

TEST(QUEUE, move_constructor) {
  s21::queue<int> queue1({1, 2, 3});
  s21::queue<int> queue2(std::move(queue1));

  EXPECT_EQ(queue1.size(), 0);
  EXPECT_EQ(queue2.size(), 3);
  EXPECT_EQ(queue2.front(), 1);
  EXPECT_EQ(queue2.back(), 3);
}

TEST(QUEUE, move_assignment) {
  s21::queue<int> queue1({1, 2, 3});
  s21::queue<int> queue2;

  queue2 = std::move(queue1);

  EXPECT_EQ(queue1.size(), 0);
  EXPECT_EQ(queue2.size(), 3);
  EXPECT_EQ(queue2.front(), 1);
  EXPECT_EQ(queue2.back(), 3);
}

TEST(QUEUE, push_and_pop) {
  s21::queue<int> queue({1, 2, 3, 4});

  queue.push(5);

  EXPECT_EQ(queue.size(), 5);

  queue.pop();

  EXPECT_EQ(queue.size(), 4);
  EXPECT_EQ(queue.front(), 2);
}

TEST(QUEUE, swap) {
  s21::queue<int> queue1({1, 2, 3});
  s21::queue<int> queue2({4, 5});

  queue1.swap(queue2);

  EXPECT_EQ(queue1.size(), 2);
  EXPECT_EQ(queue1.front(), 4);

  EXPECT_EQ(queue2.size(), 3);
  EXPECT_EQ(queue2.front(), 1);
}

TEST(QUEUE, front) {
  s21::queue<int> queue({1, 2, 3, 4, 5});

  EXPECT_EQ(queue.front(), 1);
}

TEST(QUEUE, back) {
  s21::queue<int> queue({1, 2, 3, 4, 5});

  EXPECT_EQ(queue.back(), 5);
}

TEST(QUEUE, empty) {
  s21::queue<int> queue;

  EXPECT_TRUE(queue.empty());
}

TEST(QUEUE, not_empty) {
  s21::queue<int> queue({1, 2, 3, 4, 5});

  EXPECT_FALSE(queue.empty());
}

TEST(QUEUE, size_of_empty_queue) {
  s21::queue<int> queue;

  EXPECT_EQ(queue.size(), 0);
}

TEST(QUEUE, size_of_not_empty_queue) {
  s21::queue<int> queue({1, 2, 3, 4, 5});

  EXPECT_EQ(queue.size(), 5);
}

TEST(QUEUE, move_semantics) {
  s21::queue<std::string> queue1({"Hello", "World"});
  s21::queue<std::string> queue2(std::move(queue1));

  EXPECT_EQ(queue1.size(), 0);
  EXPECT_EQ(queue2.size(), 2);

  EXPECT_EQ(queue2.front(), "Hello");
  EXPECT_EQ(queue2.back(), "World");
}

TEST(QUEUE, swap_empty_queues) {
  s21::queue<int> queue1;
  s21::queue<int> queue2;

  queue1.swap(queue2);

  EXPECT_TRUE(queue1.empty());
  EXPECT_TRUE(queue2.empty());
}

TEST(QUEUE, swap_with_one_empty_queue) {
  s21::queue<int> queue1;
  s21::queue<int> queue2({1, 2, 3});

  queue1.swap(queue2);

  EXPECT_EQ(queue1.size(), 3);
  EXPECT_EQ(queue1.front(), 1);
  EXPECT_EQ(queue1.back(), 3);

  EXPECT_TRUE(queue2.empty());
}

TEST(QUEUE, front_and_back_for_const_queue) {
  const s21::queue<int> queue({1, 2, 3});

  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 3);
}

TEST(QUEUE, size_of_const_queue) {
  const s21::queue<int> constQueue({1, 2, 3});

  EXPECT_EQ(constQueue.size(), 3);
}
