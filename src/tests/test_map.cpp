#include <gtest/gtest.h>

#include <iostream>
#include <map>

#include "../headers/s21_map.h"
#include "../headers/s21_vector.h"

template <typename Key, typename T>
bool eq_map(s21::map<Key, T> *map1, std::map<Key, T> *map2) {
    bool result = true;
    if (map1->size() == map2->size()) {
        if (map1->size() != 0) {
            typename s21::map<Key, T>::iterator iter1 = map1->begin();
            typename std::map<Key, T>::iterator iter2 = map2->begin();
            for (; iter1 != map1->end(); ++iter1, ++iter2) {
                if (!((*iter1).first == (*iter2).first &&
                      (*iter1).second == (*iter2).second)) {
                    result = false;
                }
            }
        }
    } else {
        result = false;
    }
    return result;
}

template <typename Key, typename T>
bool eq_map_size(s21::map<Key, T> map1, std::map<Key, T> map2) {
    return map1.size() == map2.size();
}

TEST(MapTest, constructor_1) {
    s21::map<int, int> map1 = s21::map<int, int>();
    std::map<int, int> map2 = std::map<int, int>();
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, constructor_2) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, constructor_3) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    s21::map<int, int> map2 = s21::map<int, int>(map1);
    std::map<int, int> map3 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map4 = std::map<int, int>(map3);
    ASSERT_TRUE(eq_map(&map1, &map3) && eq_map(&map2, &map4));
}

TEST(MapTest, constructor_4) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    s21::map<int, int> map2 = s21::map<int, int>(std::move(map1));
    std::map<int, int> map3 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map4 = std::map<int, int>(std::move(map3));
    ASSERT_TRUE(eq_map(&map1, &map3) && eq_map(&map2, &map4));
}

TEST(MapTest, eq_1) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    s21::map<int, int> map2;
    std::map<int, int> map3 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map4;
    map2 = s21::map<int, int>({std::pair<int, int>(1, 1)});
    map4 = std::map<int, int>({std::pair<int, int>(1, 1)});
    ASSERT_TRUE(eq_map(&map1, &map3) && eq_map(&map2, &map4));
}

TEST(MapTest, at_1) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    ASSERT_TRUE(map1.at(1) == map2.at(1) &&
                map1.at(2) == map2.at(2) &&
                map1.at(3) == map2.at(3));
}

TEST(MapTest, at_2) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    ASSERT_TRUE(map1.at(1) == map2.at(1) &&
                map1.at(2) == map2.at(2) &&
                map1.at(3) == map2.at(3));
}

TEST(MapTest, operator_square_brakets_1) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    ASSERT_TRUE(map1[1] == map2[1] &&
                map1[2] == map2[2] &&
                map1[3] == map2[3]);
}

TEST(MapTest, operator_square_brakets_2) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(3, 3)});
    ASSERT_TRUE(map1[1] == map2[1] &&
                map1[2] == map2[2] &&
                map1[3] == map2[3]);
}

TEST(MapTest, empty_1) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    ASSERT_TRUE(map1.empty() == map2.empty());
}

TEST(MapTest, empty_2) {
    s21::map<int, int> map1 = s21::map<int, int>();
    std::map<int, int> map2 = std::map<int, int>();
    ASSERT_TRUE(map1.empty() == map2.empty());
}

TEST(MapTest, size_1) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    ASSERT_TRUE(map1.size() == map2.size());
}

TEST(MapTest, size_2) {
    s21::map<int, int> map1 = s21::map<int, int>();
    std::map<int, int> map2 = std::map<int, int>();
    ASSERT_TRUE(map1.size() == map2.size());
}

TEST(MapTest, max_size_1) {
    s21::map<int, int> map1 = s21::map<int, int>();
    std::map<int, int> map2 = std::map<int, int>();
    ASSERT_TRUE(map1.max_size() > 0 && map2.max_size() > 0);
}

TEST(MapTest, clear_1) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, clear_2) {
    s21::map<int, int> map1 = s21::map<int, int>();
    std::map<int, int> map2 = std::map<int, int>();
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, insert_1) {
    s21::map<int, int> map1 = s21::map<int, int>();
    std::map<int, int> map2 = std::map<int, int>();
    map1.insert(std::pair<int, int>(1, 1));
    map2.insert(std::pair<int, int>(1, 1));
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, insert_2) {
    s21::map<int, int> map1 = s21::map<int, int>();
    std::map<int, int> map2 = std::map<int, int>();
    map1.insert(std::pair<int, int>(1, 1));
    map1.insert(std::pair<int, int>(2, 2));
    map2.insert(std::pair<int, int>(1, 1));
    map2.insert(std::pair<int, int>(2, 2));
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, insert_3) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1)});
    map1.insert(std::pair<int, int>(1, 1));
    map1.insert(std::pair<int, int>(2, 2));
    map2.insert(std::pair<int, int>(1, 1));
    map2.insert(std::pair<int, int>(2, 2));
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, insert_4) {
    s21::map<int, int> map1 = s21::map<int, int>();
    std::map<int, int> map2 = std::map<int, int>();
    map1.insert(1, 1);
    map1.insert(2, 2);
    map2.insert(std::pair<int, int>(1, 1));
    map2.insert(std::pair<int, int>(2, 2));
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, insert_or_assign_1) {
    s21::map<int, int> map1 = s21::map<int, int>();
    std::map<int, int> map2 = std::map<int, int>();
    map1.insert(1, 1);
    map1.insert_or_assign(1, 33);
    map2.insert(std::pair<int, int>(1, 33));
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, insert_or_assign_2) {
    s21::map<int, int> map1 = s21::map<int, int>();
    std::map<int, int> map2 = std::map<int, int>();
    map1.insert(1, 1);
    map1.insert_or_assign(2, 2);
    map2.insert(std::pair<int, int>(1, 1));
    map2.insert(std::pair<int, int>(2, 2));
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, swap_1) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    s21::map<int, int> map2 = s21::map<int, int>();
    std::map<int, int> map3 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map4 = std::map<int, int>();
    map1.swap(map2);
    map3.swap(map4);
    ASSERT_TRUE(eq_map(&map1, &map3) && eq_map(&map2, &map4));
}

