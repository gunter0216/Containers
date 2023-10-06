#include <gtest/gtest.h>

#include <iostream>
#include <list>

#include "../headers/s21_list.h"

template <typename T>
bool eq_list(s21::list<T> *lst1, std::list<T> *lst2) {
    bool result = true;
    if (lst1->size() == lst2->size()) {
        typename s21::list<T>::iterator iter1 = lst1->begin();
        typename std::list<T>::iterator iter2 = lst2->begin();
        while (iter1 != lst1->end() && iter2 != lst2->end()) {
            if (*iter1 != *iter2) {
                result = false;
                std::cout << "iter1 = " << *iter1 << std::endl;
                std::cout << "iter2 = " << *iter2 << std::endl;
            }
            ++iter1;
            ++iter2;
        }
    } else {
        result = false;
    }
    return result;
}

template <typename T>
bool eq_list_size(s21::list<T> *lst1, std::list<T> *lst2) {
    return lst1->size() == lst2->size();
}

TEST(ListTest, constructor_1) {
    s21::list<int> lst1 = s21::list<int>();
    std::list<int> lst2 = std::list<int>();
    lst1.push_back(1);
    lst1.push_back(2);
    lst1.push_back(3);
    lst2.push_back(1);
    lst2.push_back(2);
    lst2.push_back(3);
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, constructor_2) {
    s21::list<int> lst1 = s21::list<int>();
    std::list<int> lst2 = std::list<int>();
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, constructor_3) {
    s21::list<int> lst1 = s21::list<int>(5);
    std::list<int> lst2 = std::list<int>(5);
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, constructor_4) {
    s21::list<int> lst1 = s21::list<int>(0);
    std::list<int> lst2 = std::list<int>(0);
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, constructor_5) {
    s21::list<int> lst1 = s21::list<int>({1, 2, 3});
    std::list<int> lst2 = std::list<int>({1, 2, 3});
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, constructor_6) {
    s21::list<int> lst1 = s21::list<int>({});
    std::list<int> lst2 = std::list<int>({});
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, constructor_7) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    s21::list<int> lst3 = s21::list<int>(lst1);
    std::list<int> lst4 = std::list<int>(lst2);
    ASSERT_TRUE(eq_list(&lst3, &lst4) && eq_list(&lst1, &lst2));
}

TEST(ListTest, constructor_8) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    s21::list<int> lst3 = s21::list<int>(std::move(lst1));
    std::list<int> lst4 = std::list<int>(std::move(lst2));
    ASSERT_TRUE(eq_list(&lst3, &lst4) && eq_list(&lst1, &lst2));
}

TEST(ListTest, constructor_9) {
    s21::list<int> lst1(lst1);
    std::list<int> lst2(lst2);
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, front_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    ASSERT_TRUE(lst1.front() == lst2.front());
}

TEST(ListTest, back_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    ASSERT_TRUE(lst1.back() == lst2.back());
}

TEST(ListTest, clear_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    lst1.clear();
    lst2.clear();
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, insert_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    lst1.insert(lst1.begin(), 3);
    lst2.insert(lst2.begin(), 3);
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, erase_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    lst1.erase(lst1.begin());
    lst2.erase(lst2.begin());
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, push_back_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    lst1.push_back(3);
    lst2.push_back(3);
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, pop_back_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    lst1.pop_back();
    lst2.pop_back();
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, push_front_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    lst1.push_front(3);
    lst2.push_front(3);
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, push_front_2) {
    s21::list<int> lst1 = s21::list<int>();
    std::list<int> lst2 = std::list<int>();
    lst1.push_front(3);
    lst2.push_front(3);
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, pop_front_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    lst1.pop_front();
    lst2.pop_front();
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, swap_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    s21::list<int> lst3 = s21::list<int>({3, 4});
    std::list<int> lst4 = std::list<int>({3, 4});
    lst1.swap(lst3);
    lst2.swap(lst4);
    ASSERT_TRUE(eq_list(&lst1, &lst2) && eq_list(&lst3, &lst4));
}

TEST(ListTest, merge_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    s21::list<int> lst3 = s21::list<int>({3, 4});
    std::list<int> lst4 = std::list<int>({3, 4});
    lst1.merge(lst3);
    lst2.merge(lst4);
    ASSERT_TRUE(eq_list(&lst1, &lst2) && eq_list(&lst3, &lst4));
}

TEST(ListTest, merge_2) {
    s21::list<int> lst1 = s21::list<int>({2, 1});
    std::list<int> lst2 = std::list<int>({1, 2, 4, 7});
    s21::list<int> lst3 = s21::list<int>({7, 4});
    lst1.merge(lst3);
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, splice_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    s21::list<int> lst3 = s21::list<int>({3, 4});
    std::list<int> lst4 = std::list<int>({3, 4});
    lst1.splice(lst1.cbegin(), lst3);
    lst2.splice(lst2.cbegin(), lst4);
    ASSERT_TRUE(eq_list(&lst1, &lst2) && eq_list(&lst3, &lst4));
}

