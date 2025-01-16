//
// Created by sergey on 11.12.24.
//

#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(VECTOR, default_initializer) {
  s21::vector<int> a(1);
  EXPECT_EQ(a.size(), 1);
}

TEST(VECTOR, size_initializer) {
  auto b = s21::vector<int>();
  EXPECT_EQ(b.size(), 0);
}

TEST(VECTOR, initializer_list) {
  s21::vector<int> a = {1, 2, 3, 4, 5};

  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 3);
  EXPECT_EQ(a[3], 4);
  EXPECT_EQ(a[4], 5);
}

TEST(VECTOR, copy_constructor) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int> b(a);

  EXPECT_EQ(b[0], a[0]);
  EXPECT_EQ(b[1], a[1]);
  EXPECT_EQ(b[2], a[2]);
  EXPECT_EQ(b[3], a[3]);
  EXPECT_EQ(b[4], a[4]);
}

TEST(VECTOR, push_back) {
  auto b = s21::vector<int>();

  for (int i = 0; i < 10; ++i)
    b.push_back(1);

  bool fine = true;
  for (int i = 0; i < 10 && fine; ++i)
    fine = b[i] == 1;

  EXPECT_TRUE(fine);
}

TEST(VECTOR, move_constructor) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int> b(std::move(a));

  bool fine = true;
  for (int i = 0; i < a.size() && fine; ++i)
    fine = b[i] == a[i];

  EXPECT_TRUE(fine);
}

TEST(VECTOR, operator_eq) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int> b = a;

  bool fine = true;
  for (int i = 0; i < a.size() && fine; ++i)
    fine = b[i] == a[i];

  EXPECT_TRUE(fine);
}

TEST(VECTOR, at) {
  s21::vector<int> a = {1, 2, 3, 4, 5};

  EXPECT_EQ(a.at(0), 1);
  EXPECT_EQ(a.at(1), 2);
  EXPECT_EQ(a.at(2), 3);
  EXPECT_EQ(a.at(3), 4);
  EXPECT_EQ(a.at(4), 5);

  EXPECT_THROW(a.at(5), std::out_of_range);
}

TEST(VECTOR, front) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  auto b = s21::vector<int>();

  EXPECT_EQ(a.front(), 1);
  EXPECT_THROW(b.front(), std::out_of_range);
}

TEST(VECTOR, back) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  auto b = s21::vector<int>();

  EXPECT_EQ(a.back(), 5);
  EXPECT_THROW(b.back(), std::out_of_range);
}

TEST(VECTOR, data) {
  s21::vector<int> a = {1, 2, 3, 4, 5};

  EXPECT_EQ(a.data(), &a[0]);
}

TEST(VECTOR, empty) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int> b;

  EXPECT_FALSE(a.empty());
  EXPECT_TRUE(b.empty());
}

TEST(VECTOR, size) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int> b;

  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(b.size(), 0);
}

TEST(VECTOR, max_size) {
  s21::vector<int> a = {1, 2, 3, 4, 5};

  EXPECT_EQ(a.max_size(), a.capacity());
}

TEST(VECTOR, reserve) {
  s21::vector<int> a = {1, 2, 3, 4, 5};

  a.reserve(10);
  for (int i = 0; i < 10; ++i) {
    if (i < 5)
      a[i] = 1;
    else
      a.push_back(1);
  }

  bool fine = true;
  for (int i = 0; i < 10 && fine; ++i)
    fine = a[i] == 1;

  EXPECT_TRUE(fine);
}

TEST(VECTOR, shrink_to_fit) {
  s21::vector<int> a = {1, 2, 3, 4, 5};

  a.reserve(100);
  a.shrink_to_fit();

  EXPECT_EQ(a.capacity(), 5);
}

TEST(VECTOR, clear) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  a.clear();
  EXPECT_EQ(a.size(), 0);
}

