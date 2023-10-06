#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../headers/s21_vector.h"

template <typename T>
bool eq_vector(s21::vector<T> *vec1, std::vector<T> *vec2) {
    bool result = true;
    if (vec1->size() == vec2->size()) {
        typename s21::vector<T>::iterator iter1 = (vec1->begin());
        typename std::vector<T>::iterator iter2 = (vec2->begin());
        while (iter1 != vec1->end() && iter2 != vec2->end()) {
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

TEST(VectorTest, constuctor) {
    s21::vector<int> s21_vec;
    std::vector<int> std_vec;
    ASSERT_TRUE(eq_vector(&s21_vec, &std_vec));
}

TEST(VectorTest, constuctor_with_param) {
    s21::vector<int> s21_vec(5);
    s21::vector<int> std_vec(5);
    ASSERT_TRUE(s21_vec.size() == std_vec.size());
}

TEST(VectorTest, constuctor_default) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    std::vector<int> std_vec{0, 1, 2, 3, 4};
    ASSERT_TRUE(eq_vector(&s21_vec, &std_vec));
}

TEST(VectorTest, constuctor_with_copy) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    std::vector<int> std_vec{0, 1, 2, 3, 4};
    s21::vector<int> s21_new_vec(s21_vec);
    std::vector<int> std_new_vec(std_vec);
    ASSERT_TRUE(eq_vector(&s21_new_vec, &std_new_vec));
}

TEST(VectorTest, constuctor_with_move) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    std::vector<int> std_vec{0, 1, 2, 3, 4};
    s21::vector<int> s21_move_vec = std::move(s21_vec);
    std::vector<int> std_move_vec = std::move(std_vec);
    ASSERT_TRUE(eq_vector(&s21_move_vec, &std_move_vec));
}

TEST(VectorTest, acces_by_at) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    std::vector<int> std_vec{0, 1, 2, 3, 4};
    ASSERT_TRUE(s21_vec.at(3) == std_vec.at(3));
}

TEST(VectorTest, acces_by_brackets) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    std::vector<int> std_vec{0, 1, 2, 3, 4};
    ASSERT_TRUE(s21_vec[3] == std_vec[3]);
}

TEST(VectorTest, acces_by_front) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    std::vector<int> std_vec{0, 1, 2, 3, 4};
    ASSERT_TRUE(s21_vec.front() == std_vec.front());
}

TEST(VectorTest, acces_by_back) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    std::vector<int> std_vec{0, 1, 2, 3, 4};
    ASSERT_TRUE(s21_vec.back() == std_vec.back());
}

TEST(VectorTest, acces_by_data) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    std::vector<int> std_vec{0, 1, 2, 3, 4};
    ASSERT_TRUE((*s21_vec.data()) == *(std_vec.data()));
}

TEST(VectorTest, iterator_begin) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    std::vector<int> std_vec{0, 1, 2, 3, 4};
    auto s21_it = s21_vec.begin();
    auto std_it = std_vec.begin();
    ++s21_it;
    ++std_it;
    ASSERT_TRUE(*(s21_it) == *(std_it));
}

TEST(VectorTest, iterator_end) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    std::vector<int> std_vec{0, 1, 2, 3, 4};
    auto s21_it = s21_vec.end();
    auto std_it = std_vec.end();
    --s21_it;
    --std_it;
    ASSERT_TRUE(*(s21_it) == *(std_it));
}

TEST(VectorTest, capacity_empty) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    ASSERT_FALSE(s21_vec.empty());
}

TEST(VectorTest, capacity_size) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    ASSERT_EQ(s21_vec.size(), 5);
}

TEST(VectorTest, capacity_reserve) {
    s21::vector<double> s21_vec{0, 1, 2, 3, 4};
    s21_vec.reserve(40);
    ASSERT_EQ(s21_vec.capacity(), 40);
}

TEST(VectorTest, capacity_capacity) {
    s21::vector<double> s21_vec{0, 1, 2, 3, 4};
    s21_vec.shrink_to_fit();
    ASSERT_EQ(s21_vec.capacity(), 5);
}

TEST(VectorTest, capacity_shrink_to_fit) {
    s21::vector<double> s21_vec{0, 1, 2, 3, 4};
    ASSERT_EQ(s21_vec.capacity(), 8);
}

TEST(VectorTest, modifier_clear) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    s21_vec.clear();
    ASSERT_EQ(s21_vec.size(), 0);
}

TEST(VectorTest, modifier_insert) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    s21::vector<int>::iterator s21_iter = s21_vec.begin();
    s21_vec.insert(s21_iter += 3, 123);
    ASSERT_EQ(s21_vec[3], 123);
}

TEST(VectorTest, modifier_push_back) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    s21_vec.push_back(123);
    ASSERT_EQ(s21_vec[5], 123);
}

TEST(VectorTest, modifier_pop_back) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    s21_vec.pop_back();
    ASSERT_EQ(s21_vec.size(), 4);
}

TEST(VectorTest, modifier_swap) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    s21::vector<int> s21_vec1{4, 3, 2, 1, 0};
    s21::vector<int> s21_vec2{4, 3, 2, 1, 0};

    s21_vec.swap(s21_vec2);
    for (size_t i = 0; i < s21_vec.size(); ++i) {
        ASSERT_TRUE(s21_vec[i] == s21_vec1[i]);
    }
}

TEST(VectorTest, emplace) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    s21::vector<int>::const_iterator s21_iter = s21_vec.cbegin();
    s21_vec.emplace(s21_iter+=2, 3, 4);
    ASSERT_EQ(s21_vec[2], 3);
}

TEST(VectorTest, emplace_back) {
    s21::vector<int> s21_vec{0, 1, 2, 3, 4};
    s21_vec.emplace_back(2, 3, 4);
    ASSERT_EQ(s21_vec[6], 3);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
