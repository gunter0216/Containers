#include <gtest/gtest.h>

#include <iostream>
#include <list>
#include <queue>

#include "../headers/s21_list.h"
#include "../headers/s21_queue.h"

template <typename T>
bool eq_queue(s21::queue<T> que1, std::queue<T> que2) {
    bool result = true;
    if (que1.size() == que2.size()) {
        int size = que1.size();
        for (int i = 0; i < size; i++) {
            if (que1.front() != que2.front())
                result = false;
            que1.pop();
            que2.pop();
        }
    } else {
        result = false;
    }
    return result;
}

template <typename T>
bool eq_queue_size(s21::queue<T> que1, std::queue<T> que2) {
    return que1.size() == que2.size();
}

TEST(ListTest, constructor_1) {
    s21::queue<int> que1 = s21::queue<int>();
    std::queue<int> que2 = std::queue<int>();
    ASSERT_TRUE(eq_queue(que1, que2));
}

TEST(ListTest, constructor_2) {
    s21::queue<int> que1 = s21::queue<int>({1, 2, 3});
    std::queue<int> que2 = std::queue<int>({1, 2, 3});
    ASSERT_TRUE(eq_queue(que1, que2));
}

TEST(ListTest, constructor_3) {
    s21::queue<int> que1 = s21::queue<int>({1, 2});
    s21::queue<int> que2 = s21::queue<int>(que1);
    std::queue<int> que3 = std::queue<int>({1, 2});
    std::queue<int> que4 = std::queue<int>(que3);
    ASSERT_TRUE(eq_queue(que1, que3) && eq_queue(que2, que4));
}

TEST(ListTest, constructor_4) {
    s21::queue<int> que1 = s21::queue<int>({1, 2});
    s21::queue<int> que2 = s21::queue<int>(std::move(que1));
    std::queue<int> que3 = std::queue<int>({1, 2});
    std::queue<int> que4 = std::queue<int>(std::move(que3));
    ASSERT_TRUE(eq_queue(que1, que3) && eq_queue(que2, que4));
}

TEST(ListTest, constructor_5) {
    s21::queue<int, s21::list<int>> que1 = s21::queue<int>({1, 2});
    std::queue<int, std::list<int>> que2 = std::queue<int, std::list<int>>({1, 2});
    ASSERT_TRUE(que1.front() == que2.front() && que1.back() == que2.back());
}

TEST(ListTest, eq_1) {
    s21::queue<int> que1 = s21::queue<int>({1, 2});
    s21::queue<int> que2 = s21::queue<int>({1, 2});
    std::queue<int> que3 = std::queue<int>({1, 2});
    std::queue<int> que4 = std::queue<int>({1, 2});
    que2 = s21::queue<int>({1, 2});
    que4 = std::queue<int>({1, 2});
    ASSERT_TRUE(eq_queue(que1, que3) && eq_queue(que2, que4));
}

TEST(ListTest, empty_1) {
    s21::queue<int> que1 = s21::queue<int>({1, 2, 3});
    std::queue<int> que2 = std::queue<int>({1, 2, 3});
    ASSERT_TRUE(que1.empty() == que2.empty());
}

TEST(ListTest, empty_2) {
    s21::queue<int> que1 = s21::queue<int>();
    std::queue<int> que2 = std::queue<int>();
    ASSERT_TRUE(que1.empty() == que2.empty());
}

TEST(ListTest, size_1) {
    s21::queue<int> que1 = s21::queue<int>({1, 2});
    std::queue<int> que2 = std::queue<int>({1, 2});
    ASSERT_TRUE(que1.size() == que2.size());
}

TEST(ListTest, size_2) {
    s21::queue<int> que1 = s21::queue<int>();
    std::queue<int> que2 = std::queue<int>();
    ASSERT_TRUE(que1.size() == que2.size());
}

TEST(ListTest, front_1) {
    s21::queue<int> que1 = s21::queue<int>({1, 2, 3});
    std::queue<int> que2 = std::queue<int>({1, 2, 3});
    ASSERT_TRUE(que1.front() == que2.front());
}

TEST(ListTest, back_1) {
    s21::queue<int> que1 = s21::queue<int>({1, 2, 3});
    std::queue<int> que2 = std::queue<int>({1, 2, 3});
    ASSERT_TRUE(que1.back() == que2.back());
}

TEST(ListTest, push_1) {
    s21::queue<int> que1 = s21::queue<int>({1, 2, 3});
    std::queue<int> que2 = std::queue<int>({1, 2, 3});
    que1.push(5);
    que2.push(5);
    ASSERT_TRUE(eq_queue(que1, que2));
}

TEST(ListTest, pop_1) {
    s21::queue<int> que1 = s21::queue<int>({1, 2, 3});
    std::queue<int> que2 = std::queue<int>({1, 2, 3});
    que1.pop();
    que2.pop();
    ASSERT_TRUE(eq_queue(que1, que2));
}

TEST(ListTest, swap_1) {
    s21::queue<int> que1 = s21::queue<int>({1, 2, 3});
    s21::queue<int> que2 = s21::queue<int>({2, 3, 4});
    std::queue<int> que3 = std::queue<int>({1, 2, 3});
    std::queue<int> que4 = std::queue<int>({2, 3, 4});
    que1.swap(que2);
    que3.swap(que4);
    ASSERT_TRUE(eq_queue(que1, que3) && eq_queue(que2, que4));
}

TEST(ListTest, emplace_back_1) {
    s21::queue<int> que1 = s21::queue<int>({1, 2, 3});
    std::queue<int> que2 = std::queue<int>({1, 2, 3});
    que1.emplace_back();
    ASSERT_TRUE(eq_queue(que1, que2));
}

TEST(ListTest, emplace_back_2) {
    s21::queue<int> que1 = s21::queue<int>({1, 2, 3});
    std::queue<int> que2 = std::queue<int>({1, 2, 3, 4});
    que1.emplace_back(4);
    ASSERT_TRUE(eq_queue(que1, que2));
}

TEST(ListTest, emplace_back_3) {
    s21::queue<int> que1 = s21::queue<int>({1, 2, 3});
    std::queue<int> que2 = std::queue<int>({1, 2, 3, 4, 5});
    que1.emplace_back(4, 5);
    ASSERT_TRUE(eq_queue(que1, que2));
}

void test() {
    s21::queue<int> que1 = s21::queue<int>({1, 2, 3});
    que1.emplace_back(1);
    while (que1.size()) {
        std::cout << que1.front() << std::endl;
        que1.pop();
    }
}

int main(int argc, char **argv) {
    // test();
    // return 0;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
