#include "headers/s21_tree.h"

template <typename Key>
typename s21::Tree<Key>::iterator
s21::Tree<Key>::begin() {
    iterator iter(_head);
    while (iter.iter->_left != nullptr)
        iter.iter = iter.iter->_left;
    return iter;
}

template <typename Key>
typename s21::Tree<Key>::iterator
s21::Tree<Key>::end() {
    iterator iter(_head);
    while (iter.iter->_right != nullptr)
        iter.iter = iter.iter->_right;
    return iter;
}

template <typename Key>
typename s21::Tree<Key>::iterator
s21::Tree<Key>::cbegin() const {
    iterator iter(_head);
    while (iter.iter->_left != nullptr)
        iter.iter = iter.iter->_left;
    return iter;
}

template <typename Key>
typename s21::Tree<Key>::iterator
s21::Tree<Key>::cend() const {
    iterator iter(_head);
    while (iter.iter->_right != nullptr)
        iter.iter = iter.iter->_right;
    return iter;
}

template <typename Key>
s21::Tree<Key>::Tree() {
    _head = new node();
}

template <typename Key>
s21::Tree<Key>::Tree(std::initializer_list<value_type> const& items) {
    _head = new node();
    for (auto item : items)
        insert(item);
}

template <typename Key>
s21::Tree<Key>::Tree(const Tree& ms) {
    _head = new node();
    if (ms._head != this->_head && !ms.empty()) {
        for (const_iterator iter = ms.cbegin(); iter != ms.cend(); ++iter)
            insert(*iter);
    }
}

template <typename Key>
s21::Tree<Key>::Tree(Tree&& ms) {
    if (ms._head != this->_head) {
        _head = ms._head;
        ms._head = new node();
    } else {
        _head = new node();
    }
}

template <typename Key>
s21::Tree<Key>::~Tree() {
    if (_head != nullptr)
        free_tree(_head);
}

template <typename Key>
template <typename... Args>
s21::vector<std::pair<typename s21::Tree<Key>::iterator, bool>>
s21::Tree<Key>::emplace(Args&&... args) {
    vector<std::pair<iterator, bool>> result;
    std::initializer_list<Key> lst = {args...};
    for (auto item : lst)
        result.push_back(std::pair<iterator, bool>(insert(item), true));
    return result;
}

template <typename Key>
bool s21::Tree<Key>::empty() const {
    return (_head->_left == nullptr && _head->_right == nullptr);
}

template <typename Key>
typename s21::Tree<Key>::size_type s21::Tree<Key>::size() {
    size_type size = 0;
    for (auto iter = begin(); iter != end(); ++iter, ++size) {
    }
    return size;
}

template <typename Key>
typename s21::Tree<Key>::size_type s21::Tree<Key>::max_size() {
    return LLONG_MAX / sizeof(node);
}

template <typename Key>
void s21::Tree<Key>::clear() {
    if (_head != nullptr)
        free_tree(_head);
    _head = new node();
}

template <typename Key>
typename s21::Tree<Key>::iterator
s21::Tree<Key>::insert(const s21::Tree<Key>::value_type& value) {
    iterator result;
    if (_head->_left == nullptr && _head->_right == nullptr) {
        _head->_right = new node();
        _head->_data = value;
        _head->_right->_parent = _head;
        iterator temp(_head);
        result = temp;
    } else {
        iterator iter(_head);
        bool stop = false;
        bool only_right = true;
        while (!stop) {
            if (value < (*iter)) {
                if (iter.iter->_left == nullptr) {
                    iter.iter->_left = new node(value);
                    iter.iter->_left->_parent = iter.iter;
                    stop = true;
                }
                iter.iter = iter.iter->_left;
                only_right = false;
            } else if (value > (*iter)) {
                if ((only_right == true && iter.iter->_right->_right == nullptr &&
                     iter.iter->_right->_left == nullptr)) {
                    node* newNode = new node(value);
                    newNode->_right = iter.iter->_right;
                    newNode->_parent = iter.iter;
                    iter.iter->_right->_parent = newNode;
                    iter.iter->_right = newNode;
                    stop = true;
                } else if (iter.iter->_right == nullptr) {
                    iter.iter->_right = new node(value);
                    iter.iter->_right->_parent = iter.iter;
                    stop = true;
                }
                iter.iter = iter.iter->_right;
            } else {
                node* newNode = new node(value,
                                         nullptr,
                                         iter.iter->_left,
                                         iter.iter);
                if (iter.iter->_left != nullptr)
                    iter.iter->_left->_parent = newNode;
                iter.iter->_left = newNode;
                stop = true;
            }
        }
        result = iter;
    }
    return result;
}

