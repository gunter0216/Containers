#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "../headers/s21_set.h"
#include "../headers/s21_tree.h"

template <typename Key>
bool eq_set(s21::set<Key> *set1, std::set<Key> *set2) {
    bool result = true;
    if (set1->size() == set2->size()) {
        if (set1->size() != 0) {
            typename s21::set<Key>::iterator iter1 = set1->begin();
            typename std::set<Key>::iterator iter2 = set2->begin();
            for (; iter1 != set1->end(); ++iter1, ++iter2) {
                if (*iter1 != *iter2 || *iter1 != *iter2) {
                    result = false;
                }
            }
        }
    } else {
        result = false;
    }
    return result;
}

template <typename Key>
bool eq_set_size(s21::set<Key> set1, std::set<Key> set2) {
    return set1.size() == set2.size();
}

TEST(SetTest, constructor_1) {
    s21::set<int> set1 = s21::set<int>();
    std::set<int> set2 = std::set<int>();
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, constructor_2) {
    s21::set<int> set1 = s21::set<int>({1, 2, 3});
    std::set<int> set2 = std::set<int>({1, 2, 3});
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, constructor_3) {
    s21::set<int> set1 = s21::set<int>({1, 2, 3});
    s21::set<int> set2 = s21::set<int>(set1);
    std::set<int> set3 = std::set<int>({1, 2, 3});
    std::set<int> set4 = std::set<int>(set3);
    ASSERT_TRUE(eq_set(&set1, &set3) && eq_set(&set2, &set4));
}

TEST(SetTest, constructor_4) {
    s21::set<int> set1 = s21::set<int>({1, 2, 3});
    s21::set<int> set2 = s21::set<int>(std::move(set1));
    std::set<int> set3 = std::set<int>({1, 2, 3});
    std::set<int> set4 = std::set<int>(std::move(set3));
    ASSERT_TRUE(eq_set(&set1, &set3) && eq_set(&set2, &set4));
}

TEST(SetTest, empty_1) {
    s21::set<int> set1 = s21::set<int>({1, 2, 3});
    std::set<int> set2 = std::set<int>({1, 2, 3});
    ASSERT_TRUE(set1.empty() == set2.empty());
}

TEST(SetTest, empty_2) {
    s21::set<int> set1 = s21::set<int>();
    std::set<int> set2 = std::set<int>();
    ASSERT_TRUE(set1.empty() == set2.empty());
}

TEST(SetTest, size_1) {
    s21::set<int> set1 = s21::set<int>({1, 2, 3});
    std::set<int> set2 = std::set<int>({1, 2, 3});
    ASSERT_TRUE(set1.size() == set2.size());
}

TEST(SetTest, size_2) {
    s21::set<int> set1 = s21::set<int>();
    std::set<int> set2 = std::set<int>();
    ASSERT_TRUE(set1.size() == set2.size());
}

TEST(SetTest, max_size_1) {
    s21::set<int> set1 = s21::set<int>({1, 2, 3});
    std::set<int> set2 = std::set<int>({1, 2, 3});
    ASSERT_TRUE(set1.size() > 0 && set2.size() > 0);
}

TEST(SetTest, clear_1) {
    s21::set<int> set1 = s21::set<int>({1, 2, 3});
    std::set<int> set2 = std::set<int>({1, 2, 3});
    set1.clear();
    set2.clear();
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, clear_2) {
    s21::set<int> set1 = s21::set<int>();
    std::set<int> set2 = std::set<int>();
    set1.clear();
    set2.clear();
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, insert_1) {
    s21::set<int> set1 = s21::set<int>();
    std::set<int> set2 = std::set<int>();
    set1.insert(1);
    set2.insert(1);
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, insert_2) {
    s21::set<int> set1 = s21::set<int>({1});
    std::set<int> set2 = std::set<int>({1});
    set1.insert(1);
    set2.insert(1);
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, insert_3) {
    s21::set<int> set1 = s21::set<int>();
    std::set<int> set2 = std::set<int>();
    set1.insert(1);
    set1.insert(2);
    set2.insert(1);
    set2.insert(2);
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, swap_1) {
    s21::set<int> set1 = s21::set<int>({1, 2, 3});
    s21::set<int> set2 = s21::set<int>();
    std::set<int> set3 = std::set<int>({1, 2, 3});
    std::set<int> set4 = std::set<int>();
    set1.swap(set2);
    set3.swap(set4);
    ASSERT_TRUE(eq_set(&set1, &set3) && eq_set(&set2, &set4));
}

TEST(SetTest, merge_1) {
    s21::set<int> set1 = s21::set<int>({1, 2});
    s21::set<int> set2 = s21::set<int>({3, 4});
    std::set<int> set3 = std::set<int>({1, 2, 3, 4});
    set1.merge(set2);
    ASSERT_TRUE(eq_set(&set1, &set3));
}

TEST(SetTest, find_1) {
    s21::set<int> set1 = s21::set<int>({1, 2, 3});
    std::set<int> set2 = std::set<int>({1, 2, 3});
    ASSERT_TRUE(*set1.find(1) == *set2.find(1) &&
                *set1.find(2) == *set2.find(2) &&
                *set1.find(3) == *set2.find(3));
}

TEST(SetTest, contains_1) {
    s21::set<int> set1 = s21::set<int>({1, 2, 3});
    ASSERT_TRUE(set1.contains(1) && !set1.contains(4));
}

