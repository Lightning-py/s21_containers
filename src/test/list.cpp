//
// Created by sergey on 11.12.24.
//

#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(LIST, default_initializer) {
    auto a = s21::list<int>();
    EXPECT_EQ(a.size(), 0);
}

TEST(LIST, size_consructor) {
    auto a = s21::list<int>(10);

    EXPECT_EQ(a.size(), 10);
    for (auto iter = a.begin(); iter != a.end(); ++iter) {
        EXPECT_EQ(*iter, 0);
    }
}

TEST(LIST, initializer_list) {
    s21::list<int> a = {1, 2, 3, 4, 5};

    EXPECT_EQ(a.size(), 5);
    auto iter = a.begin();
    EXPECT_EQ(*iter, 1);
    ++iter;
    EXPECT_EQ(*iter, 2);
    ++iter;
    EXPECT_EQ(*iter, 3);
    ++iter;
    EXPECT_EQ(*iter, 4);
    ++iter;
    EXPECT_EQ(*iter, 5);
}

TEST(LIST, copy_constructor) {
    s21::list<int> a = {1, 2, 3, 4, 5};
    s21::list<int> b(a);

    EXPECT_EQ(b.size(), 5);
    auto iter = b.begin();
    EXPECT_EQ(*iter, 1);
    ++iter;
    EXPECT_EQ(*iter, 2);
    ++iter;
    EXPECT_EQ(*iter, 3);
    ++iter;
    EXPECT_EQ(*iter, 4);
    ++iter;
    EXPECT_EQ(*iter, 5);
}

TEST(LIST, move_constructor) {
    s21::list<int> a = {1, 2, 3, 4, 5};
    s21::list<int> b(std::move(a));

    EXPECT_EQ(b.size(), 5);
    auto iter = b.begin();
    EXPECT_EQ(*iter, 1);
    ++iter;
    EXPECT_EQ(*iter, 2);
    ++iter;
    EXPECT_EQ(*iter, 3);
    ++iter;
    EXPECT_EQ(*iter, 4);
    ++iter;
    EXPECT_EQ(*iter, 5);
}

TEST(LIST, equal_operator) {
    s21::list<int> a = {1, 2, 3, 4, 5};
    s21::list<int> b = a;

    auto iter = b.begin();
    EXPECT_EQ(*iter, 1);
    ++iter;
    EXPECT_EQ(*iter, 2);
    ++iter;
    EXPECT_EQ(*iter, 3);
    ++iter;
    EXPECT_EQ(*iter, 4);
    ++iter;
    EXPECT_EQ(*iter, 5);
}

TEST(LIST, front_back) {
    s21::list<int> a = {1, 2, 3, 4, 5};

    const int front = a.front();
    const int back = a.back();

    EXPECT_EQ(front, 1);
    EXPECT_EQ(back, 5);
}

TEST(LIST, empty) {
    s21::list<int> a;
    EXPECT_TRUE(a.empty());

    a.push_front(1);
    EXPECT_FALSE(a.empty());
}

TEST(LIST, clear) {
    s21::list<int> a = {1, 2, 3, 4, 5};
    a.clear();

    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.size(), 0);
}

TEST(LIST, insert) {
    s21::list<int> a = {1, 2, 3, 4, 5};
    auto iter = a.begin();

    a.insert(iter, 10);
    a.insert(a.rbegin(), 10);

    // { 10, 1, 2, 3, 4, 10, 5 }

    auto check = a.begin();
    EXPECT_EQ(*check, 10);
    ++check;
    EXPECT_EQ(*check, 1);
    ++check;
    EXPECT_EQ(*check, 2);
    ++check;
    EXPECT_EQ(*check, 3);
    ++check;
    EXPECT_EQ(*check, 4);
    ++check;
    EXPECT_EQ(*check, 10);
    ++check;
    EXPECT_EQ(*check, 5);

    s21::list<int> b;
    auto value = b.insert(a.begin(), 10);

    EXPECT_EQ(b.front(), 10);
    EXPECT_EQ(b.size(), 1);
    EXPECT_EQ(value, b.begin());

    b.insert(b.rbegin(), 15);
    EXPECT_EQ(b.front(), 15);
    EXPECT_EQ(b.size(), 2);
}

