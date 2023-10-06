#include "headers/s21_list.h"

template <typename T>
s21::list<T>::list() : _size(0) {
    _head = new node;
    _head->_next = _head;
    _head->_prev = _head;
}

template <typename T>
s21::list<T>::list(size_type Count) : _size(0) {
    _head = new node;
    _head->_next = _head;
    _head->_prev = _head;
    for (size_type i = 0; i < Count; i++)
        push_back(0);
}

template <typename T>
s21::list<T>::list(std::initializer_list<T> const& items) : _size(0) {
    _head = new node;
    _head->_next = _head;
    _head->_prev = _head;
    for (auto item : items)
        push_back(item);
}

template <typename T>
s21::list<T>::list(const list& other) : _size(0) {
    _head = new node;
    _head->_next = _head;
    _head->_prev = _head;
    if (&other != this && !other.empty()) {
        for (const_iterator iter = other.cbegin(); iter != other.cend(); ++iter)
            push_back(*iter);
    }
}

template <typename T>
s21::list<T>::list(list&& other) : _size(0) {
    if (&other != this) {
        _head = other._head;
        other._head = new node;
        other._head->_next = other._head;
        other._head->_prev = other._head;
        _size = other._size;
        other._size = 0;
    } else {
        _head = new node;
        _head->_next = _head;
        _head->_prev = _head;
    }
}

template <typename T>
s21::list<T>::~list() {
    clear();
    delete (_head);
}

template <typename T>
void s21::list<T>::clear() {
    if (!empty()) {
        node* p = _head->_next;
        while (p->_next != _head) {
            p = p->_next;
        }
        while (p != _head) {
            p = p->_prev;
            delete (p->_next);
        }
        _head->_next = _head;
        _head->_prev = _head;
    }
    _size = 0;
}

template <typename T>
s21::list<T>& s21::list<T>::operator=(list&& other) {
    if (&other != this) {
        if (_head != nullptr) {
            clear();
            delete _head;
        }
        _head = other._head;
        _size = other._size;
        other._head = new node;
        other._head->_next = other._head;
        other._head->_prev = other._head;
        other._size = 0;
    }
    return *this;
}

template <typename T>
template <typename... Args>
typename s21::list<T>::iterator
s21::list<T>::emplace(const_iterator pos, Args&&... args) {
    std::initializer_list<T> lst = {args...};
    iterator result = begin();
    for (; result.iter != pos.iter; ++result) {
    }
    iterator pos_not_const = result;
    bool temp = true;
    for (auto item : lst) {
        if (temp) {
            result = insert(pos_not_const, item);
            temp = false;
        } else {
            insert(pos_not_const, item);
        }
    }
    return result;
}

template <typename T>
template <typename... Args>
void s21::list<T>::emplace_back(Args&&... args) {
    emplace(cend(), args...);
}

template <typename T>
template <typename... Args>
void s21::list<T>::emplace_front(Args&&... args) {
    emplace(cbegin(), args...);
}

template <typename T>
void s21::list<T>::pop_front() {
    if (!empty())
        erase(iterator(_head));
}

