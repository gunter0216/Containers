#include "headers/s21_vector.h"

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::begin() {
    return iterator(_vector);
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::end() {
    return iterator(_vector + _size);
}

template <typename T>
typename s21::vector<T>::const_iterator s21::vector<T>::cbegin() const {
    return const_iterator(_vector);
}

template <typename T>
typename s21::vector<T>::const_iterator s21::vector<T>::cend() const {
    return const_iterator(_vector + _size);
}

template <typename T>
s21::vector<T>::vector() : _size(0), _capacity(0), _vector(nullptr) {}

template <typename T>
s21::vector<T>::vector(size_type size) : _size(size), _capacity(size) {
    if (size <= 0) {
        throw std::out_of_range("Invalid size of vector");
    }
    _vector = new T[_size];
}

template <typename T>
s21::vector<T>::vector(std::initializer_list<T> const& items) {
    _size = 0;
    _capacity = 0;
    for (auto item : items) {
        push_back(item);
    }
}

template <typename T>
s21::vector<T>::vector(const vector& other) {
    if (&other != this) {
        _size = other._size;
        _capacity = other._capacity;
        _vector = new T[_capacity];
        for (size_t i = 0; i < _capacity; ++i) {
            _vector[i] = other._vector[i];
        }
    }
}

template <typename T>
s21::vector<T>::vector(vector<T>&& other) {
    if (other._vector && &other != this) {
        _size = 0;
        _capacity = 0;
        _vector = nullptr;
        swap(other);
    }
}

template <typename T>
s21::vector<T>::~vector() {
    if (capacity() > 0) {
        delete[] _vector;
    }
    // _vector = nullptr;
}

template <typename T>
s21::vector<T>& s21::vector<T>::operator=(s21::vector<T>&& other) {
    delete[] _vector;
    _size = other._size;
    _capacity = other._capacity;
    _vector = new T[_capacity];
    for (int i = 0; i < _capacity; ++i) {
        _vector[i] = other._vector[i];
    }
    return *this;
}

template <typename T>
T& s21::vector<T>::at(size_type pos) {
    if (pos >= _capacity) throw std::out_of_range("out of bounds");
    return *(_vector + pos);
}

template <typename T>
T& s21::vector<T>::operator[](size_type pos) {
    return *(_vector + pos);
}

template <typename T>
const T& s21::vector<T>::front() const {
    return _vector[0];
}

template <typename T>
const T& s21::vector<T>::back() const {
    return _vector[_size - 1];
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::data() {
    return begin();
}

template <typename T>
bool s21::vector<T>::empty() {
    return 0 == size();
}
template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::size() {
    return _size;
}

template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::max_size() {
    // return ~sizeof(0) / sizeof(T);
    return LLONG_MAX / sizeof(T);
}

template <typename T>
void s21::vector<T>::reserve(size_type size) {
    s21::vector<T> temp(*this);
    _capacity = size;
    delete[] _vector;
    _vector = new T[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _vector[i] = temp._vector[i];
    }
}

template <typename T>
void s21::vector<T>::shrink_to_fit() {
    s21::vector<T> temp(*this);
    _capacity = _size;
    delete[] _vector;
    _vector = new T[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _vector[i] = temp._vector[i];
    }
}

template <typename T>
typename s21::vector<T>::size_type s21::vector<T>::capacity() {
    return _capacity;
}

template <typename T>
void s21::vector<T>::clear() {
    _size = 0;
    delete[] _vector;
    _vector = nullptr;
}

template <typename T>
void s21::vector<T>::erase(iterator pos) {
    for (iterator i = pos; i != end(); ++i) {
        *i = *(++pos);
    }
    --_size;
}

template <typename T>
typename s21::vector<T>::iterator s21::vector<T>::insert(iterator pos, const_reference value) {
    push_back(value);
    iterator temp;
    for (iterator i = end(); i != pos; --i) {
        temp = i;
        *i = *(--temp);
    }
    *pos = value;
    return pos;
}

template <typename T>
void s21::vector<T>::push_back(T count) {
    if (capacity() == 0) {
        _size = 1;
        _capacity = _size;
        _vector = new T[_capacity];
        _vector[0] = count;
    } else if (size() == capacity() && max_size() - size() > 0) {
        s21::vector<T> temp(*this);
        _capacity = capacity() * 2;
        delete[] _vector;
        _vector = new T[_capacity];
        size_t i = 0;
        for (; i < _size; ++i) {
            _vector[i] = temp._vector[i];
        }
        _vector[_size] = count;
        ++_size;
    } else if (max_size() - size() > 0) {
        _vector[_size] = count;
        ++_size;
    } else {
        throw std::out_of_range("max size is reached");
    }
}

template <typename T>
void s21::vector<T>::pop_back() {
    --_size;
}

template <typename T>
void s21::vector<T>::swap(vector& other) {
    std::swap(_capacity, other._capacity);
    std::swap(_size, other._size);
    std::swap(_vector, other._vector);
}

template <typename T>
template <typename... Args>
typename s21::vector<T>::iterator s21::vector<T>::emplace(const_iterator pos, Args&&... args) {
    std::initializer_list<value_type> listForInsert = {args...};
    s21::vector<T>::iterator position = begin();
    s21::vector<T>::iterator temp = begin();
    for (; &(*temp) != &(*pos); ++temp, ++position) {
    }
    int i = 0;
    for (auto itemElement = listForInsert.begin(); itemElement != listForInsert.end(); ++itemElement) {
        position += i;
        insert(position, *itemElement);
        i++;
    }
    return temp;
}

template <typename T>
template <typename... Args>
void s21::vector<T>::emplace_back(Args&&... args) {
    std::initializer_list<value_type> listForInsert = {args...};
    for (auto itemElement = listForInsert.begin(); itemElement != listForInsert.end(); ++itemElement) {
        push_back(*itemElement);
    }
}
