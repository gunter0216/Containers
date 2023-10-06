#ifndef SRC_HEADERS_S21_QUEUE_H_
#define SRC_HEADERS_S21_QUEUE_H_

#include "s21_list.h"

namespace s21 {
template <typename T, class Container = s21::list<T>>
class queue {
 private:
    Container c;

 public:
    typedef typename Container::value_type value_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;
    typedef typename Container::size_type size_type;

    queue() : c() {}
    explicit queue(std::initializer_list<T> const& items) : c(items) {}
    explicit queue(const Container& other) : c(other) {}
    explicit queue(Container&& other) : c(std::move(other)) {}

    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    const_reference front() const { return c.front(); }
    const_reference back() const { return c.back(); }
    void push(const T& count) { c.push_back(count); }
    void pop() { c.pop_front(); }
    void swap(queue& other) { c.swap(other.c); }
    template <typename... Args>
    void emplace_back(Args&&... args) { c.emplace_back(args...); }
};
}  // namespace s21

#endif  // SRC_HEADERS_S21_QUEUE_H_
