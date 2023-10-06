#include <gtest/gtest.h>

#include <array>
#include <iostream>

#include "../headers/s21_array.h"

template <typename T, size_t size>
bool eq_array(s21::array<T, size> arr1, std::array<T, size> arr2) {
    bool result = true;
    if (arr1.size() == arr2.size()) {
        typename s21::array<T, size>::iterator iter1 = arr1.begin();
        typename std::array<T, size>::iterator iter2 = arr2.begin();
        while (iter1 != arr1.end() && iter2 != arr2.end()) {
            if (*iter1 != *iter2) {
                result = false;
                break;
            }
            iter1++;
            iter2++;
        }
    } else {
        result = false;
    }
    return result;
}

TEST(ArrayTest, constuctor_default) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    std::array<int, 5> std_arr{0, 1, 2, 3, 4};
    ASSERT_TRUE(eq_array(s21_arr, std_arr));
}

TEST(ArrayTest, constuctor_with_copy) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    std::array<int, 5> std_arr{0, 1, 2, 3, 4};
    s21::array<int, 5> s21_new_arr(s21_arr);
    std::array<int, 5> std_new_arr(std_arr);
    ASSERT_TRUE(eq_array(s21_new_arr, std_new_arr));
}

TEST(ArrayTest, constuctor_with_move) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    std::array<int, 5> std_arr{0, 1, 2, 3, 4};
    s21::array<int, 5> s21_move_arr = std::move(s21_arr);
    std::array<int, 5> std_move_arr = std::move(std_arr);
    ASSERT_TRUE(eq_array(s21_move_arr, std_move_arr));
}

TEST(ArrayTest, acces_by_at) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    std::array<int, 5> std_arr{0, 1, 2, 3, 4};
    ASSERT_TRUE(s21_arr.at(3) == std_arr.at(3));
}

TEST(ArrayTest, acces_by_brackets) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    std::array<int, 5> std_arr{0, 1, 2, 3, 4};
    ASSERT_TRUE(s21_arr[3] == std_arr[3]);
}

TEST(ArrayTest, acces_by_front) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    std::array<int, 5> std_arr{0, 1, 2, 3, 4};
    ASSERT_TRUE(s21_arr.front() == std_arr.front());
}

TEST(ArrayTest, acces_by_back) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    std::array<int, 5> std_arr{0, 1, 2, 3, 4};
    ASSERT_TRUE(s21_arr.back() == std_arr.back());
}

TEST(ArrayTest, acces_by_data) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    std::array<int, 5> std_arr{0, 1, 2, 3, 4};
    auto s21_data = s21_arr.data();
    auto std_data = std_arr.data();
    for (auto i = 0; i < 5; ++i) {
        ASSERT_TRUE(s21_data[i] == std_data[i]);
    }
}

TEST(ArrayTest, iterator_begin) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    std::array<int, 5> std_arr{0, 1, 2, 3, 4};
    auto s21_it = s21_arr.begin();
    auto std_it = std_arr.begin();
    ++s21_it;
    ++std_it;
    ASSERT_TRUE(*(s21_it) == *(std_it));
}

TEST(ArrayTest, iterator_end) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    std::array<int, 5> std_arr{0, 1, 2, 3, 4};
    auto s21_it = s21_arr.end();
    auto std_it = std_arr.end();
    --s21_it;
    --std_it;
    ASSERT_TRUE(*(s21_it) == *(std_it));
}

TEST(ArrayTest, capacity_empty) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    ASSERT_FALSE(s21_arr.empty());
}

TEST(ArrayTest, capacity_size) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    ASSERT_EQ(s21_arr.size(), 5);
}

TEST(ArrayTest, capacity_max_size) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    ASSERT_EQ(s21_arr.max_size(), 5);
}

TEST(ArrayTest, modifier_swap) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    s21::array<int, 5> s21_arr1{4, 3, 2, 1, 0};
    s21::array<int, 5> s21_arr2{4, 3, 2, 1, 0};

    s21_arr.swap(s21_arr2);
    for (size_t i = 0; i < s21_arr.size(); ++i) {
        ASSERT_TRUE(s21_arr[i] == s21_arr1[i]);
    }
}

TEST(ArrayTest, modifier_fill) {
    s21::array<int, 5> s21_arr{0, 1, 2, 3, 4};
    s21_arr.fill(123);
    for (size_t i = 0; i < s21_arr.size(); ++i) {
        ASSERT_EQ(s21_arr[i], 123);
    }
}


int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
