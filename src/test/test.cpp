//
// Created by sergey on 05.12.24.
//

#include <gtest/gtest.h>

#define INCLUDE

#ifdef INCLUDE

#include "array.cpp"
#include "list.cpp"
#include "map.cpp"
#include "multiset.cpp"
#include "queue.cpp"
#include "set.cpp"
#include "stack.cpp"
#include "vector.cpp"

#endif

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}