template <typename T>
void s21::list<T>::pop_back() {
    if (!empty())
        erase(--end());
}

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::front() const {
    return _head->_data;
}

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::back() const {
    return _head->_prev->_prev->_data;
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::begin() {
    return iterator(_head);
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::end() {
    return iterator(_head->_prev);
}

template <typename T>
typename s21::list<T>::const_iterator s21::list<T>::cbegin() const {
    return const_iterator(this->_head);
}

template <typename T>
typename s21::list<T>::const_iterator s21::list<T>::cend() const {
    return const_iterator(this->_head->_prev);
}

template <typename T>
void s21::list<T>::push_back(T count) {
    if (size() != max_size()) {
        node* temp = new node(count, nullptr, nullptr);
        if (empty()) {
            _head->_data = count;
            _head->_next = temp;
            _head->_prev = temp;
            temp->_data = 0;
            temp->_next = _head;
            temp->_prev = _head;
        } else {
            node* p = _head;
            while (p->_next->_next != _head) {
                p = p->_next;
            }
            temp->_prev = p;
            temp->_next = p->_next;
            p->_next->_prev = temp;
            p->_next = temp;
        }
        ++_size;
    }
}

template <typename T>
void s21::list<T>::push_front(const_reference count) {
    if (size() != max_size()) {
        node* temp = new node(_head->_data, _head->_next, _head);
        _head->_data = count;
        _head->_next->_prev = temp;
        _head->_next = temp;
        ++_size;
    }
}

template <typename T>
bool s21::list<T>::empty() const {
    return size() == 0;
}

template <typename T>
typename s21::list<T>::size_type s21::list<T>::size() const {
    return _size;
}

template <typename T>
typename s21::list<T>::size_type s21::list<T>::max_size() const {
    return LLONG_MAX / sizeof(node);
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::insert(iterator Where, const T& Val) {
    node* temp = new node(Val, Where.iter, Where.iter->_prev);
    if (size() != max_size()) {
        if (begin() == Where)
            _head = temp;
        Where.iter->_prev->_next = temp;
        Where.iter->_prev = temp;
        ++_size;
    }
    return iterator(temp);
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::insert(const_iterator Where, const T& Val) {
    node* temp = new node(Val, Where.iter, Where.iter->_prev);
    if (size() != max_size()) {
        if (cbegin() == Where)
            _head = temp;
        Where.iter->_prev->_next = temp;
        Where.iter->_prev = temp;
        ++_size;
    }
    return iterator(temp);
}

template <typename T>
void s21::list<T>::splice(const_iterator Where, list& Source) {
    if (&Source != this && Where.iter != nullptr) {
        iterator SourceBegin = Source.begin();
        iterator SourceEnd = --Source.end();
        iterator Where_not_const = begin();
        for (; Where_not_const.iter != Where.iter; ++Where_not_const) {
        }

        if (cbegin() == Where)
            _head = SourceBegin.iter;

        Source._head = Source.end().iter;
        Source._head->_next = Source._head;
        Source._head->_prev = Source._head;

        SourceEnd.iter->_next = Where_not_const.iter->_next->_prev;
        SourceBegin.iter->_prev = Where_not_const.iter->_prev;
        Where_not_const.iter->_prev->_next = SourceBegin.iter;
        Where_not_const.iter->_prev = SourceEnd.iter;

        _size += Source._size;
        Source._size = 0;
    }
}

template <typename T>
void s21::list<T>::merge(list& right) {
    if (&right != this) {
        iterator iter = --end();
        iterator rightBegin = right.begin();
        iterator rightEnd = right.end();

        right._head = iter.iter->_next;
        right._head->_next = right._head;
        right._head->_prev = right._head;

        iter.iter->_next = rightBegin.iter;
        rightBegin.iter->_prev = iter.iter;
        rightEnd.iter->_next = _head;
        _head->_prev = rightEnd.iter;

        _size += right._size;
        right._size = 0;
        sort();
    }
}

template <typename T>
void s21::list<T>::swap(list& right) {
    std::swap(_head, right._head);
    std::swap(_size, right._size);
}

template <typename T>
void s21::list<T>::sort() {
    iterator iter = begin();
    size_type temp_size = size();
    for (size_t i = 0; i < temp_size - 1; ++i) {
        for (size_t j = 0; j < temp_size - i - 1; ++j, ++iter) {
            if (iter.iter->_data > iter.iter->_next->_data)
                std::swap(iter.iter->_data, iter.iter->_next->_data);
        }
        iter = begin();
    }
}

template <typename T>
void s21::list<T>::reverse() {
    if (size() > 1) {
        iterator p = --end();
        iterator nd = ++end();
        iterator iter = begin();
        node* n;
        do {
            n = iter.iter->_next;
            iter.iter->_next = iter.iter->_prev;
            iter.iter->_prev = n;
            --iter;
        } while (iter != nd);
        _head = p.iter;
    }
}

template <typename T>
void s21::list<T>::unique() {
    for (iterator iter = begin(); iter != end();) {
        if (iter.iter->_data == iter.iter->_next->_data) {
            erase(iterator(iter.iter->_next));
        } else {
            ++iter;
        }
    }
}

template <typename T>
void s21::list<T>::erase(iterator iter) {
    if (iter.iter != nullptr) {
        if (iter == _head)
            _head = iter.iter->_next;
        iter.iter->_prev->_next = iter.iter->_next;
        iter.iter->_next->_prev = iter.iter->_prev;
        delete (iter.iter);
        --_size;
    }
}
