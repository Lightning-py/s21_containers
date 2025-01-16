#include <gtest/gtest.h>

#include "../set/s21_set.h"

TEST(SET, Default_constructor) {
  s21::set<int> set;
  EXPECT_EQ(set.size(), 0);
}

TEST(SET, Initializer_list_constructor) {
  s21::set<int> set = {1, 2, 3, 4, 5};

  EXPECT_EQ(set.size(), 5);
  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(2));
  EXPECT_TRUE(set.contains(3));
  EXPECT_TRUE(set.contains(4));
  EXPECT_TRUE(set.contains(5));
}

TEST(SET, Copy_Constructor) {
  const s21::set<int> set = {1, 2, 3, 4, 5};
  const s21::set<int>& copy = set;

  EXPECT_EQ(copy.size(), 5);
  EXPECT_TRUE(copy.contains(1));
  EXPECT_TRUE(copy.contains(2));
  EXPECT_TRUE(copy.contains(3));
  EXPECT_TRUE(copy.contains(4));
  EXPECT_TRUE(copy.contains(5));
}

TEST(SET, Move_constructor) {
  s21::set<int> set = {1, 2, 3, 4, 5};
  s21::set<int> set2(std::move(set));

  EXPECT_EQ(set2.size(), 5);
  EXPECT_TRUE(set2.contains(1));
  EXPECT_TRUE(set2.contains(2));
  EXPECT_TRUE(set2.contains(3));
  EXPECT_TRUE(set2.contains(4));
  EXPECT_TRUE(set2.contains(5));
}

TEST(SET, Equal_operator) {
  const s21::set<int> set = {1, 2, 3, 4, 5};
  const s21::set<int>& set2 = set;

  EXPECT_EQ(set2.size(), 5);
  EXPECT_TRUE(set2.contains(1));
  EXPECT_TRUE(set2.contains(2));
  EXPECT_TRUE(set2.contains(3));
  EXPECT_TRUE(set2.contains(4));
  EXPECT_TRUE(set2.contains(5));
}

TEST(SET, Empty) {
  s21::set<int> set;

  EXPECT_TRUE(set.empty());
  set.insert(1);
  EXPECT_FALSE(set.empty());
}

TEST(SET, Size) {
  s21::set<int> set = {1, 2, 3, 4, 5};
  EXPECT_EQ(set.size(), 5);
}

TEST(SET, Max_size) {
  s21::set<int> set = {1, 2, 3, 4, 5};
  EXPECT_EQ(set.max_size(), std::numeric_limits<size_t>::max());
}

TEST(SET, Clear) {
  s21::set<int> set = {1, 2, 3, 4, 5};
  set.clear();
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0);
}

TEST(SET, Insert) {
  s21::set<int> set;
  auto it = set.insert(1).first;

  EXPECT_TRUE(set.contains(1));
  EXPECT_EQ(*it, 1);
}

TEST(SET, Erase) {
  s21::set<int> set = {1};

  set.erase(set.begin());
  EXPECT_TRUE(set.empty());
  EXPECT_FALSE(set.contains(1));
}

TEST(SET, Swap) {
  s21::set<int> set = {1, 2};
  s21::set<int> set2 = {10};

  set.swap(set2);
  EXPECT_EQ(set.size(), 1);
  EXPECT_EQ(set2.size(), 2);
  EXPECT_TRUE(set.contains(10));
  EXPECT_TRUE(set2.contains(1));
  EXPECT_TRUE(set2.contains(2));
}

TEST(SET, Merge) {
  s21::set<int> set = {1, 2};
  s21::set<int> set2 = {10};

  set.merge(set2);
  EXPECT_EQ(set.size(), 3);
  EXPECT_TRUE(set.contains(10));
  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(2));
}

TEST(SET, Find) {
  s21::set<int> set = {1, 2, 3, 4, 5};

  EXPECT_EQ(set.find(1), set.begin());
  EXPECT_EQ(set.find(100), set.end());
}

TEST(SET, Contains) {
  s21::set<int> set = {1, 2, 3, 4, 5};

  EXPECT_TRUE(set.contains(1));
  EXPECT_FALSE(set.contains(100));
}

TEST(SET, Insert_many) {
  s21::set<int> set = {1, 2};

  int a = 1;
  int b = 2;

  const auto result = set.insert_many(a, b);

  EXPECT_EQ(result.size(), 2);
  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(2));
}