TEST(SetTest, erase_1) {
    s21::set<int> set1 = s21::set<int>({1, 2, 3});
    std::set<int> set2 = std::set<int>({1, 2});
    set1.erase(--set1.end());
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, erase_2) {
    s21::set<int> set1 = s21::set<int>({1, 2, 3});
    std::set<int> set2 = std::set<int>({2, 3});
    set1.erase(set1.begin());
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, erase_3) {
    s21::set<int> set1 = s21::set<int>({1, 2});
    std::set<int> set2 = std::set<int>({2});
    set1.erase(set1.begin());
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, erase_4) {
    s21::set<int> set1 = s21::set<int>({1});
    std::set<int> set2 = std::set<int>();
    set1.erase(set1.begin());
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, erase_5) {
    s21::set<int> set1 = s21::set<int>({5, 3});
    std::set<int> set2 = std::set<int>({5});
    set1.erase(set1.begin());
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, erase_6) {
    s21::set<int> set1 = s21::set<int>({5, 3, 2, 4});
    std::set<int> set2 = std::set<int>({5, 2, 3});
    set1.erase(-- --set1.end());
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, erase_7) {
    s21::set<int> set1 = s21::set<int>({5, 3, 2, 4});
    std::set<int> set2 = std::set<int>({5, 2, 4});
    set1.erase(---- --set1.end());
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, erase_8) {
    s21::set<int> set1 = s21::set<int>({5, 3, 2, 4});
    std::set<int> set2 = std::set<int>({5, 4, 3});
    set1.erase(set1.begin());
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, erase_9) {
    s21::set<int> set1 = s21::set<int>({5, 3, 2, 4});
    std::set<int> set2 = std::set<int>({2, 4, 3});
    set1.erase(--set1.end());
    ASSERT_TRUE(eq_set(&set1, &set2));
}

TEST(SetTest, emplace_1) {
    s21::set<int> set1 = s21::set<int>({1, 2, 3});
    std::set<int> set2 = std::set<int>({1, 2, 3});
    s21::vector<std::pair<typename s21::set<int>::iterator, bool>> v1(
        set1.emplace());
    ASSERT_TRUE(eq_set(&set1, &set2) && v1.empty());
}

TEST(SetTest, emplace_2) {
    s21::set<int> set1 = s21::set<int>({1, 2});
    std::set<int> set2 = std::set<int>({1, 2, 3});
    s21::vector<std::pair<typename s21::set<int>::iterator, bool>> v1(
        set1.emplace(3));
    ASSERT_TRUE(eq_set(&set1, &set2) && *v1.at(0).first == 3 && v1.at(0).second == true);
}

TEST(SetTest, emplace_3) {
    s21::set<int> set1 = s21::set<int>({1, 2});
    std::set<int> set2 = std::set<int>({1, 2});
    s21::vector<std::pair<typename s21::set<int>::iterator, bool>> v1(
        set1.emplace(1));
    ASSERT_TRUE(eq_set(&set1, &set2) && *v1.at(0).first == 1 && v1.at(0).second == false);
}

TEST(SetTest, emplace_4) {
    s21::set<int> set1 = s21::set<int>({1, 2});
    std::set<int> set2 = std::set<int>({1, 2, 3, 4});
    s21::vector<std::pair<typename s21::set<int>::iterator, bool>> v1(
        set1.emplace(3, 4));
    ASSERT_TRUE(eq_set(&set1, &set2) && *v1.at(0).first == 3 && v1.at(0).second == true &&
                *v1.at(1).first == 4 && v1.at(1).second == true);
}

TEST(SetTest, emplace_5) {
    s21::set<int> set1 = s21::set<int>({1, 2});
    std::set<int> set2 = std::set<int>({1, 2, 4});
    s21::vector<std::pair<typename s21::set<int>::iterator, bool>> v1(
        set1.emplace(1, 4));
    ASSERT_TRUE(eq_set(&set1, &set2) && *v1.at(0).first == 1 && v1.at(0).second == false &&
                *v1.at(1).first == 4 && v1.at(1).second == true);
}

TEST(SetTest, iterator_1) {
    s21::set<int> set1 = s21::set<int>({5, 3, 2, 4});
    s21::set<int>::iterator iter = set1.begin();
    for (int i = 0; i < 4; ++i)
        iter++;
    for (int i = 0; i < 4; ++i)
        iter--;
    for (int i = 0; i < 4; ++i)
        ++iter;
    for (int i = 0; i < 4; ++i)
        --iter;
    ASSERT_EQ(*iter, 2);
}

TEST(SetTest, find_2) {
    s21::set<int> set1 = s21::set<int>({10, 5, 15, 7, 3, 2, 9, 8, 12, 17, 11});
    ASSERT_TRUE(*set1.find(5) == 5 &&
                *set1.find(10) == 10 &&
                *set1.find(15) == 15 &&
                *set1.find(7) == 7 &&
                *set1.find(3) == 3 &&
                *set1.find(2) == 2 &&
                *set1.find(9) == 9 &&
                *set1.find(8) == 8 &&
                *set1.find(12) == 12 &&
                *set1.find(17) == 17 &&
                *set1.find(11) == 11);
}

void test() {
    s21::set<int> set = s21::set<int>({1, 2, 3});
    set.erase(--set.end());
    set.print();
    std::set<int>::iterator iter;
}

int main(int argc, char **argv) {
    // test();
    // return 0;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
