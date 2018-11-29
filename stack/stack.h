#include "../vector/vector.h"
// #include "../list/list.h"

namespace datastruct {

// ***************************
// implementation using Vector
template <typename T>
class Stack : public Vector<T> {
 public:
  using Vector<T>::size;
  using Vector<T>::insert;
  using Vector<T>::remove;
  void push(const T& e) { insert(size(), e); }
  T pop() { return remove(size() - 1); }
  T& top() { return (*this)[size() - 1]; }
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