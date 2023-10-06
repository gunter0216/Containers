#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "../headers/s21_multiset.h"
#include "../headers/s21_tree.h"

template <typename Key>
bool eq_multiset(s21::multiset<Key> *ms1, std::multiset<Key> *ms2) {
    bool result = true;
    if (ms1->size() == ms2->size()) {
        if (ms1->size() != 0) {
            typename s21::multiset<Key>::iterator iter1 = ms1->begin();
            typename std::multiset<Key>::iterator iter2 = ms2->begin();
            for (; iter1 != ms1->end(); ++iter1, ++iter2) {
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
bool eq_multiset_size(s21::multiset<Key> ms1, std::multiset<Key> ms2) {
    return ms1.size() == ms2.size();
}

TEST(multisetTest, constructor_1) {
    s21::multiset<int> ms1 = s21::multiset<int>();
    std::multiset<int> ms2 = std::multiset<int>();
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, constructor_2) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
    std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, constructor_3) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
    s21::multiset<int> ms2 = s21::multiset<int>(ms1);
    std::multiset<int> ms3 = std::multiset<int>({1, 2, 3});
    std::multiset<int> ms4 = std::multiset<int>(ms3);
    ASSERT_TRUE(eq_multiset(&ms1, &ms3) && eq_multiset(&ms2, &ms4));
}

TEST(multisetTest, constructor_4) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
    s21::multiset<int> ms2 = s21::multiset<int>(std::move(ms1));
    std::multiset<int> ms3 = std::multiset<int>({1, 2, 3});
    std::multiset<int> ms4 = std::multiset<int>(std::move(ms3));
    ASSERT_TRUE(eq_multiset(&ms1, &ms3) && eq_multiset(&ms2, &ms4));
}

TEST(multisetTest, empty_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
    std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
    ASSERT_TRUE(ms1.empty() == ms2.empty());
}

TEST(multisetTest, empty_2) {
    s21::multiset<int> ms1 = s21::multiset<int>();
    std::multiset<int> ms2 = std::multiset<int>();
    ASSERT_TRUE(ms1.empty() == ms2.empty());
}

TEST(multisetTest, size_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
    std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
    ASSERT_TRUE(ms1.size() == ms2.size());
}

TEST(multisetTest, size_2) {
    s21::multiset<int> ms1 = s21::multiset<int>();
    std::multiset<int> ms2 = std::multiset<int>();
    ASSERT_TRUE(ms1.size() == ms2.size());
}

TEST(multisetTest, max_size_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
    std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
    ASSERT_TRUE(ms1.max_size() > 0 && ms2.max_size() > 0);
}

TEST(multisetTest, clear_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
    std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
    ms1.clear();
    ms2.clear();
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, clear_2) {
    s21::multiset<int> ms1 = s21::multiset<int>();
    std::multiset<int> ms2 = std::multiset<int>();
    ms1.clear();
    ms2.clear();
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, insert_1) {
    s21::multiset<int> ms1 = s21::multiset<int>();
    std::multiset<int> ms2 = std::multiset<int>();
    ms1.insert(1);
    ms2.insert(1);
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, insert_2) {
    s21::multiset<int> ms1 = s21::multiset<int>({1});
    std::multiset<int> ms2 = std::multiset<int>({1});
    ms1.insert(1);
    ms2.insert(1);
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, insert_3) {
    s21::multiset<int> ms1 = s21::multiset<int>();
    std::multiset<int> ms2 = std::multiset<int>();
    ms1.insert(1);
    ms1.insert(2);
    ms2.insert(1);
    ms2.insert(2);
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, swap_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
    s21::multiset<int> ms2 = s21::multiset<int>();
    std::multiset<int> ms3 = std::multiset<int>({1, 2, 3});
    std::multiset<int> ms4 = std::multiset<int>();
    ms1.swap(ms2);
    ms3.swap(ms4);
    ASSERT_TRUE(eq_multiset(&ms1, &ms3) && eq_multiset(&ms2, &ms4));
}

TEST(multisetTest, merge_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2});
    s21::multiset<int> ms2 = s21::multiset<int>({3, 4});
    std::multiset<int> ms3 = std::multiset<int>({1, 2, 3, 4});
    ms1.merge(ms2);
    ASSERT_TRUE(eq_multiset(&ms1, &ms3));
}

