#ifndef DATA_STRUCTURE_QUEUE_H_
#define DATA_STRUCTURE_QUEUE_H_
#include "../list/list.h"

namespace datastruct {

template <typename T>
class Queue : public List<T> {
  using List<T>::insertAsLast;
  using List<T>::remove;
  using List<T>::first;

 public:
  void enqueue(const T& e) { insertAsLast(e); }
  T dequeue() { return remove(first()); }
  T& front() { return first()->data; }
};

}  // namespace datastruct

#endif  // ! DATA_STRUCTURE_QUEUE_H_