TEST(ListTest, reverse_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    lst1.reverse();
    lst2.reverse();
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, unique_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2, 2, 2, 3, 3, 3, 4});
    std::list<int> lst2 = std::list<int>({1, 2, 2, 2, 3, 3, 3, 4});
    lst1.unique();
    lst2.unique();
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, sort_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2, 7, 4, 5, 3});
    std::list<int> lst2 = std::list<int>({1, 2, 7, 4, 5, 3});
    lst1.sort();
    lst2.sort();
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, empty_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    ASSERT_TRUE(lst1.empty() == lst2.empty());
}

TEST(ListTest, empty_2) {
    s21::list<int> lst1 = s21::list<int>();
    std::list<int> lst2 = std::list<int>();
    ASSERT_TRUE(lst1.empty() == lst2.empty());
}

TEST(ListTest, size_1) {
    s21::list<int> lst1 = s21::list<int>();
    std::list<int> lst2 = std::list<int>();
    ASSERT_TRUE(lst1.size() == lst2.size());
}

TEST(ListTest, size_2) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    ASSERT_TRUE(lst1.size() == lst2.size());
}

TEST(ListTest, max_size_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    ASSERT_TRUE(lst1.max_size() > 0 && lst2.max_size() > 0);
}

TEST(ListTest, eq_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    s21::list<int> lst3 = lst1;
    std::list<int> lst4 = lst2;
    ASSERT_TRUE(eq_list(&lst1, &lst2) && eq_list(&lst3, &lst4));
}

TEST(ListTest, eq_2) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    s21::list<int> lst3 = std::move(lst1);
    std::list<int> lst4 = std::move(lst2);
    ASSERT_TRUE(eq_list(&lst1, &lst2) && eq_list(&lst3, &lst4));
}

TEST(ListTest, eq_3) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    s21::list<int> lst3;
    std::list<int> lst4;
    lst3 = s21::list<int>({1, 2});
    lst4 = std::list<int>({1, 2});
    ASSERT_TRUE(eq_list(&lst1, &lst2) && eq_list(&lst3, &lst4));
}

TEST(ListTest, begin_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    s21::list<int>::iterator iter1 = lst1.begin();
    std::list<int>::iterator iter2 = lst2.begin();
    ASSERT_TRUE(*iter1 == *iter2);
}

TEST(ListTest, end_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    s21::list<int>::iterator iter1 = --lst1.end();
    std::list<int>::iterator iter2 = --lst2.end();
    ASSERT_TRUE(*iter1 == *iter2);
}

TEST(ListTest, emplace_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    s21::list<int>::iterator result = lst1.emplace(++lst1.cbegin());
    ASSERT_TRUE(eq_list(&lst1, &lst2) && (*result) == 2);
}

TEST(ListTest, emplace_2) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 3, 2});
    s21::list<int>::iterator result = lst1.emplace(++lst1.cbegin(), 3);
    ASSERT_TRUE(eq_list(&lst1, &lst2) && (*result) == 3);
}

TEST(ListTest, emplace_3) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 3, 5, 2});
    s21::list<int>::iterator result = lst1.emplace(++lst1.cbegin(), 3, 5);
    ASSERT_TRUE(eq_list(&lst1, &lst2) && (*result) == 3);
}

TEST(ListTest, emplace_back_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    lst1.emplace_back();
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, emplace_back_2) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2, 3});
    lst1.emplace_back(3);
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, emplace_back_3) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2, 3, 5});
    lst1.emplace_back(3, 5);
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, emplace_front_1) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({1, 2});
    lst1.emplace_front();
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, emplace_front_2) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({3, 1, 2});
    lst1.emplace_front(3);
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

TEST(ListTest, emplace_front_3) {
    s21::list<int> lst1 = s21::list<int>({1, 2});
    std::list<int> lst2 = std::list<int>({3, 5, 1, 2});
    lst1.emplace_front(3, 5);
    ASSERT_TRUE(eq_list(&lst1, &lst2));
}

void test() {
    s21::list<int> lst1 = s21::list<int>();
    std::list<int> lst2 = std::list<int>();
    lst1.push_back(1);
    lst1.push_back(2);
    lst1.push_back(3);
    lst2.push_back(1);
    lst2.push_back(2);
    lst2.push_back(3);
    std::cout << "Size = " << lst1.size() << std::endl;
    std::cout << "Size = " << lst2.size() << std::endl;
    std::cout << (lst1.size() == lst2.size()) << std::endl;
    std::cout << eq_list_size(&lst1, &lst2) << std::endl;
    for (std::list<int>::iterator iter = lst2.begin(); iter != lst2.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
    for (s21::list<int>::iterator iter = lst1.begin(); iter != lst1.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    // test();
    // return 0;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
