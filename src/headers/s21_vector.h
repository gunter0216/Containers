#ifndef SRC_HEADERS_S21_VECTOR_H_
#define SRC_HEADERS_S21_VECTOR_H_

#include <limits.h>

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

#define s21_MAX_SIZE 9223372036854775807

namespace s21 {
template <typename T>
class vector;
template <typename T>
class vectorIterator;
template <typename T>
class vectorConstIterator;

template <typename T>
class vectorIterator {
 private:
    T* _current;

 public:
    vectorIterator() {}
    explicit vectorIterator(T* first) : _current(first) {}

    T& operator*() { return *_current; }
    vectorIterator& operator++() {
        ++_current;
        return *this;
    }
    vectorIterator operator++(int) {
        vectorIterator temp = *this;
        ++_current;
        return temp;
    }
    vectorIterator& operator--() {
        --_current;
        return *this;
    }
    vectorIterator operator--(int) {
        vectorIterator temp = *this;
        --_current;
        return temp;
    }
    vectorIterator& operator+=(int num) {
        for (int i = 0; i < num; ++i) {
            ++_current;
        }
        return *this;
    }
    bool operator==(const vectorIterator& other) {
        return _current == other._current;
    }
    bool operator!=(const vectorIterator& other) {
        return _current != other._current;
    }
};

template <typename T>
class vectorConstIterator {
 private:
    const T* _current;

 public:
    vectorConstIterator() {}
    explicit vectorConstIterator(T* first) : _current(first) {}

    const T& operator*() const { return *_current; }

    vectorConstIterator& operator++() {
        ++_current;
        return *this;
    }

    vectorConstIterator operator++(int) {
        vectorConstIterator temp = *this;
        ++_current;
        return temp;
    }

    vectorConstIterator& operator--() {
        --_current;
        return *this;
    }

    vectorConstIterator operator--(int) {
        vectorConstIterator temp = *this;
        --_current;
        return temp;
    }
    vectorConstIterator& operator+=(int num) {
        for (int i = 0; i < num; ++i) {
            ++_current;
        }
        return *this;
    }

    bool operator==(const vectorConstIterator& other) {
        return _current == other._current;
    }

    bool operator!=(const vectorConstIterator& other) {
        return _current != other._current;
    }
};

template <typename T>
class vector {
 public:
    typedef vectorIterator<T> iterator;
    typedef vectorConstIterator<T> const_iterator;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

    vector();
    explicit vector(size_type size);
    explicit vector(std::initializer_list<T> const& items);
    vector(const vector& other);
    vector(vector<T>&& other);
    ~vector();
    vector<T>& operator=(vector&& other);

    T& at(size_type pos);
    T& operator[](size_type pos);
    const T& front() const;
    const T& back() const;
    iterator data();

    bool empty();
    size_type size();
    size_type max_size();
    void reserve(size_type size);
    size_type capacity();
    void shrink_to_fit();

    void clear();
    void erase(iterator pos);
    iterator insert(iterator pos, const_reference value);
    void push_back(T count);
    void pop_back();
    void swap(vector& other);

    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args);

    template <typename... Args>
    void emplace_back(Args&&... args);

 private:
    T* _vector;
    size_type _size;
    size_type _capacity;
};

}  // namespace s21

#include "../s21_vector.cpp"

#endif  // SRC_HEADERS_S21_VECTOR_H_
