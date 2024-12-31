#include "../set/s21_set.h"
#include <gtest/gtest.h>

TEST(SetTest, InsertElements) {
    s21::Set<int> mySet;

    mySet.insert(5);
    EXPECT_TRUE(mySet.contains(5));
    EXPECT_EQ(mySet.size(), 1);

    mySet.insert(10);
    EXPECT_TRUE(mySet.contains(10));
    EXPECT_EQ(mySet.size(), 2);

    mySet.insert(5);
    EXPECT_EQ(mySet.size(), 2);
}

TEST(SetTest, RemoveElements) {
    s21::Set<int> mySet;

    mySet.insert(5);
    mySet.insert(10);

    mySet.remove(5);
    EXPECT_FALSE(mySet.contains(5));
    EXPECT_EQ(mySet.size(), 1);

    mySet.remove(10);
    EXPECT_TRUE(mySet.empty());
}

TEST(SetTest, ContainsElement) {
    s21::Set<int> mySet;

    mySet.insert(42);
    EXPECT_TRUE(mySet.contains(42));

    mySet.remove(42);
    EXPECT_FALSE(mySet.contains(42));
}

TEST(SetTest, ClearSet) {
    s21::Set<int> mySet;

    mySet.insert(1);
    mySet.insert(2);
    mySet.insert(3);

    mySet.clear();
    EXPECT_TRUE(mySet.empty());
    EXPECT_EQ(mySet.size(), 0);
}

TEST(SetTest, Iterators) {
    s21::Set<int> mySet;

    mySet.insert(3);
    mySet.insert(1);
    mySet.insert(2);

    std::vector<int> elements;
    for (auto it = mySet.begin(); it != mySet.end(); ++it) {
        elements.push_back((*it).first);
    }

    EXPECT_EQ(elements, std::vector<int>({1, 2, 3}));
}

TEST(SetTest, EqualityCheck) {
    s21::Set<int> set1;
    s21::Set<int> set2;

    set1.insert(1);
    set1.insert(2);

    set2.insert(2);
    set2.insert(1);

    EXPECT_TRUE(set1 == set2);

    set2.insert(3);
    EXPECT_FALSE(set1 == set2);
}
