#ifndef SRC_HEADERS_S21_STACK_H_
#define SRC_HEADERS_S21_STACK_H_

#include "s21_list.h"

namespace s21 {
template <typename T, class Container = s21::list<T>>
class stack {
 private:
    Container c;

 public:
    typedef typename Container::value_type value_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;
    typedef typename Container::size_type size_type;

    stack() : c() {}
    explicit stack(std::initializer_list<T> const& items) : c(items) {}
    explicit stack(const Container& other) : c(other) {}
    explicit stack(Container&& other) : c(std::move(other)) {}

    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    const_reference top() const { return c.back(); }
    void push(const T& value) { c.push_back(value); }
    void pop() { c.pop_back(); }
    void swap(stack& other) { c.swap(other.c); }
    template <typename... Args>
    void emplace_front(Args&&... args) { c.emplace_front(args...); }
};
}  // namespace s21

#endif  // SRC_HEADERS_S21_STACK_H_
