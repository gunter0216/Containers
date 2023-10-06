#ifndef SRC_HEADERS_S21_MAP_H_
#define SRC_HEADERS_S21_MAP_H_

#include <climits>
#include <iostream>
#include <ostream>

#include "s21_tree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class _pair {
 public:
    Key first;
    T second;

    _pair() {}
    _pair(const Key& _first, const T& _second) : first(_first), second(_second) {}
    explicit _pair(const std::pair<Key, T>& value) : first(value.first), second(value.second) {}

    _pair& operator=(const std::pair<Key, T>& p) {
        first = p.first;
        second = p.second;
        return *this;
    }
    _pair& operator=(std::pair<Key, T>&& p) {
        std::swap(first, p.first);
        std::swap(second, p.second);
        return *this;
    }

    friend bool operator!=(const _pair<Key, T>& x, const _pair<Key, T>& y) {
        return x.first != y.first;
    }

    friend bool operator==(const _pair<Key, T>& x, const _pair<Key, T>& y) {
        return x.first == y.first;
    }

    friend bool operator<(const _pair<Key, T>& x, const _pair<Key, T>& y) {
        return x.first < y.first;
    }

    friend bool operator>(const _pair<Key, T>& x, const _pair<Key, T>& y) {
        return x.first > y.first;
    }
};

template <typename Key, typename T>
class map : Tree<_pair<Key, T>> {
 public:
    typedef typename Tree<_pair<Key, T>>::iterator iterator;
    typedef typename Tree<_pair<Key, T>>::const_iterator const_iterator;
    typedef T mapped_type;
    typedef Key key_type;
    typedef _pair<Key, T> value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;

    map() : Tree<value_type>() {}
    explicit map(std::initializer_list<std::pair<Key, T>> const& items) : Tree<value_type>() {
        for (auto item : items)
            insert(value_type(item));
    }
    map(const map& m) : Tree<value_type>(m) {}
    map(map&& m) : Tree<value_type>(std::move(m)) {}
    map& operator=(map&& m) {
        if (this->_head != m._head) {
            swap(m);
            m.clear();
        }
        return *this;
    }
    iterator begin() {
        return Tree<value_type>::begin();
    }
    iterator end() {
        return Tree<value_type>::end();
    }
    const_iterator cbegin() const {
        return Tree<value_type>::cbegin();
    }
    const_iterator cend() const {
        return Tree<value_type>::cend();
    }
    void print() {
        Tree<value_type>::print();
    }
    iterator find(const Key& key) {
        return Tree<value_type>::find(value_type(key, 0));
    }
    T& at(const Key& key) {
        T* result;
        if (contains(key))
            result = &((*find(key)).second);
        return *result;
    }
    T& operator[](const Key& key) {
        T* result;
        if (contains(key)) {
            result = &((*find(key)).second);
        } else {
            result = &((*(insert(key, 0).first)).second);
        }
        return *result;
    }
    bool empty() const {
        return Tree<value_type>::empty();
    }
    size_type size() {
        return Tree<value_type>::size();
    }
    size_type max_size() {
        return Tree<value_type>::max_size();
    }
    void clear() {
        return Tree<value_type>::clear();
    }
    std::pair<iterator, bool> insert(const std::pair<Key, T>& value) {
        return insert(value_type(value));
    }
    std::pair<iterator, bool> insert(const Key& key, const T& obj) {
        return insert(value_type(key, obj));
    }
    std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
        std::pair<iterator, bool> result = insert(key, obj);
        if (result.second == false)
            (*(result.first)).second = obj;
        return result;
    }
    void erase(iterator pos) {
        Tree<value_type>::erase(pos);
    }
    void swap(map& other) {
        Tree<value_type>::swap(other);
    }
    void merge(map& other) {
        Tree<value_type>::merge(other);
    }
    bool contains(const Key& key) {
        return Tree<value_type>::contains(value_type(key, 0));
    }
    template <typename... Args>
    vector<std::pair<iterator, bool>> emplace(Args&&... args) {
        vector<std::pair<iterator, bool>> result;
        std::initializer_list<std::pair<Key, T>> lst = {args...};
        for (auto item : lst)
            result.push_back(insert(value_type(item)));
        return result;
    }

 private:
    std::pair<iterator, bool> insert(const value_type& value) {
        std::pair<iterator, bool> result;
        if (contains(value.first)) {
            result.first = find(value.first);
            result.second = false;
        } else {
            result.first = Tree<value_type>::insert(value);
            result.second = true;
        }
        return result;
    }
};
}  // namespace s21

#endif  // SRC_HEADERS_S21_MAP_H_
