#ifndef SRC_HEADERS_S21_LIST_H_
#define SRC_HEADERS_S21_LIST_H_

#include <climits>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <ostream>

namespace s21 {
template <typename T>
class list;
template <typename T>
class ListIterator;
template <typename T>
class listNode;
template <typename T>
class ListConstIterator;

template <typename T>
class listNode {
    friend class list<T>;
    friend class ListIterator<T>;
    friend class ListConstIterator<T>;

 private:
    T _data;

 public:
    listNode* _next;
    listNode* _prev;

    listNode() : _next(nullptr), _prev(nullptr) {}
    listNode(const T _data, listNode* _next, listNode* _prev) : _data(_data), _next(_next), _prev(_prev) {}
    listNode(const listNode& other) : _data(other._data), _next(other._next), _prev(other._prev) {}
};

template <typename T>
class ListIterator {
 private:
    typedef listNode<T> node;

 public:
    node* iter;

    ListIterator() : iter(nullptr) {}
    explicit ListIterator(node* iter) : iter(iter) {}
    T& operator*() const {
        T* result = nullptr;
        if (iter != nullptr)
            result = &iter->_data;
        if (result == nullptr) throw std::out_of_range("iterator is nullptr");
        return *result;
    }
    ListIterator& operator++() {
        if (iter != nullptr)
            iter = iter->_next;
        return *this;
    }
    ListIterator operator++(int) {
        ListIterator p = *this;
        if (iter != nullptr)
            iter = iter->_next;
        return p;
    }
    ListIterator& operator--() {
        if (iter != nullptr)
            iter = iter->_prev;
        return *this;
    }
    ListIterator operator--(int) {
        ListIterator p = *this;
        if (iter != nullptr)
            iter = iter->_prev;
        return p;
    }
    bool operator==(ListIterator const& iter) {
        return (this->iter == iter.iter);
    }
    bool operator==(node* const& _node) {
        return this->iter == _node;
    }
    bool operator!=(ListIterator const& iter) {
        return (this->iter != iter.iter);
    }
};

template <typename T>
class ListConstIterator {
 private:
    typedef listNode<T> node;

 public:
    const node* iter;

    ListConstIterator() : iter(nullptr) {}
    explicit ListConstIterator(const node* iter) : iter(iter) {}
    explicit ListConstIterator(const ListIterator<T>& iter) : iter(iter.iter) {}
    const T& operator*() const {
        const T* result = nullptr;
        if (iter != nullptr)
            result = &iter->_data;
        if (result == nullptr) throw std::out_of_range("iterator is nullptr");
        return *result;
    }
    ListConstIterator& operator++() {
        if (iter != nullptr)
            iter = iter->_next;
        return *this;
    }
    ListConstIterator operator++(int) {
        ListConstIterator p = *this;
        if (iter != nullptr)
            iter = iter->_next;
        return p;
    }
    ListConstIterator& operator--() {
        if (iter != nullptr)
            iter = iter->_prev;
        return *this;
    }
    ListConstIterator operator--(int) {
        ListConstIterator p = *this;
        if (iter != nullptr)
            iter = iter->_prev;
        return p;
    }
    bool operator==(ListConstIterator const& iter) {
        return (this->iter == iter.iter);
    }
    bool operator==(node* const& _node) {
        return this->iter == _node;
    }
    bool operator!=(ListConstIterator const& iter) {
        return (this->iter != iter.iter);
    }
};

template <typename T>
class list {
 private:
    size_t _size;
    typedef listNode<T> node;
    node* _head;

 public:
    typedef ListIterator<T> iterator;
    typedef ListConstIterator<T> const_iterator;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

    list();
    explicit list(size_type Count);
    explicit list(std::initializer_list<T> const& items);
    list(const list& other);
    list(list&& other);
    ~list();
    list& operator=(list&& other);

    // Возвращает ссылку на первый элемент в списке.
    const_reference front() const;
    // Возвращает ссылку на последний элемент списка.
    const_reference back() const;

    // Проверяет, пуст ли список.
    bool empty() const;
    // Возвращает количество элементов в списке.
    size_type size() const;
    size_type max_size() const;

    // Стирает все элементы списка.
    void clear();
    // Вставляет элемент или ряд элементов или диапазон элементов в список в указанной позиции.
    iterator insert(iterator Where, const T& Val);
    iterator insert(const_iterator Where, const T& Val);
    // Удаляет элемент в списке.
    void erase(iterator iter);
    // Добавляет элемент в конец списка.
    void push_back(T count);
    // Удаляет элемент в конце списка.
    void pop_back();
    // Добавляет элемент в начало списка.
    void push_front(const_reference count);
    // Удаляет элемент в начале списка.
    void pop_front();
    // Обменивается элементами двух списков.
    void swap(list& right);
    // Удаляет элементы из списка аргументов, вставляет их в целевой список.
    void merge(list& right);
    // Удаляет элементы из списка источников и вставляет их в список назначения.
    void splice(const_iterator Where, list& Source);
    // Изменяет порядок, в котором элементы встречаются в списке.
    void reverse();
    // Удаляет из списка смежные повторяющиеся элементы.
    void unique();
    // Упорядочивает элементы списка в порядке возрастания
    void sort();
    // inserts new elements into the container directly before pos
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args);
    // appends new elements to the end of the container
    template <typename... Args>
    void emplace_back(Args&&... args);
    // appends new elements to the top of the container
    template <typename... Args>
    void emplace_front(Args&&... args);
};
}  // namespace s21

#include "../s21_list.cpp"

#endif  // SRC_HEADERS_S21_LIST_H_
