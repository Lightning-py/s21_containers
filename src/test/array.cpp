#include <gtest/gtest.h>
#include "array/s21_array.h"

class S21ArrayTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Constructor Tests
TEST_F(S21ArrayTest, DefaultConstructor) {
s21::s21_array<int, 5> arr;
EXPECT_EQ(arr.size(), 5);
EXPECT_FALSE(arr.empty());
}

TEST_F(S21ArrayTest, InitializerListConstructor) {
s21::s21_array<int, 5> arr = {1, 2, 3, 4, 5};
EXPECT_EQ(arr[0], 1);
EXPECT_EQ(arr[4], 5);

// Test partial initialization
s21::s21_array<int, 5> arr2 = {1, 2, 3};
EXPECT_EQ(arr2[0], 1);
EXPECT_EQ(arr2[2], 3);
EXPECT_EQ(arr2[3], 0); // Should be zero-initialized
}

TEST_F(S21ArrayTest, InitializerListTooLarge) {
EXPECT_THROW((s21::s21_array<int, 3>{1, 2, 3, 4}), std::out_of_range);
}

// Copy Constructor Test
TEST_F(S21ArrayTest, CopyConstructor) {
s21::s21_array<int, 3> arr1 = {1, 2, 3};
s21::s21_array<int, 3> arr2(arr1);
EXPECT_EQ(arr1[0], arr2[0]);
EXPECT_EQ(arr1[1], arr2[1]);
EXPECT_EQ(arr1[2], arr2[2]);
}

// Move Constructor Test
TEST_F(S21ArrayTest, MoveConstructor) {
s21::s21_array<int, 3> arr1 = {1, 2, 3};
s21::s21_array<int, 3> arr2(std::move(arr1));
EXPECT_EQ(arr2[0], 1);
EXPECT_EQ(arr2[1], 2);
EXPECT_EQ(arr2[2], 3);
}

// Element Access Tests
TEST_F(S21ArrayTest, At) {
s21::s21_array<int, 3> arr = {1, 2, 3};
EXPECT_EQ(arr.at(0), 1);
EXPECT_EQ(arr.at(2), 3);
EXPECT_THROW(arr.at(3), std::out_of_range);
}

TEST_F(S21ArrayTest, OperatorBrackets) {
s21::s21_array<int, 3> arr = {1, 2, 3};
EXPECT_EQ(arr[0], 1);
EXPECT_EQ(arr[2], 3);
}

TEST_F(S21ArrayTest, FrontBack) {
s21::s21_array<int, 3> arr = {1, 2, 3};
EXPECT_EQ(arr.front(), 1);
EXPECT_EQ(arr.back(), 3);
}

// Iterator Tests
TEST_F(S21ArrayTest, Iterators) {
s21::s21_array<int, 3> arr = {1, 2, 3};
int sum = 0;
for (auto it = arr.begin(); it != arr.end(); ++it) {
sum += *it;
}
EXPECT_EQ(sum, 6);
}

TEST_F(S21ArrayTest, ConstIterators) {
const s21::s21_array<int, 3> arr = {1, 2, 3};
int sum = 0;
for (auto it = arr.begin(); it != arr.end(); ++it) {
sum += *it;
}
EXPECT_EQ(sum, 6);
}

// Capacity Tests
TEST_F(S21ArrayTest, Empty) {
s21::s21_array<int, 0> empty_arr;
s21::s21_array<int, 3> non_empty_arr = {1, 2, 3};

EXPECT_TRUE(empty_arr.empty());
EXPECT_FALSE(non_empty_arr.empty());
}

TEST_F(S21ArrayTest, Size) {
s21::s21_array<int, 5> arr;
EXPECT_EQ(arr.size(), 5);
EXPECT_EQ(arr.max_size(), 5);
}

// Modifiers Tests
TEST_F(S21ArrayTest, Fill) {
s21::s21_array<int, 3> arr;
arr.fill(42);
EXPECT_EQ(arr[0], 42);
EXPECT_EQ(arr[1], 42);
EXPECT_EQ(arr[2], 42);
}

TEST_F(S21ArrayTest, Swap) {
s21::s21_array<int, 3> arr1 = {1, 2, 3};
s21::s21_array<int, 3> arr2 = {4, 5, 6};
arr1.swap(arr2);
EXPECT_EQ(arr1[0], 4);
EXPECT_EQ(arr1[1], 5);
EXPECT_EQ(arr1[2], 6);
EXPECT_EQ(arr2[0], 1);
EXPECT_EQ(arr2[1], 2);
EXPECT_EQ(arr2[2], 3);
}

// Edge Cases
TEST_F(S21ArrayTest, EmptyArrayOperations) {
s21::s21_array<int, 0> arr;
EXPECT_TRUE(arr.empty());
EXPECT_EQ(arr.size(), 0);
EXPECT_EQ(arr.begin(), arr.end());
}

TEST_F(S21ArrayTest, NonTrivialType) {
s21::s21_array<std::string, 3> arr = {"Hello", "World", "!"};
EXPECT_EQ(arr[0], "Hello");
EXPECT_EQ(arr[1], "World");
EXPECT_EQ(arr[2], "!");
}

// New Tests to Increase Coverage
TEST_F(S21ArrayTest, FillAndSwapEmptyArray) {
s21::s21_array<int, 0> arr1, arr2;
arr1.swap(arr2);
arr1.fill(0);
EXPECT_TRUE(arr1.empty());
}

TEST_F(S21ArrayTest, AccessOutOfBounds) {
s21::s21_array<int, 3> arr = {1, 2, 3};
EXPECT_THROW(arr.at(5), std::out_of_range);
}

TEST_F(S21ArrayTest, SwapSelf) {
s21::s21_array<int, 3> arr = {1, 2, 3};
arr.swap(arr);
EXPECT_EQ(arr[0], 1);
EXPECT_EQ(arr[1], 2);
EXPECT_EQ(arr[2], 3);
}

TEST_F(S21ArrayTest, SwapDifferentSizes) {
s21::s21_array<int, 5> arr1 = {1, 2, 3, 4, 5};
s21::s21_array<int, 5> arr2 = {6, 7, 8, 9, 10};
arr1.swap(arr2);
EXPECT_EQ(arr1[0], 6);
EXPECT_EQ(arr2[0], 1);
}
