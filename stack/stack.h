#ifndef DATA_STRUCTURE_STACK_H_
#define DATA_STRUCTURE_STACK_H_

#include "../vector/vector.h"
// #include "../list/list.h"

namespace datastruct {

// ***************************
// implementation using Vector
template <typename T>
class Stack : private Vector<T> {
  using Vector<T>::size;
  using Vector<T>::insert;
  using Vector<T>::remove;

 public:
  Rank size() const { return Vector<T>::size(); }
  bool empty() const { return Vector<T>::empty(); }
  void push(const T& e) { insert(size(), e); }
  T pop() { return remove(size() - 1); }
  T& top() { return (*this)[size() - 1]; }
  void traverse(std::function<void(T&)> functor) {
    return Vector<T>::traverse(functor);
  }
};

// ***************************
// implementation using Vector
// implementation using List
// template <typename T>
// class Stack : public List<T> {
//  public:
//   using List<T>::insertAsLast;
//   using List<T>::remove;
//   using List<T>::last;
//   void push(const T& e) { insertAsLast(e); }
//   T pop() { return remove(last()); }
//   T& top() { return last()->data; }
// };

}  // namespace datastruct
#endif  // ! DATA_STRUCTURE_STACK_H_