TEST(LIST, erase) {
    s21::list<int> a = {1, 2, 3, 4, 5};
    a.erase(a.begin());

    // { 2, 3, 4, 5}

    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(*(a.begin()), 2);

    a.erase(a.rbegin());

    // { 2, 3, 4}

    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(*(a.rbegin()), 4);

    a.erase(a.begin());
    a.erase(a.begin());
    a.erase(a.begin());

    EXPECT_EQ(a.size(), 0);

    s21::list<int> b = {1, 2};
    b.erase(b.rbegin());

    s21::list<int> c = {1, 2, 3, 4, 5};

    c.erase(c.begin() + 2);
}

TEST(LIST, push_pop) {
    s21::list<int> a = {1};

    a.push_back(2);
    a.push_front(3);

    // 3 1 2

    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(*(a.begin()), 3);
    EXPECT_EQ(*(++a.begin()), 1);
    EXPECT_EQ(*(a.begin() + 2), 2);

    a.pop_back();
    a.pop_front();

    // 1

    EXPECT_EQ(a.size(), 1);
    EXPECT_EQ(*(a.begin()), 1);

    a.pop_front();
}

TEST(LIST, swap) {
    s21::list<int> a = {1, 2, 3, 4, 5};
    s21::list<int> b;

    b.swap(a);

    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(b.size(), 5);

    auto iter = b.begin();
    EXPECT_EQ(*iter, 1);
    ++iter;
    EXPECT_EQ(*iter, 2);
    ++iter;
    EXPECT_EQ(*iter, 3);
    ++iter;
    EXPECT_EQ(*iter, 4);
    ++iter;
    EXPECT_EQ(*iter, 5);
}

TEST(LIST, merge) {
    s21::list<int> a = {1, 3, 5, 7, 9};
    s21::list<int> b = {2, 4, 6, 8};

    b.merge(a);

    auto iter = b.begin();
    EXPECT_EQ(*iter, 1);
    ++iter;
    EXPECT_EQ(*iter, 2);
    ++iter;
    EXPECT_EQ(*iter, 3);
    ++iter;
    EXPECT_EQ(*iter, 4);
    ++iter;
    EXPECT_EQ(*iter, 5);
    ++iter;
    EXPECT_EQ(*iter, 6);
    ++iter;
    EXPECT_EQ(*iter, 7);
    ++iter;
    EXPECT_EQ(*iter, 8);
}

TEST(LIST, reverse) {
    s21::list<int> a = {1, 2, 3, 4, 5};
    a.reverse();

    auto iter = a.begin();
    EXPECT_EQ(*iter, 5);
    ++iter;
    EXPECT_EQ(*iter, 4);
    ++iter;
    EXPECT_EQ(*iter, 3);
    ++iter;
    EXPECT_EQ(*iter, 2);
    ++iter;
    EXPECT_EQ(*iter, 1);
}

TEST(LIST, unique) {
    s21::list<int> a = {1, 1, 1, 1, 2, 2};

    a.unique();
    auto iter = a.begin();
    EXPECT_EQ(*iter, 1);
    ++iter;
    EXPECT_EQ(*iter, 2);
}

TEST(LIST, sort) {
    s21::list<int> a = {5, 4, 3, 2, 1};

    a.sort();

    auto iter = a.begin();
    EXPECT_EQ(*iter, 1);
    ++iter;
    EXPECT_EQ(*iter, 2);
    ++iter;
    EXPECT_EQ(*iter, 3);
    ++iter;
    EXPECT_EQ(*iter, 4);
    ++iter;
    EXPECT_EQ(*iter, 5);
}

TEST(LIST, splice) {
    s21::list<int> a = {1, 2, 3, 4, 5};
    s21::list<int> b = {10, 20, 30};

    a.splice(a.cbegin() + 2, b);

    auto iter = a.begin();
    EXPECT_EQ(*iter, 1);
    ++iter;
    EXPECT_EQ(*iter, 2);
    ++iter;
    EXPECT_EQ(*iter, 10);
    ++iter;
    EXPECT_EQ(*iter, 20);
    ++iter;
    EXPECT_EQ(*iter, 30);
    ++iter;
    EXPECT_EQ(*iter, 3);
    ++iter;
    EXPECT_EQ(*iter, 4);
    ++iter;
    EXPECT_EQ(*iter, 5);
}