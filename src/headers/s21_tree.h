#ifndef SRC_HEADERS_S21_TREE_H_
#define SRC_HEADERS_S21_TREE_H_

#include <climits>
#include <iostream>
#include <ostream>

#include "s21_vector.h"

namespace s21 {
template <typename T>
class Tree;
template <typename T>
class TreeNode;
template <typename T>
class TreeIterator;
template <typename T>
class TreeConstIterator;

template <typename Key>
class TreeNode {
    friend class Tree<Key>;
    friend class TreeIterator<Key>;

 private:
    Key _data;

 public:
    TreeNode* _right;
    TreeNode* _left;
    TreeNode* _parent;

    TreeNode() : _right(nullptr), _left(nullptr), _parent(nullptr) {}
    explicit TreeNode(const Key data) : _data(data), _right(nullptr), _left(nullptr), _parent(nullptr) {}
    TreeNode(const Key data, TreeNode* right, TreeNode* left) : _data(data),
                                                                _right(right),
                                                                _left(left),
                                                                _parent(nullptr) {}
    TreeNode(const Key data,
             TreeNode* right,
             TreeNode* left,
             TreeNode* parent) : _data(data),
                                 _right(right),
                                 _left(left),
                                 _parent(parent) {}
};

template <typename Key>
class TreeIterator {
 private:
    typedef TreeNode<Key> node;

 public:
    node* iter;

    TreeIterator() : iter(nullptr) {}
    explicit TreeIterator(node* iter) : iter(iter) {}
    Key& operator*() const {
        if (iter == nullptr)
            throw std::out_of_range("Zero iterator.");
        return iter->_data;
    }
    TreeIterator& operator++();
    TreeIterator& operator--();
    TreeIterator operator++(int);
    TreeIterator operator--(int);
    bool operator==(TreeIterator const& iter) {
        return this->iter == iter.iter;
    }
    bool operator!=(TreeIterator const& iter) {
        return this->iter != iter.iter;
    }
};

template <typename Key>
class Tree {
 protected:
    typedef TreeIterator<Key> iterator;
    typedef TreeIterator<Key> const_iterator;
    typedef Key key_type;
    typedef Key value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef TreeNode<Key> node;
    node* _head;

    Tree();
    explicit Tree(std::initializer_list<value_type> const& items);
    Tree(const Tree& s);
    Tree(Tree&& s);
    ~Tree();

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

    void free_tree(node* p);
    void print();

    Tree& operator=(Tree&& m);

    bool empty() const;
    size_type size();
    size_type max_size();

    void clear();
    iterator insert(const value_type& value);
    void erase(iterator pos);
    void swap(Tree& other);
    void merge(Tree& other);
    iterator upper_bound(const Key& key);
    iterator lower_bound(const Key& key);
    std::pair<iterator, iterator> equal_range(const Key& key);
    size_type count(const Key& key);

    iterator find(const Key& key);
    bool contains(const Key& key);
    template <typename... Args>
    vector<std::pair<iterator, bool>> emplace(Args&&... args);
};
}  // namespace s21

#include "../s21_tree.cpp"

#endif  // SRC_HEADERS_S21_TREE_H_
