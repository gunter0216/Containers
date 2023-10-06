#include "headers/s21_array.h"

template <typename T, size_t _size>
typename s21::array<T, _size>::iterator s21::array<T, _size>::begin() {
    return _array;
}

template <typename T, size_t _size>
typename s21::array<T, _size>::iterator s21::array<T, _size>::end() {
    return _array + _size;
}

template <typename T, size_t _size>
typename s21::array<T, _size>::const_iterator s21::array<T, _size>::cbegin() const {
    return _array;
}

template <typename T, size_t _size>
typename s21::array<T, _size>::const_iterator s21::array<T, _size>::cend() const {
    return _array + _size;
}

template <typename T, size_t _size>
s21::array<T, _size>::array() {}

template <typename T, size_t _size>
s21::array<T, _size>::array(std::initializer_list<T> const& items) {
    if (items.size() > _size) {
        throw std::out_of_range("list size is greater ther size of array");
    }
    int i = 0;
    for (auto item : items) {
        _array[i] = item;
        ++i;
    }
}

template <typename T, size_t _size>
s21::array<T, _size>::array(const array& other) {
    if (&other != this) {
        std::copy(other._array, other._array + _size, _array);
    }
}

template <typename T, size_t _size>
s21::array<T, _size>::array(array&& other) {
    if (&other != this) {
        std::move(other._array, other._array + _size, _array);
    }
}

template <typename T, size_t _size>
s21::array<T, _size>::~array() {
}

template <typename T, size_t _size>
s21::array<T, _size>& s21::array<T, _size>::operator=(s21::array<T, _size>&& other) {
    std::move(other._array, other._array_ + _size, _array);
    return *this;
}

template <typename T, size_t _size>
T& s21::array<T, _size>::at(size_type pos) {
    if (pos >= _size) throw std::out_of_range("out of bounds");
    return *(_array + pos);
}

template <typename T, size_t _size>
T& s21::array<T, _size>::operator[](size_type pos) {
    return *(_array + pos);
}

template <typename T, size_t _size>
constexpr typename s21::array<T, _size>::const_reference s21::array<T, _size>::front() const {
    return _array[0];
}

template <typename T, size_t _size>
constexpr typename s21::array<T, _size>::const_reference s21::array<T, _size>::back() const {
    return _array[_size - 1];
}

template <typename T, size_t _size>
typename s21::array<T, _size>::iterator s21::array<T, _size>::data() {
    return _array;
}

template <typename T, size_t _size>
bool s21::array<T, _size>::empty() {
    return 0 == size();
}
template <typename T, size_t _size>
typename s21::array<T, _size>::size_type s21::array<T, _size>::size() {
    return _size;
}

template <typename T, size_t _size>
typename s21::array<T, _size>::size_type s21::array<T, _size>::max_size() {
    return _size;
}

template <typename T, size_t _size>
void s21::array<T, _size>::swap(array& other) {
    std::swap(_array, other._array);
}

template <typename T, size_t _size>
void s21::array<T, _size>::fill(const T count) {
    for (size_t i = 0; i < _size; ++i) {
        _array[i] = count;
    }
}

// #endif  // SRC_S21_ARRAY_H_
