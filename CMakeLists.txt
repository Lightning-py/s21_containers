# Устанавливаем минимальную версию CMake
cmake_minimum_required(VERSION 3.14)

# Название проекта
project(s21_containers)

# Устанавливаем стандарт C++ (C++17 или выше)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем поддержку Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Добавляем исходные файлы
set(SOURCES
        src/s21_containers.h
        src/s21_containersplus.h
        src/array/s21_array.h
        src/linked_list/s21_list.h
        src/map/s21_map.h
        src/multiset/s21_multiset.h
        src/queue/s21_queue.h
        src/set/s21_set.h
        src/shared/shared.cpp
        src/stack/s21_stack.h
        src/vector/s21_vector.h
        src/binary_tree/binary_tree.h
)

set(TEST_SOURCES
        src/test/array.cpp
        src/test/list.cpp
        src/test/map.cpp
        src/test/queue.cpp
        src/test/set.cpp
        src/test/stack.cpp
        src/test/vector.cpp
        src/test/test.cpp
        src/test/multiset.cpp
)

add_executable(s21_containers_tests ${TEST_SOURCES} ${SOURCES})

target_link_libraries(s21_containers_tests ${GTEST_LIBRARIES} pthread)

add_test(NAME s21_containers_tests COMMAND s21_containers_tests)