#include <gtest/gtest.h>

#include <string>

#include "../s21_containers.h"

TEST(MAP, Default_constructor) {
  s21::map<int, int> map;

  EXPECT_EQ(map.size(), 0);
}

TEST(MAP, Initializer_list_Constructor) {
  s21::map<int, int> map = {std::make_pair(1, 2), std::make_pair(3, 4)};

  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map[1], 2);
  EXPECT_EQ(map[3], 4);
}

TEST(MAP, Copy_constructor) {
  s21::map<int, int> map;
  map[1] = 2;
  map[3] = 4;

  s21::map<int, int> copy(map);

  EXPECT_EQ(copy.size(), 2);
  EXPECT_EQ(copy[1], 2);
  EXPECT_EQ(copy[3], 4);
}

TEST(MAP, Move_constructor) {
  s21::map<int, int> map = {std::make_pair(1, 2), std::make_pair(3, 4)};
  s21::map<int, int> copy(std::move(map));
}

TEST(MAP, Operator_equal) {
  const s21::map<int, int> map = {std::make_pair(1, 2), std::make_pair(3, 4)};
  s21::map<int, int> map2 = map;

  EXPECT_EQ(map2.size(), 2);
  EXPECT_EQ(map2[1], 2);
  EXPECT_EQ(map2[3], 4);
}

TEST(MAP, At_normal) {
  s21::map<int, int> map = {std::make_pair(1, 2), std::make_pair(3, 4)};

  EXPECT_EQ(map.at(1), 2);
  EXPECT_EQ(map.at(3), 4);
}

TEST(MAP, At_invalid) {
  s21::map<int, int> map = {std::make_pair(1, 2), std::make_pair(3, 4)};

  EXPECT_THROW(map.at(10), std::out_of_range);
}

TEST(MAP, Operator_square_brackets) {
  s21::map<int, int> map;

  map[1] = 2;
  EXPECT_EQ(map[1], 2);
  map[1] = 3;
  EXPECT_EQ(map[1], 3);
}

TEST(MAP, Empty) {
  s21::map<int, int> map;

  EXPECT_EQ(map.empty(), true);
}

TEST(MAP, Size) {
  s21::map<int, int> map;

  EXPECT_EQ(map.size(), 0);
  map[1] = 2;
  EXPECT_EQ(map.size(), 1);
}

TEST(MAP, Max_size) {
  s21::map<int, int> map;
  EXPECT_EQ(map.max_size(), std::numeric_limits<size_t>::max());
}

TEST(MAP, Clear) {
  s21::map<int, int> map;

  map[1] = 2;
  EXPECT_EQ(map.size(), 1);
  map.clear();
  EXPECT_EQ(map.size(), 0);
  EXPECT_TRUE(map.empty());
}

TEST(MAP, Insert) {
  s21::map<int, int> map;
  map.insert(std::make_pair(1, 2));
  EXPECT_EQ(map[1], 2);
  map.insert(3, 4);
  EXPECT_EQ(map[3], 4);
  map.insert(3, 4);
}

TEST(MAP, Insert_Or_Assign) {
  s21::map<int, int> map;
  map.insert_or_assign(1, 2);

  EXPECT_EQ(map[1], 2);
}

TEST(MAP, Erase) {
  s21::map<int, int> map;

  map[1] = 2;
  EXPECT_EQ(map[1], 2);
  map.erase(map.begin());
  EXPECT_EQ(map.size(), 0);
  map[1] = 2;
  EXPECT_EQ(map[1], 2);
  map.erase(1);
  EXPECT_EQ(map.size(), 0);
}

TEST(MAP, Swap) {
  s21::map<int, int> map;
  map[1] = 2;
  s21::map<int, int> map2;
  map2.swap(map);
  EXPECT_EQ(map2[1], 2);
}

TEST(MAP, Merge) {
  s21::map<int, int> map;
  map[1] = 2;
  s21::map<int, int> map2;
  map2.merge(map);

  EXPECT_EQ(map2[1], 2);
  EXPECT_EQ(map.size(), 0);
}

TEST(MAP, Contains) {
  s21::map<int, int> map;
  map[1] = 2;
  EXPECT_TRUE(map.contains(1));
  EXPECT_FALSE(map.contains(2));
}

TEST(MAP, Insert_many) {
  s21::map<int, int> map;

  auto pair1 = std::make_pair(1, 2);
  auto pair2 = std::make_pair(3, 4);

  const auto result = map.insert_many(pair1, pair2);

  EXPECT_EQ(result.size(), 2);
  EXPECT_EQ(map[1], 2);
  EXPECT_EQ(map[3], 4);
}