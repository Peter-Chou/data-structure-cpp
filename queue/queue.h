#ifndef DATA_STRUCTURE_QUEUE_H_
#define DATA_STRUCTURE_QUEUE_H_
#include "../list/list.h"

namespace datastruct {

template <typename T>
class Queue : private List<T> {
 public:
  Rank size() const { return List<T>::size(); }
  bool empty() const { return List<T>::empty(); }
  void enqueue(const T& e) { this->insertAsLast(e); }
  T dequeue() { return this->remove(this->first()); }
  T& front() { return this->first()->data; }
  void traverse(std::function<void(T&)> functor) {
    return List<T>::traverse(functor);
  }
};

}  // namespace datastruct

#endif  // ! DATA_STRUCTURE_QUEUE_H_