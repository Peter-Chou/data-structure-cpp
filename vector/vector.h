#ifndef DATA_STRUCTURE_VECTOR_H_
#define DATA_STRUCTURE_VECTOR_H_
#include <cstdlib>
#include <utility>

typedef int Rank;
// #define DEFAULT_CAPACITY 3;
const int DEFAULT_CAPACITY = 3;

template <typename T>
class Vector {
 protected:
  Rank _size;
  int _capacity;
  T* _elem;

  // 以数组区间A[lo, hi)为蓝本复制向量
  void copyFrom(T const* A, Rank lo, Rank hi);
  void expand();
  void shrink();
  bool bubble(Rank lo, Rank hi);
  void bubbleSort(Rank lo, Rank hi);
  Rank max(Rank lo, Rank hi);
  void selectionSort(Rank lo, Rank hi);
  void merge(Rank lo, Rank mi, Rank hi);
  void mergeSort(Rank lo, Rank hi);
  Rank partition(Rank lo, Rank hi);
  void quickSort(Rank lo, Rank hi);
  void heapSort(Rank lo, Rank hi);

 public:
  // constructors
  Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
    _elem = new T[_capacity = c];
    for (_size = 0; _size < s; _elem[_size++] = v)
      ;
  }
  Vector(T const* A, Rank n) { copyFrom(A, 0, n); }
  Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
  Vector(Vector<T> const& v) { copyFrom(v._elem, 0, v._size); }
  Vector(Vector<T> const& v, Rank lo, Rank hi) { copyFrom(v._elem, lo, hi); }

  // destructor
  ~Vector() { delete[] _elem; }

  // read-only API
  T* begin() const { return _elem; }
  T* end() const { return _elem + _size; }
  Rank size() const { return _size; }
  bool empty() const { return !_size; }
  int disordered() const;
  Rank find(T const& e) const { return find(e, 0, _size); }
  Rank find(T const& e, Rank lo, Rank hi) const;
  Rank search(T const& e) { return (0 >= _size) ? -1 : search(e, 0, _size); }
  Rank search(T const& e, Rank lo, Rank hi) const;
  // writeable API
  T& operator[](Rank r) const;
  Vector<T>& operator=(Vector<T> const&);
  T remove(Rank r);
  int remove(Rank lo, Rank hi);
  Rank insert(Rank r, T const& e);
  Rank insert(T const& e) { return insert(_size, e); }
  void sort(Rank lo, Rank hi);
  void sort() { sort(0, _size); }
  void unsort(Rank lo, Rank hi);
  void unsort() { unsort(0, _size); }
  int deduplicate();
  int uniquify();

  // traverse
  void traverse(void (*)(T&));
  template <typename VST>
  void traverse(VST&);
};  // Vector

// ! ----------------------------------------------------------------------
// ! Implementations of non-inline functions

template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
  _elem = new T[_capacity = 2 * (hi - lo)];
  _size = 0;
  while (lo < hi) _elem[_size++] = A[lo++];
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& v) {
  if (_elem) {
    delete[] _elem;
  }
  copyFrom(v._elem, 0, v.size());
  return *this;
}

template <typename T>
void Vector<T>::expand() {  // 装载因子 100%
  if (_size < _capacity) return;
  if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
  T* oldElem = _elem;
  _elem = new T[_capacity <<= 1];  // 容量翻倍
  for (int i = 0; i < _size; i++) {
    _elem[i] = oldElem[i];
  }
  delete[] oldElem;
}

template <typename T>
void Vector<T>::shrink() {                        // 阈值为25%
  if (_capacity < DEFAULT_CAPACITY << 1) return;  // capacity 至少两倍与DC
  if (_size << 2 > _capacity) return;
  T* oldElem = _elem;
  _elem = new T[_capacity >>= 1];  // 容量减半
  for (int i = 0; i < _size; i++) {
    _elem[i] = oldElem[i];
  }
  delete[] oldElem;
}

template <typename T>
T& Vector<T>::operator[](Rank r) const {
  return _elem[r];
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
  T* V = _elem + lo;
  for (Rank i = hi - lo; i > 0; i--) {
    std::swap(V[i - 1], V[std::rand() % i]);
  }
}

template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
  while ((lo < hi--) && (e != _elem[hi]))
    ;
  return hi;  // 失败时返回lo - 1
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
  expand();
  for (int i = _size; i > r; i--) {
    _elem[i] = _elem[i - 1];
  }
  _elem[r] = e;
  _size++;
  return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
  if (lo == hi) return 0;
  while (hi < _size) {
    _elem[lo++] = _elem[hi++];
  }
  _size = lo;
  shrink();
  return hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r) {
  T e = _elem[r];
  remove(r, r + 1);
  return e;
}

template <typename T>
int Vector<T>::deduplicate() {  // 删除无序向量中重复元素
  int oldSize = _size;
  Rank i = 1;
  while (i < _size) {
    (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
  }
  return oldSize - _size;
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST& visit) {
  for (int i = 0; i < _size; i++) {
    visit(_elem[i]);
  }
}

template <typename T>
void Vector<T>::traverse(void (*visit)(T&)) {
  for (int i = 0; i < _size; i++) visit(_elem[i]);
}

template <typename T>
int Vector<T>::disordered() const {
  int n = 0;
  for (int i = 1; i < _size; i++) {
    if (_elem[i - 1] > _elem[i]) {
      n++;
    }
  }
  return n;
}

template <typename T>
int Vector<T>::uniquify() {
  Rank i = 0, j = 0;
  while (++j < _size) {
    if (_elem[i] != _elem[j]) {
      _elem[++i] = _elem[j];
    }
  }
  _size = ++i;
  shrink();
  return j - i;
}

template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const {
  binSearch(_elem, e, lo, hi);
}

template <typename T>
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {
  while (lo < hi) {
    Rank mi = (lo + hi) >> 1;
    (e < A[mi]) ? hi = mi : lo = mi + 1;
  }
  return --lo;
}

// FIXME: sort bug
template <typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
  mergeSort(lo, hi);
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
  if (hi - lo < 2) {
    return;
  }
  int mi = (lo + hi) / 2;
  mergeSort(lo, mi);
  mergeSort(mi, hi);
  merge(lo, mi, hi);
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
  T* A = _elem + lo;
  int lb = mi - lo;
  T* B = new T[lb];
  for (Rank i = 0; i < lb; i++) B[i] = A[i];
  int lc = hi - mi;
  T* C = _elem + mi;
  for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
    if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) {
      A[i++] = B[j++];
    }
    if ((k < lc) && (!(j < lb) || (C[k] < B[j]))) {
      A[i++] = C[k++];
    }
  }
  delete[] B;
}

#endif  // ! DATA_STRUCTURE_VECTOR_H_