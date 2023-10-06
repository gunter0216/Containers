#ifndef SRC_HEADERS_S21_MULTISET_H_
#define SRC_HEADERS_S21_MULTISET_H_

#include <climits>
#include <iostream>
#include <ostream>

#include "s21_tree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key>
class multiset : public Tree<Key> {
 public:
    typedef typename Tree<Key>::iterator iterator;
    typedef typename Tree<Key>::const_iterator const_iterator;
    typedef typename Tree<Key>::key_type key_type;
    typedef typename Tree<Key>::value_type value_type;
    typedef typename Tree<Key>::reference reference;
    typedef typename Tree<Key>::const_reference const_reference;
    typedef typename Tree<Key>::size_type size_type;

    multiset() : Tree<Key>() {}
    explicit multiset(std::initializer_list<value_type> const& items) : Tree<Key>(items) {}
    multiset(const multiset& ms) : Tree<Key>(ms) {}
    multiset(multiset&& ms) : Tree<Key>(std::move(ms)) {}
    multiset& operator=(multiset&& ms) {
        if (this->_head != ms._head) {
            swap(ms);
            ms.clear();
        }
        return *this;
    }
    iterator begin() {
        return Tree<Key>::begin();
    }
    iterator end() {
        return Tree<Key>::end();
    }
    const_iterator cbegin() const {
        return Tree<Key>::cbegin();
    }
    const_iterator cend() const {
        return Tree<Key>::cend();
    }
    void print() {
        Tree<Key>::print();
    }
    bool empty() const {
        return Tree<Key>::empty();
    }
    size_type size() {
        return Tree<Key>::size();
    }
    size_type max_size() {
        return Tree<Key>::max_size();
    }
    void clear() {
        Tree<Key>::clear();
    }
    iterator insert(const value_type& value) {
        return Tree<Key>::insert(value);
    }
    void erase(iterator pos) {
        Tree<Key>::erase(pos);
    }
    void swap(multiset& other) {
        Tree<Key>::swap(other);
    }
    void merge(multiset& other) {
        Tree<Key>::merge(other);
    }
    iterator upper_bound(const Key& key) {
        return Tree<Key>::upper_bound(key);
    }
    iterator lower_bound(const Key& key) {
        return Tree<Key>::lower_bound(key);
    }
    std::pair<iterator, iterator> equal_range(const Key& key) {
        return Tree<Key>::equal_range(key);
    }
    size_type count(const Key& key) {
        return Tree<Key>::count(key);
    }
    iterator find(const Key& key) {
        return Tree<Key>::find(key);
    }
    bool contains(const Key& key) {
        return Tree<Key>::contains(key);
    }
    template <typename... Args>
    vector<std::pair<iterator, bool>> emplace(Args&&... args) {
        return Tree<Key>::emplace(args...);
    }
};
}  // namespace s21

#endif  // SRC_HEADERS_S21_MULTISET_H_
