//
// Created by sergey on 05.01.25.
//

#include <gtest/gtest.h>

#include "../s21_containersplus.h"

TEST(MULTISET, Default_constructor) {
    s21::multiset<int> multiset;

    EXPECT_EQ(multiset.size(), 0);
}

TEST(MULTISET, Initializer_list_constructor) {
    s21::multiset<int> multiset = {1, 2, 3, 4, 1};

    EXPECT_EQ(multiset.size(), 5);
}

TEST(MULTISET, Copy_constructor) {
    const s21::multiset<int> multiset = {1, 2, 3, 4, 1};
    const s21::multiset<int>& multiset_copy = multiset;

    EXPECT_EQ(multiset_copy.size(), 5);
}

TEST(MULTISET, Move_constructor) {
    s21::multiset<int> multiset = {1, 2, 3, 4, 1};
    s21::multiset<int> multiset_copy(std::move(multiset));

    EXPECT_EQ(multiset_copy.size(), 5);
}

TEST(MULTISET, Equal_operator) {
    const s21::multiset<int> multiset = {1, 2, 3, 4, 1};
    const s21::multiset<int> multiset_copy = multiset;

    EXPECT_EQ(multiset_copy.size(), 5);
}

TEST(MULTISET, Empty) {
    s21::multiset<int> multiset;
    EXPECT_TRUE(multiset.empty());

    multiset.insert_(1);
    EXPECT_FALSE(multiset.empty());
}

TEST(MULTISET, Size) {
    s21::multiset<int> multiset = {1, 2, 3, 4, 1};
    EXPECT_EQ(multiset.size(), 5);
}

TEST(MULTISET, Max_size) {
    s21::multiset<int> multiset = {1, 2, 3, 4, 1};
    EXPECT_EQ(multiset.max_size(), std::numeric_limits<size_t>::max());
}

TEST(MULTISET, Clear) {
    s21::multiset<int> multiset = {1, 2, 3, 4, 1};

    multiset.clear();
    EXPECT_EQ(multiset.size(), 0);
    EXPECT_TRUE(multiset.empty());
}

TEST(MULTISET, Insert) {
    s21::multiset<int> multiset;

    int a = 1;

    multiset.insert(a);
    EXPECT_EQ(multiset.size(), 1);
    EXPECT_EQ(multiset.contains(1), 1);
}

TEST(MULTISET, Erase) {
    s21::multiset<int> multiset = {1, 1};

    multiset.erase(multiset.begin());
    multiset.erase(multiset.begin());

    EXPECT_EQ(multiset.size(), 0);
}

TEST(MULTISET, Swap) {
    s21::multiset<int> multiset = {1, 2};
    s21::multiset<int> multiset_copy = {3, 4};

    multiset.swap(multiset_copy);

    EXPECT_TRUE(multiset.contains(3));
    EXPECT_TRUE(multiset.contains(4));

    EXPECT_TRUE(multiset_copy.contains(1));
    EXPECT_TRUE(multiset_copy.contains(2));
}

TEST(MULTISET, Merge) {
    s21::multiset<int> multiset = {1, 2};
    s21::multiset<int> multiset_copy = {3, 4};

    multiset.merge(multiset_copy);

    EXPECT_TRUE(multiset.contains(3));
    EXPECT_TRUE(multiset.contains(4));
    EXPECT_TRUE(multiset.contains(1));
    EXPECT_TRUE(multiset.contains(2));
}

TEST(MULTISET, Count) {
    s21::multiset<int> multiset = {1, 1, 2};

    EXPECT_EQ(multiset.count(1), 2);
    EXPECT_EQ(multiset.count(2), 1);
}

TEST(MULTISET, Find) {
    s21::multiset<int> multiset = {1, 2};

    EXPECT_EQ(multiset.find(1), multiset.begin());
}

TEST(MULTISET, Contains) {
    s21::multiset<int> multiset = {1, 1, 2};

    EXPECT_TRUE(multiset.contains(1));
}

TEST(MULTISET, Equal_range) {
    s21::multiset<int> multiset = {1, 1, 2};

    auto iterators = multiset.equal_range(1);

    for (auto it = iterators.first; it != iterators.second; ++it) {
        EXPECT_EQ(*it, 1);
    }
}

TEST(MULTISET, Upper_bound) {
    s21::multiset<int> multiset = {-2, -1};

    auto it = multiset.begin();
    ++it;

    EXPECT_EQ(multiset.upper_bound(-2), it);
}

TEST(MULTISET, Lower_bound) {
    s21::multiset<int> multiset = {1, 2};

    EXPECT_EQ(multiset.lower_bound(2), multiset.begin());
}