TEST(VECTOR, insert) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  a.insert(a.begin() + 2, 10);

  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 10);
  EXPECT_EQ(a[3], 3);
  EXPECT_EQ(a[4], 4);
  EXPECT_EQ(a[5], 5);

  a.insert(a.begin() + 6, 10);
  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 10);
  EXPECT_EQ(a[3], 3);
  EXPECT_EQ(a[4], 4);
  EXPECT_EQ(a[5], 5);
  EXPECT_EQ(a[6], 10);

  a.insert(a.begin(), 10);
  EXPECT_EQ(a[0], 10);
  EXPECT_EQ(a[1], 1);
  EXPECT_EQ(a[2], 2);
  EXPECT_EQ(a[3], 10);
  EXPECT_EQ(a[4], 3);
  EXPECT_EQ(a[5], 4);
  EXPECT_EQ(a[6], 5);
  EXPECT_EQ(a[7], 10);

  s21::vector<int> b(0);
  for (int i = 0; i < 10; ++i) {
    b.insert(b.begin() + i, i);
  }

  EXPECT_EQ(b[0], 0);
  EXPECT_EQ(b[1], 1);
  EXPECT_EQ(b[2], 2);
  EXPECT_EQ(b[3], 3);
  EXPECT_EQ(b[4], 4);
  EXPECT_EQ(b[5], 5);
  EXPECT_EQ(b[6], 6);
  EXPECT_EQ(b[7], 7);
  EXPECT_EQ(b[8], 8);
  EXPECT_EQ(b[9], 9);
}

TEST(VECTOR, erase) {
  s21::vector<int> a = {1, 2, 3, 4, 5};

  a.erase(a.begin());
  EXPECT_EQ(a[0], 2);
  EXPECT_EQ(a[1], 3);
  EXPECT_EQ(a[2], 4);
  EXPECT_EQ(a[3], 5);

  a.erase(a.end() - 1);
  EXPECT_EQ(a[0], 2);
  EXPECT_EQ(a[1], 3);
  EXPECT_EQ(a[2], 4);

  a.erase(a.begin() + 1);
  EXPECT_EQ(a[0], 2);
  EXPECT_EQ(a[1], 4);

  a.erase(a.begin());
  EXPECT_EQ(a[0], 4);

  a.erase(a.begin());
}

TEST(VECTOR, pop_back) {
  s21::vector<int> a = {1, 2, 3, 4, 5};

  while (a.size() > 0)
    a.pop_back();

  EXPECT_EQ(a.size(), 0);
  EXPECT_THROW(a.pop_back(), std::out_of_range);
}

TEST(VECTOR, swap) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int> b = {10};

  a.swap(b);

  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(b.size(), 5);

  EXPECT_EQ(a[0], 10);

  EXPECT_EQ(b[0], 1);
  EXPECT_EQ(b[1], 2);
  EXPECT_EQ(b[2], 3);
  EXPECT_EQ(b[3], 4);
  EXPECT_EQ(b[4], 5);
}

TEST(VECTOR, iterator) {
  s21::vector<int> a = {1, 2, 3, 4, 5};

  bool fine = true;
  int counter = 1;
  for (auto iter = a.begin(); iter != a.end() && fine; ++iter) {
    fine = counter == *iter;
    counter++;
  }
}

TEST(VECTOR, std_copy) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int> b(5);

  std::copy(a.begin(), a.end(), b.begin());
}

TEST(VECTOR, Insert_many) {
  s21::vector<int> a = {1, 2};

  a.insert_many(s21::vector<int>::const_iterator(a.data() + 1), 3, 4);

  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 3);
  EXPECT_EQ(a[2], 4);
  EXPECT_EQ(a[3], 2);
}

TEST(VECTOR, Insert_many_back) {
  s21::vector<int> a = {1, 2};
  a.insert_many_back(3, 4);

  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 3);
  EXPECT_EQ(a[3], 4);
}