TEST(multisetTest, find_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
    std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
    ASSERT_TRUE(*ms1.find(1) == *ms2.find(1) &&
                *ms1.find(2) == *ms2.find(2) &&
                *ms1.find(3) == *ms2.find(3));
}

TEST(multisetTest, contains_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
    ASSERT_TRUE(ms1.contains(1) && !ms1.contains(4));
}

TEST(multisetTest, count_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 2, 2, 3});
    std::multiset<int> ms2 = std::multiset<int>({1, 2, 2, 2, 3});
    ASSERT_TRUE(ms1.count(1) == ms2.count(1) &&
                ms1.count(2) == ms2.count(2) &&
                ms1.count(3) == ms2.count(3) &&
                ms1.count(4) == ms2.count(4));
}

TEST(multisetTest, lower_bound_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 2, 2, 3});
    std::multiset<int> ms2 = std::multiset<int>({1, 2, 2, 2, 3});
    s21::multiset<int>::iterator iter1 = ms1.lower_bound(2);
    std::multiset<int>::iterator iter2 = ms2.lower_bound(2);
    ASSERT_TRUE(*(iter1) == *(iter2) &&
                *(--iter1) == *(--iter2) &&
                *(++ ++iter1) == *(++ ++iter2));
}

TEST(multisetTest, upper_bound_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 2, 2, 3});
    std::multiset<int> ms2 = std::multiset<int>({1, 2, 2, 2, 3});
    s21::multiset<int>::iterator iter1 = ms1.upper_bound(2);
    std::multiset<int>::iterator iter2 = ms2.upper_bound(2);
    ASSERT_TRUE(*(iter1) == *(iter2) &&
                *(--iter1) == *(--iter2));
}

TEST(multisetTest, equal_range_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 2, 2, 3});
    std::multiset<int> ms2 = std::multiset<int>({1, 2, 2, 2, 3});
    std::pair<typename s21::multiset<int>::iterator,
    typename s21::multiset<int>::iterator> iter1 = ms1.equal_range(2);
    std::pair<typename std::multiset<int>::iterator,
    typename std::multiset<int>::iterator> iter2 = ms2.equal_range(2);
    bool result = true;
    for (; iter1.first != iter1.second || iter2.first != iter2.second; ++iter1.first, ++iter2.first) {
        if (*(iter1.first) != *(iter2.first))
            result = false;
    }
    ASSERT_TRUE(result);
}

TEST(multisetTest, erase_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
    std::multiset<int> ms2 = std::multiset<int>({1, 2});
    ms1.erase(--ms1.end());
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, erase_2) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
    std::multiset<int> ms2 = std::multiset<int>({2, 3});
    ms1.erase(ms1.begin());
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, erase_3) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2});
    std::multiset<int> ms2 = std::multiset<int>({2});
    ms1.erase(ms1.begin());
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, erase_4) {
    s21::multiset<int> ms1 = s21::multiset<int>({1});
    std::multiset<int> ms2 = std::multiset<int>();
    ms1.erase(ms1.begin());
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, erase_5) {
    s21::multiset<int> ms1 = s21::multiset<int>({5, 3});
    std::multiset<int> ms2 = std::multiset<int>({5});
    ms1.erase(ms1.begin());
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, erase_6) {
    s21::multiset<int> ms1 = s21::multiset<int>({5, 3, 2, 4});
    std::multiset<int> ms2 = std::multiset<int>({5, 2, 3});
    ms1.erase(-- --ms1.end());
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, erase_7) {
    s21::multiset<int> ms1 = s21::multiset<int>({5, 3, 2, 4});
    std::multiset<int> ms2 = std::multiset<int>({5, 2, 4});
    ms1.erase(---- --ms1.end());
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, erase_8) {
    s21::multiset<int> ms1 = s21::multiset<int>({5, 3, 2, 4});
    std::multiset<int> ms2 = std::multiset<int>({5, 4, 3});
    ms1.erase(ms1.begin());
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, erase_9) {
    s21::multiset<int> ms1 = s21::multiset<int>({5, 3, 2, 4});
    std::multiset<int> ms2 = std::multiset<int>({2, 4, 3});
    ms1.erase(--ms1.end());
    ASSERT_TRUE(eq_multiset(&ms1, &ms2));
}