template <typename Key>
void s21::Tree<Key>::erase(iterator pos) {
    if (!(pos.iter->_parent == nullptr && pos.iter->_left == nullptr && pos.iter->_right == nullptr)) {
        if (pos.iter->_left == nullptr && pos.iter->_right == nullptr) {
            if (pos.iter->_parent != nullptr && pos.iter->_parent->_left == pos.iter)
                pos.iter->_parent->_left = nullptr;
            if (pos.iter->_parent != nullptr && pos.iter->_parent->_right == pos.iter)
                pos.iter->_parent->_right = nullptr;
            delete (pos.iter);
        } else if (pos.iter->_left == nullptr) {
            if (pos.iter->_parent != nullptr && pos.iter->_parent->_left == pos.iter)
                pos.iter->_parent->_left = pos.iter->_right;
            if (pos.iter->_parent != nullptr && pos.iter->_parent->_right == pos.iter)
                pos.iter->_parent->_right = pos.iter->_right;
            if (pos.iter->_parent != nullptr) {
                pos.iter->_right->_parent = pos.iter->_parent;
            } else {
                pos.iter->_right->_parent = nullptr;
                _head = pos.iter->_right;
            }
            delete (pos.iter);
        } else if (pos.iter->_right == nullptr) {
            if (pos.iter->_parent != nullptr && pos.iter->_parent->_left == pos.iter)
                pos.iter->_parent->_left = pos.iter->_left;
            if (pos.iter->_parent != nullptr && pos.iter->_parent->_right == pos.iter)
                pos.iter->_parent->_right = pos.iter->_left;
            if (pos.iter->_parent != nullptr) {
                pos.iter->_left->_parent = pos.iter->_parent;
            } else {
                pos.iter->_left->_parent = nullptr;
                _head = pos.iter->_left;
            }
            delete (pos.iter);
        } else {
            iterator iter = pos;
            if (pos.iter->_parent == nullptr && pos.iter->_right == end().iter) {
                iter.iter = iter.iter->_left;
                while (iter.iter->_right != nullptr)
                    iter.iter = iter.iter->_right;
            } else {
                if (iter.iter->_right != end().iter)
                    iter.iter = iter.iter->_right;
                while (iter.iter->_left != nullptr)
                    iter.iter = iter.iter->_left;
            }
            pos.iter->_data = iter.iter->_data;
            erase(iter);
        }
    }
}

template <typename Key>
void s21::Tree<Key>::swap(Tree& other) {
    if (other._head != _head) {
        std::swap(other._head, _head);
    }
}

template <typename Key>
void s21::Tree<Key>::merge(Tree& other) {
    if (_head != other._head) {
        for (iterator iter = other.begin(); iter != other.end(); ++iter)
            insert(iter.iter->_data);
        other.clear();
    }
}

template <typename Key>
typename s21::Tree<Key>::size_type s21::Tree<Key>::count(const Key& key) {
    iterator iter = find(key);
    size_type result = 0;
    if (iter.iter != end().iter) {
        ++result;
        while (iter.iter->_left != nullptr && iter.iter->_left->_data == key) {
            ++result;
            iter.iter = iter.iter->_left;
        }
    }
    return result;
}

template <typename Key>
bool s21::Tree<Key>::contains(const Key& key) {
    node* p = _head;
    bool result = true;
    bool stop = false;
    bool only_right = true;
    while (!stop) {
        if (key < p->_data) {
            if (p->_left == nullptr) {
                stop = true;
                result = false;
            }
            p = p->_left;
            only_right = false;
        } else if (key > p->_data) {
            if (p->_right == nullptr || (only_right == true && p->_right->_right == nullptr)) {
                stop = true;
                result = false;
            }
            p = p->_right;
        } else {
            stop = true;
        }
    }
    return result;
}

template <typename Key>
std::pair<typename s21::Tree<Key>::iterator, typename s21::Tree<Key>::iterator>
s21::Tree<Key>::equal_range(const Key& key) {
    std::pair<iterator,
              iterator>
        result(lower_bound(key), upper_bound(key));
    return result;
}

