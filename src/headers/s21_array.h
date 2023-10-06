#ifndef SRC_HEADERS_S21_ARRAY_H_
#define SRC_HEADERS_S21_ARRAY_H_

#include <limits.h>

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T, size_t _size>
class array {
 public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

    array();
    explicit array(std::initializer_list<T> const& items);
    array(const array& other);
    array(array&& other);
    ~array();
    array<T, _size>& operator=(array&& other);

    T& at(size_type pos);
    T& operator[](size_type pos);
    constexpr const_reference front() const;
    constexpr const_reference back() const;
    iterator data();

    bool empty();
    size_type size();
    size_type max_size();

    void swap(array& other);
    void fill(const T count);

 private:
    T _array[_size];
};

}  // namespace s21

#include "../s21_array.cpp"

#endif  // SRC_HEADERS_S21_ARRAY_H_