TEST(multisetTest, emplace_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
    std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
    s21::vector<std::pair<typename s21::multiset<int>::iterator, bool>> v1(
        ms1.emplace());
    ASSERT_TRUE(eq_multiset(&ms1, &ms2) && v1.empty());
}

TEST(multisetTest, emplace_2) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2});
    std::multiset<int> ms2 = std::multiset<int>({1, 2, 3});
    s21::vector<std::pair<typename s21::multiset<int>::iterator, bool>> v1(
        ms1.emplace(3));
    ASSERT_TRUE(eq_multiset(&ms1, &ms2) && *v1.at(0).first == 3 && v1.at(0).second == true);
}

TEST(multisetTest, emplace_3) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2});
    std::multiset<int> ms2 = std::multiset<int>({1, 1, 2});
    s21::vector<std::pair<typename s21::multiset<int>::iterator, bool>> v1(
        ms1.emplace(1));
    ASSERT_TRUE(eq_multiset(&ms1, &ms2) && *v1.at(0).first == 1 && v1.at(0).second == true);
}

TEST(multisetTest, emplace_4) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2});
    std::multiset<int> ms2 = std::multiset<int>({1, 2, 3, 4});
    s21::vector<std::pair<typename s21::multiset<int>::iterator, bool>> v1(
        ms1.emplace(3, 4));
    ASSERT_TRUE(eq_multiset(&ms1, &ms2) && *v1.at(0).first == 3 && v1.at(0).second == true &&
                *v1.at(1).first == 4 && v1.at(1).second == true);
}

TEST(multisetTest, emplace_5) {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2});
    std::multiset<int> ms2 = std::multiset<int>({1, 1, 2, 4});
    s21::vector<std::pair<typename s21::multiset<int>::iterator, bool>> v1(
        ms1.emplace(1, 4));
    ASSERT_TRUE(eq_multiset(&ms1, &ms2) && *v1.at(0).first == 1 && v1.at(0).second == true &&
                *v1.at(1).first == 4 && v1.at(1).second == true);
}

TEST(multisetTest, eq_1) {
    s21::multiset<int> ms1({1, 2, 2, 2, 3});
    std::multiset<int> ms2({1, 2, 2, 2, 3});
    s21::multiset<int> ms3({1});
    std::multiset<int> ms4({1});
    ms3 = std::move(ms1);
    ms4 = std::move(ms2);
    ASSERT_TRUE(eq_multiset(&ms1, &ms2) && eq_multiset(&ms3, &ms4));
}

TEST(multisetTest, iterator_1) {
    s21::multiset<int> ms1 = s21::multiset<int>({7, 14, 3, 5, 4, 1, 2, 0});
    s21::multiset<int>::iterator iter = ms1.begin();
    for (int i = 0; i < 7; ++i)
        iter++;
    for (int i = 0; i < 7; ++i)
        iter--;
    for (int i = 0; i < 7; ++i)
        ++iter;
    for (int i = 0; i < 7; ++i)
        --iter;
    ASSERT_EQ(*iter, 0);
}

void test() {
    s21::multiset<int> ms1 = s21::multiset<int>({1, 2, 3});
    // s21::multiset<int> ms2 = s21::multiset<int>(std::move(ms1));
    std::multiset<int> ms3 = std::multiset<int>({1, 2, 3});
    std::multiset<int> ms4 = std::multiset<int>(std::move(ms3));
    // std::cout << "### map2" << std::endl;
    // for (auto iter = ms2.begin(); iter != ms2.end(); iter++) {
    //     std::cout << "# " << (*iter) << std::endl;
    // }
}

int main(int argc, char **argv) {
    test();
    // return 0;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
