//
// Created by sergey on 05.12.24.
//

#include <gtest/gtest.h>

#include "array.cpp"
#include "list.cpp"
#include "map.cpp"
#include "queue.cpp"
#include "set.cpp"
#include "stack.cpp"
#include "vector.cpp"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}