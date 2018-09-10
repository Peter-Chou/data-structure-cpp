#include "vector.h"

template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
  _elem = new T[_capacity = 2 * (hi - lo)];
  _size = 0;
  while (lo < hi) {
    _elem[_size++] = A[lo++];
  }
}

template <typename T>
Vector<T>::Vector(int c, int s, T v) {
  _elem = new T[_capacity = c];
  for (_size = 0; _size < s;) {
    _elem[_size++] = v;
  }
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& v) {
  if (_elem) {
    delete[] _elem;
  }
  copyFrom(v._elem, 0, v._size);
  return *this;
}

// TODO: complete the remaining method definitions