template <typename Key>
typename s21::Tree<Key>::iterator s21::Tree<Key>::lower_bound(const Key& key) {
    iterator result = find(key);
    if (result != end()) {
        while (result.iter->_left != nullptr && result.iter->_left->_data == key)
            result.iter = result.iter->_left;
    }
    return result;
}

template <typename Key>
typename s21::Tree<Key>::iterator s21::Tree<Key>::upper_bound(const Key& key) {
    iterator result = find(key);
    if (result.iter != end().iter)
        ++result;
    return result;
}

template <typename Key>
void s21::Tree<Key>::free_tree(node* p) {
    if (p->_left != nullptr)
        free_tree(p->_left);
    if (p->_right != nullptr)
        free_tree(p->_right);
    delete (p);
}

template <typename Key>
void s21::Tree<Key>::print() {
    std::cout << "### map size = " << size() << std::endl;
    for (auto iter = begin(); iter != end(); ++iter) {
        std::cout << "# " << (*iter) << std::endl;
    }
}

template <typename Key>
s21::TreeIterator<Key>& s21::TreeIterator<Key>::operator++() {
    if (iter->_right == nullptr) {
        while (iter->_parent->_right == iter)
            iter = iter->_parent;
        iter = iter->_parent;
    } else {
        iter = iter->_right;
        while (iter->_left != nullptr)
            iter = iter->_left;
    }
    return *this;
}

template <typename Key>
s21::TreeIterator<Key> s21::TreeIterator<Key>::operator++(int) {
    TreeIterator result = *this;
    if (iter->_right == nullptr) {
        while (iter->_parent->_right == iter)
            iter = iter->_parent;
        iter = iter->_parent;
    } else {
        iter = iter->_right;
        while (iter->_left != nullptr)
            iter = iter->_left;
    }
    return result;
}

template <typename Key>
s21::TreeIterator<Key>& s21::TreeIterator<Key>::operator--() {
    bool is_begin = false;
    if (iter->_left != nullptr) {
        iter = iter->_left;
        while (iter->_right != nullptr)
            iter = iter->_right;
    } else {
        if (iter->_parent == nullptr) {
            while (iter->_right != nullptr)
                iter = iter->_right;
        } else {
            while (iter->_parent->_left == iter && !is_begin) {
                iter = iter->_parent;
                if (iter->_parent == nullptr) {
                    is_begin = true;
                    while (iter->_right != nullptr)
                        iter = iter->_right;
                }
            }
            if (!is_begin)
                iter = iter->_parent;
        }
    }
    return *this;
}

template <typename Key>
s21::TreeIterator<Key> s21::TreeIterator<Key>::operator--(int) {
    TreeIterator result = *this;
    bool is_begin = false;
    if (iter->_left != nullptr) {
        iter = iter->_left;
        while (iter->_right != nullptr)
            iter = iter->_right;
    } else {
        if (iter->_parent == nullptr) {
            while (iter->_right != nullptr)
                iter = iter->_right;
        } else {
            while (iter->_parent->_left == iter && !is_begin) {
                iter = iter->_parent;
                if (iter->_parent == nullptr) {
                    is_begin = true;
                    while (iter->_right != nullptr)
                        iter = iter->_right;
                }
            }
            if (!is_begin)
                iter = iter->_parent;
        }
    }
    return result;
}

template <typename Key>
typename s21::Tree<Key>::iterator s21::Tree<Key>::find(const Key& key) {
    iterator result;
    node* p = _head;
    bool stop = false;
    bool only_right = true;
    while (!stop) {
        if (key < p->_data) {
            if (p->_left == nullptr) {
                stop = true;
                result = end();
            }
            p = p->_left;
            only_right = false;
        } else if (key > p->_data) {
            if (p->_right == nullptr || (only_right == true && p->_right->_right == nullptr)) {
                stop = true;
                result = end();
            }
            p = p->_right;
        } else {
            stop = true;
            result.iter = p;
        }
    }
    return result;
}

template <typename Key>
s21::Tree<Key>& s21::Tree<Key>::operator=(Tree&& m) {
    if (this->_head != m._head) {
        std::swap(_head, m._head);
    }
    return *this;
}
