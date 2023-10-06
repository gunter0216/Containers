#include <gtest/gtest.h>

#include <iostream>
#include <list>
#include <stack>

#include "../headers/s21_list.h"
#include "../headers/s21_stack.h"

template <typename T>
bool eq_stack(s21::stack<T> stack1, std::stack<T> stack2) {
    bool result = true;
    if (stack1.size() == stack2.size()) {
        int size = stack1.size();
        for (int i = 0; i < size; i++) {
            if (stack1.top() != stack2.top())
                result = false;
            stack1.pop();
            stack2.pop();
        }
    } else {
        result = false;
    }
    return result;
}

template <typename T>
bool eq_stack_size(s21::stack<T> stack1, std::stack<T> stack2) {
    return stack1.size() == stack2.size();
}

TEST(ListTest, constructor_1) {
    s21::stack<int> stack1 = s21::stack<int>();
    std::stack<int> stack2 = std::stack<int>();
    ASSERT_TRUE(eq_stack(stack1, stack2));
}

TEST(ListTest, constructor_2) {
    s21::stack<int> stack1 = s21::stack<int>({1, 2, 3});
    std::stack<int> stack2 = std::stack<int>({1, 2, 3});
    ASSERT_TRUE(eq_stack(stack1, stack2));
}

TEST(ListTest, constructor_3) {
    s21::stack<int> stack1 = s21::stack<int>({1, 2});
    s21::stack<int> stack2 = s21::stack<int>(stack1);
    std::stack<int> stack3 = std::stack<int>({1, 2});
    std::stack<int> stack4 = std::stack<int>(stack3);
    ASSERT_TRUE(eq_stack(stack1, stack3) && eq_stack(stack2, stack4));
}

TEST(ListTest, constructor_4) {
    s21::stack<int> stack1 = s21::stack<int>({1, 2});
    s21::stack<int> stack2 = s21::stack<int>(std::move(stack1));
    std::stack<int> stack3 = std::stack<int>({1, 2});
    std::stack<int> stack4 = std::stack<int>(std::move(stack3));
    ASSERT_TRUE(eq_stack(stack1, stack3) && eq_stack(stack2, stack4));
}

TEST(ListTest, eq_1) {
    s21::stack<int> stack1 = s21::stack<int>({1, 2});
    std::stack<int> stack2 = std::stack<int>({1, 2});
    stack1 = s21::stack<int>({1, 2});
    stack2 = std::stack<int>({1, 2});
    ASSERT_TRUE(eq_stack(stack1, stack2));
}

TEST(ListTest, empty_1) {
    s21::stack<int> stack1 = s21::stack<int>({1, 2, 3});
    std::stack<int> stack2 = std::stack<int>({1, 2, 3});
    ASSERT_TRUE(stack1.empty() == stack2.empty());
}

TEST(ListTest, empty_2) {
    s21::stack<int> stack1 = s21::stack<int>();
    std::stack<int> stack2 = std::stack<int>();
    ASSERT_TRUE(stack1.empty() == stack2.empty());
}

TEST(ListTest, size_1) {
    s21::stack<int> stack1 = s21::stack<int>({1, 2});
    std::stack<int> stack2 = std::stack<int>({1, 2});
    ASSERT_TRUE(stack1.size() == stack2.size());
}

TEST(ListTest, size_2) {
    s21::stack<int> stack1 = s21::stack<int>();
    std::stack<int> stack2 = std::stack<int>();
    ASSERT_TRUE(stack1.size() == stack2.size());
}

TEST(ListTest, top_1) {
    s21::stack<int> stack1 = s21::stack<int>({1, 2, 3});
    std::stack<int> stack2 = std::stack<int>({1, 2, 3});
    ASSERT_TRUE(stack1.top() == stack2.top());
}

TEST(ListTest, push_1) {
    s21::stack<int> stack1 = s21::stack<int>({1, 2, 3});
    std::stack<int> stack2 = std::stack<int>({1, 2, 3});
    stack1.push(5);
    stack2.push(5);
    ASSERT_TRUE(eq_stack(stack1, stack2));
}

TEST(ListTest, pop_1) {
    s21::stack<int> stack1 = s21::stack<int>({1, 2, 3});
    std::stack<int> stack2 = std::stack<int>({1, 2, 3});
    stack1.pop();
    stack2.pop();
    ASSERT_TRUE(eq_stack(stack1, stack2));
}

TEST(ListTest, swap_1) {
    s21::stack<int> stack1 = s21::stack<int>({1, 2, 3});
    s21::stack<int> stack2 = s21::stack<int>({2, 3, 4});
    std::stack<int> stack3 = std::stack<int>({1, 2, 3});
    std::stack<int> stack4 = std::stack<int>({2, 3, 4});
    stack1.swap(stack2);
    stack3.swap(stack4);
    ASSERT_TRUE(eq_stack(stack1, stack3) && eq_stack(stack2, stack4));
}

TEST(ListTest, emplace_front_1) {
    s21::stack<int> stack1 = s21::stack<int>({1, 2, 3});
    std::stack<int> stack2 = std::stack<int>({1, 2, 3});
    stack1.emplace_front();
    ASSERT_TRUE(eq_stack(stack1, stack2));
}

TEST(ListTest, emplace_front_2) {
    s21::stack<int> stack1 = s21::stack<int>({1, 2, 3});
    std::stack<int> stack2 = std::stack<int>({6, 1, 2, 3});
    stack1.emplace_front(6);
    ASSERT_TRUE(eq_stack(stack1, stack2));
}

TEST(ListTest, emplace_front_3) {
    s21::stack<int> stack1 = s21::stack<int>({1, 2, 3});
    std::stack<int> stack2 = std::stack<int>({6, 7, 1, 2, 3});
    stack1.emplace_front(6, 7);
    ASSERT_TRUE(eq_stack(stack1, stack2));
}

void test() {
    s21::stack<int> stack1 = s21::stack<int>({1, 2, 3});
    std::stack<int> stack2 = std::stack<int>({1, 2, 4});
    std::cout << eq_stack(stack1, stack2) << std::endl;
}

int main(int argc, char **argv) {
    // test();
    // return 0;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
