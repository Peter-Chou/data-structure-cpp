#ifndef DATA_STRUCTURE_QUEUE_H_
#define DATA_STRUCTURE_QUEUE_H_
#include "../list/list.h"

namespace datastruct {

template <typename T>
class Queue : private List<T> {
 public:
  // 返回Queue已存的数量
  Rank size() const { return List<T>::size(); }

  // 判断Queue是否为空
  bool empty() const { return List<T>::empty(); }

  // 在Queue尾部添加元素
  void enqueue(const T& e) { this->insertAsLast(e); }

  // 在Queue头部取出元素
  T dequeue() { return this->remove(this->first()); }

  //查看Queue头部元素
  T& front() { return this->first()->data; }

  // 函数遍历作用与Queue里的每个元素
  void traverse(std::function<void(T&)> functor) {
    return List<T>::traverse(functor);
  }
};

}  // namespace datastruct

#endif  // ! DATA_STRUCTURE_QUEUE_H_