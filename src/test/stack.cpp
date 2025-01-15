#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(STACK, default_constructor) {
    s21::stack<int> stack;

    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(STACK, constructor_with_initializer_list) {
    s21::stack<int> stack({1, 2, 3, 4, 5});

    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 5);
    EXPECT_EQ(stack.top(), 5);
}

TEST(STACK, copy_constructor) {
    s21::stack<int> stack1({1, 2, 3, 4, 5});
    s21::stack<int> stack2(stack1);

    EXPECT_FALSE(stack2.empty());
    EXPECT_EQ(stack2.size(), 5);
    EXPECT_EQ(stack2.top(), 5);
}

TEST(STACK, move_constructor) {
    s21::stack<int> stack1({1, 2, 3, 4, 5});
    s21::stack<int> stack2(std::move(stack1));

    EXPECT_FALSE(stack2.empty());
    EXPECT_EQ(stack2.size(), 5);
    EXPECT_EQ(stack2.top(), 5);
    EXPECT_TRUE(stack1.empty());
}

TEST(STACK, move_assignment) {
    s21::stack<int> stack1({1, 2, 3});
    s21::stack<int> stack2;

    stack2 = std::move(stack1);

    EXPECT_EQ(stack1.size(), 0);
    EXPECT_EQ(stack2.size(), 3);
}

TEST(STACK, top) {
    s21::stack<int> stack({1, 2, 3, 4, 5});

    EXPECT_EQ(stack.top(), 5);
}

TEST(STACK, empty) {
    s21::stack<int> stack;

    EXPECT_TRUE(stack.empty());
}

TEST(STACK, not_empty) {
    s21::stack<int> stack({1, 2, 3});

    EXPECT_FALSE(stack.empty());
}

TEST(STACK, size_empty_stack) {
    s21::stack<int> stack;

    EXPECT_EQ(stack.size(), 0);
}

TEST(STACK, size) {
    s21::stack<int> stack({1, 2, 3, 4, 5});

    EXPECT_EQ(stack.size(), 5);
}

TEST(STACK, push_and_top) {
    s21::stack<int> stack;

    stack.push(21);

    EXPECT_EQ(stack.top(), 21);
    EXPECT_EQ(stack.size(), 1);
}

TEST(STACK, pop) {
    s21::stack<int> stack({1, 2, 3});

    stack.pop();

    EXPECT_EQ(stack.top(), 2);
    EXPECT_EQ(stack.size(), 2);
}

TEST(STACK, pop_empty_stack) {
    s21::stack<int> stack;

    EXPECT_NO_THROW(stack.pop());
}

TEST(STACK, swap) {
    s21::stack<int> stack1({1, 2, 3});
    s21::stack<int> stack2({4, 5, 6});

    stack1.swap(stack2);

    EXPECT_EQ(stack1.top(), 6);
    EXPECT_EQ(stack2.top(), 3);
}

TEST(STACK, swap_empty_stack) {
    s21::stack<int> stack1;
    s21::stack<int> stack2;

    stack1.swap(stack2);

    EXPECT_EQ(stack1.size(), 0);
    EXPECT_EQ(stack2.size(), 0);
}

TEST(STACK, push_and_pop) {
    s21::stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.pop();
    EXPECT_EQ(stack.top(), 2);
    stack.push(4);
    EXPECT_EQ(stack.top(), 4);
}

TEST(STACK, push_rvalue_and_pop) {
    s21::stack<std::string> stack;
    stack.push("one");
    stack.push("two");
    stack.push("three");
    stack.pop();
    EXPECT_EQ(stack.top(), "two");
    stack.push("four");
    EXPECT_EQ(stack.top(), "four");
}

TEST(STACK, swap_with_empty) {
    s21::stack<int> stack1({1, 2, 3});
    s21::stack<int> stack2;

    stack1.swap(stack2);

    EXPECT_EQ(stack1.size(), 0);
    EXPECT_EQ(stack2.size(), 3);
}

TEST(STACK, swap_with_different_containers) {
    s21::stack<int, std::vector<int>> stack1({1, 2, 3});
    s21::stack<int, std::vector<int>> stack2({4, 5, 6});

    stack1.swap(stack2);

    EXPECT_EQ(stack1.top(), 6);
    EXPECT_EQ(stack2.top(), 3);
    EXPECT_EQ(stack1.size(), 3);
    EXPECT_EQ(stack2.size(), 3);
}

TEST(STACK, Insert_many_back) {
    s21::stack<int> stack({1, 2});

    stack.insert_many_back(4, 5);

    EXPECT_EQ(stack.top(), 5);
    stack.pop();
    EXPECT_EQ(stack.top(), 4);
    stack.pop();
    EXPECT_EQ(stack.top(), 2);
}