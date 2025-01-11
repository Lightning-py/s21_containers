//
// Created by sergey on 05.01.25.
//

#include <gtest/gtest.h>

#include "../s21_containersplus.h"

TEST(MULTISET, insert) {
    s21::multiset<int> multiset;

    for (int i = 0; i < 5; ++i) {
        multiset.insert(1);
    }

    EXPECT_EQ(multiset.count(1), 5);
}