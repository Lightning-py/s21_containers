cmake_minimum_required(VERSION 3.29)
project(CPP2_s21_containers_1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")


include_directories(src)
include_directories(src/vector)
#include_directories(src/linked_list)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test
        src/test/test.cpp
        #        src/linked_list/linked_list.tpp
        #        src/linked_list/linked_list.h
)

target_link_libraries(test ${GTEST_LIBRARIES} pthread)

