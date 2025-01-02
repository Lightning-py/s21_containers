#include <gtest/gtest.h>

#include <string>

#include "../s21_containers.h"

TEST(MapTest, InsertAndGet) {
    s21::map<int, std::string> map;
    map.insert({1, "one"});
    map.insert({2, "two"});
    map.insert({3, "three"});

    EXPECT_EQ(map.get(1), "one");
    EXPECT_EQ(map.get(2), "two");
    EXPECT_EQ(map.get(3), "three");
    EXPECT_THROW(map.get(4), std::out_of_range);
}

TEST(MapTest, ContainsKey) {
    s21::map<int, std::string> map;
    map.insert({1, "one"});
    map.insert({2, "two"});

    EXPECT_TRUE(map.contains(1));
    EXPECT_TRUE(map.contains(2));
    EXPECT_FALSE(map.contains(3));
}

TEST(MapTest, SizeAndEmpty) {
    s21::map<int, std::string> map;
    EXPECT_EQ(map.size(), 0);
    EXPECT_TRUE(map.empty());

    map.insert({1, "one"});
    EXPECT_EQ(map.size(), 1);
    EXPECT_FALSE(map.empty());

    map.insert({2, "two"});
    EXPECT_EQ(map.size(), 2);
}

TEST(MapTest, RemoveKey) {
    s21::map<int, std::string> map;
    map.insert({1, "one"});
    map.insert({2, "two"});
    map.insert({3, "three"});

    map.remove(2);
    EXPECT_FALSE(map.contains(2));
    EXPECT_EQ(map.size(), 2);

    EXPECT_THROW(map.get(2), std::out_of_range);

    map.remove(1);
    EXPECT_FALSE(map.contains(1));
    EXPECT_EQ(map.size(), 1);
}

TEST(MapTest, ClearMap) {
    s21::map<int, std::string> map;
    map.insert({1, "one"});
    map.insert({2, "two"});
    map.insert({3, "three"});

    map.clear();
    EXPECT_TRUE(map.empty());
    EXPECT_EQ(map.size(), 0);
    EXPECT_FALSE(map.contains(1));
}

TEST(MapTest, OperatorAccess) {
    s21::map<int, std::string> map;
    map[1] = "one";
    map[2] = "two";

    EXPECT_EQ(map[1], "one");
    EXPECT_EQ(map[2], "two");

    // Изменение значения
    map[1] = "uno";
    EXPECT_EQ(map[1], "uno");

    // Доступ к отсутствующему ключу
    EXPECT_EQ(map[3], "");
    EXPECT_EQ(map.size(), 3);
}

TEST(MapTest, GetOrDefault) {
    s21::map<int, std::string> map;
    map.insert({1, "one"});

    EXPECT_EQ(map.getOrDefault(1, "default"), "one");
    EXPECT_EQ(map.getOrDefault(2, "default"), "default");
}

TEST(MapTest, SwapMaps) {
    s21::map<int, std::string> map1;
    s21::map<int, std::string> map2;

    map1.insert({1, "one"});
    map1.insert({2, "two"});

    map2.insert({3, "three"});
    map2.insert({4, "four"});

    map1.swap(map2);

    EXPECT_TRUE(map1.contains(3));
    EXPECT_TRUE(map1.contains(4));
    EXPECT_FALSE(map1.contains(1));
    EXPECT_FALSE(map1.contains(2));

    EXPECT_TRUE(map2.contains(1));
    EXPECT_TRUE(map2.contains(2));
    EXPECT_FALSE(map2.contains(3));
    EXPECT_FALSE(map2.contains(4));
}

TEST(MapTest, Iterators) {
    s21::map<int, std::string> map;
    map.insert({2, "two"});
    map.insert({1, "one"});
    map.insert({3, "three"});

    std::vector<std::string> values;
    for (auto it = map.begin(); it != map.end(); ++it) {
        values.push_back((*it).second);
    }

    EXPECT_EQ(values.size(), 3);
    EXPECT_EQ(values[0], "one");
    EXPECT_EQ(values[1], "two");
    EXPECT_EQ(values[2], "three");
}