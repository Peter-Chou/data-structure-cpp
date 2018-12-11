#ifndef DATA_STRUCTURE_STACK_H_
#define DATA_STRUCTURE_STACK_H_

#include "../vector/vector.h"
// #include "../list/list.h"

namespace datastruct {

// ***************************
// implementation using Vector
template <typename T>
class Stack : private Vector<T> {
 public:
  // 返回Stack已存的数量
  Rank size() const { return Vector<T>::size(); }

  // 判断Stack是否为空
  bool empty() const { return Vector<T>::empty(); }

  // 在栈顶添加元素
  void push(const T& e) { this->insert(this->size(), e); }

  // 从栈顶取出元素
  T pop() { return this->remove(this->size() - 1); }

  // 查看栈顶的元素
  T& top() { return (*this)[this->size() - 1]; }

  // 函数遍历作用与Stack里的每个元素
  void traverse(std::function<void(T&)> functor) {
    return Vector<T>::traverse(functor);
  }
};

// ***************************
// implementation using List
// template <typename T>
// class Stack : private List<T> {
//  public:
//   Rank size() const { return List<T>::size(); }
//   bool empty() const { return List<T>::empty(); }
//   void push(const T& e) { this->insertAsLast(e); }
//   T pop() { return this->remove(this->last()); }
//   T& top() { return this->last()->data; }
//   void traverse(std::function<void(T&)> functor) {
//     return List<T>::traverse(functor);
//   }
// };

}  // namespace datastruct
#endif  // ! DATA_STRUCTURE_STACK_H_