TEST(MapTest, merge_1) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1)});
    s21::map<int, int> map2 = s21::map<int, int>({std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map3 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    map1.merge(map2);
    ASSERT_TRUE(eq_map(&map1, &map3));
}

TEST(MapTest, contains_1) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    ASSERT_TRUE(map1.contains(1) == true && map1.contains(33) == false);
}

TEST(MapTest, contains_2) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(2, 1),
                                                  std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(3, 3)});
    ASSERT_TRUE(map1.contains(1) == true && map1.contains(33) == false &&
                map1.contains(0) == false);
}

TEST(MapTest, iterator_1) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(3, 3),
                                                  std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2)});
    s21::map<int, int>::iterator iter = map1.begin();
    for (int i = 0; i < 3; ++i)
        iter++;
    for (int i = 0; i < 3; ++i)
        iter--;
    for (int i = 0; i < 3; ++i)
        ++iter;
    for (int i = 0; i < 3; ++i)
        --iter;
    ASSERT_EQ((*iter).first, 1);
}

TEST(MapTest, erase_1) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2)});
    map1.erase(--map1.end());
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, erase_2) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    map1.erase(map1.begin());
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, erase_3) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(2, 2)});
    map1.erase(map1.begin());
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, erase_4) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1)});
    std::map<int, int> map2 = std::map<int, int>();
    map1.erase(map1.begin());
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, erase_5) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(5, 5),
                                                  std::pair<int, int>(3, 3)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(5, 5)});
    map1.erase(map1.begin());
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, erase_6) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(5, 5),
                                                  std::pair<int, int>(3, 3),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(4, 4)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(5, 5),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    map1.erase(-- --map1.end());
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, erase_7) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(5, 5),
                                                  std::pair<int, int>(3, 3),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(4, 4)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(5, 5),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(4, 4)});
    map1.erase(---- --map1.end());
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, erase_8) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(5, 5),
                                                  std::pair<int, int>(3, 3),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(4, 4)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(5, 5),
                                                  std::pair<int, int>(4, 4),
                                                  std::pair<int, int>(3, 3)});
    map1.erase(map1.begin());
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, erase_9) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(5, 5),
                                                  std::pair<int, int>(3, 3),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(4, 4)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(4, 4),
                                                  std::pair<int, int>(3, 3)});
    map1.erase(--map1.end());
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, erase_10) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(3, 3),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(4, 4)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(3, 3),
                                                  std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(4, 4)});
    map1.erase(++map1.begin());
    ASSERT_TRUE(eq_map(&map1, &map2));
}

TEST(MapTest, emplace_1) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2)});
    s21::vector<std::pair<typename s21::map<int, int>::iterator, bool>> v1(
        map1.emplace());
    ASSERT_TRUE(eq_map(&map1, &map2) && v1.empty());
}

TEST(MapTest, emplace_2) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3)});
    s21::vector<std::pair<typename s21::map<int, int>::iterator, bool>> v1(
        map1.emplace(std::pair<int, int>(3, 3)));
    ASSERT_TRUE(eq_map(&map1, &map2) && (*v1.at(0).first).first == 3 && v1.at(0).second == true);
}

TEST(MapTest, emplace_3) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2)});
    s21::vector<std::pair<typename s21::map<int, int>::iterator, bool>> v1(
        map1.emplace(std::pair<int, int>(1, 1)));
    ASSERT_TRUE(eq_map(&map1, &map2) && (*v1.at(0).first).first == 1 && v1.at(0).second == false);
}

TEST(MapTest, emplace_4) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(3, 3),
                                                  std::pair<int, int>(4, 4)});
    s21::vector<std::pair<typename s21::map<int, int>::iterator, bool>> v1(
        map1.emplace(std::pair<int, int>(3, 3), std::pair<int, int>(4, 4)));
    ASSERT_TRUE(eq_map(&map1, &map2) && (*v1.at(0).first).first == 3 && v1.at(0).second == true &&
                (*v1.at(1).first).first == 4 && v1.at(1).second == true);
}

TEST(MapTest, emplace_5) {
    s21::map<int, int> map1 = s21::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2)});
    std::map<int, int> map2 = std::map<int, int>({std::pair<int, int>(1, 1),
                                                  std::pair<int, int>(2, 2),
                                                  std::pair<int, int>(4, 4)});
    s21::vector<std::pair<typename s21::map<int, int>::iterator, bool>> v1(
        map1.emplace(std::pair<int, int>(1, 1), std::pair<int, int>(4, 4)));
    ASSERT_TRUE(eq_map(&map1, &map2) && (*v1.at(0).first).first == 1 && v1.at(0).second == false &&
                (*v1.at(1).first).first == 4 && v1.at(1).second == true);
}

// void test() {
//     std::pair<int, int> x1(0, 4);
//     std::pair<int, int> x2(1, 3);
//     std::pair<int, int> x3(1, 2);
//     std::pair<int, int> x4(1, 2);
//     std::cout << (x1 < x2) << std::endl;
// }

int main(int argc, char **argv) {
    // test();
    // return 0;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
