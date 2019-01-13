#ifndef DATA_STRUCTURE_COMPLETE_HEAP_H_
#define DATA_STRUCTURE_COMPLETE_HEAP_H_

#include <utility>
#include "../_share/comparator.h"
#include "../vector/vector.h"

namespace datastruct {

// 判断PQ[i]是否合法
#define InHeap(n, i) (((-1) < (i)) && ((i) < (n)))
// PQ[i]的父节点（floor(i-1)/2，i无论正负）
#define Parent(i) ((i - 1) >> 1)
// 最后一个内部节点(即末节点的父亲)
#define LastInternal(n) Parent(n - 1)
// PQ[i]的左孩子
#define LChild(i) (1 + ((i) << 1))
// PQ[i]的右孩子
#define RChild(i) ((1 + (i)) << 1)
// 判断PQ[i]是否有父亲
#define ParentValid(i) (0 < i)
// 判断PQ[i]是否有一个左孩子
#define LChildValid(n, i) InHeap(n, LChild(i))
// 判断PQ[i]是否有两个孩子
#define RChildValid(n, i) InHeap(n, RChild(i))
// 取大者（相等时前者优先）
#define Bigger(PQ, i, j) (lt(PQ[i], PQ[j]) ? j : i)
// 父子（至多）三者中的大者
#define ProperParent(PQ, n, i)                                         \
  (RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)) \
                     : (LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i))

template <typename T>
class PQ_ComplHeap : public Vector<T> {
 public:
  PQ_ComplHeap(){};
  PQ_ComplHeap(T* A, Rank n) {
    Vector<T>::copyFrom(A, 0, n);
    heapify(n);
  }
  void insert(T);
  T getMax();
  T delMax();

 protected:
  // 对向量前n个词条中的第i个实施下滤，i < n
  Rank percolateDown(Rank n, Rank i);

  // 对向量中的第i个词条实施上滤, i < _size
  Rank percolateUp(Rank i);

  // Floyd建堆算法: O(n)
  void heapify(Rank n);
};

// ! --------------------------------------
// ! Implementations of non-inline functions

template <typename T>
T PQ_ComplHeap<T>::getMax() {
  return this->_elem[0];
}

template <typename T>
void PQ_ComplHeap<T>::insert(T e) {
  Vector<T>::insert(e);
  percolateUp(this->_size - 1);
}

template <typename T>
Rank PQ_ComplHeap<T>::percolateUp(Rank i) {
  while (ParentValid(i)) {
    Rank j = Parent(i);
    if (lt(this->_elem[i], this->_elem[j])) break;
    std::swap(this->_elem[i], this->_elem[j]);
    i = j;
  }
  return i;
}

template <typename T>
T PQ_ComplHeap<T>::delMax() {
  T maxElem = this->_elem[0];
  this->_elem[0] = this->_elem[--this->_size];
  percolateDown(this->_size, 0);
  return maxElem;
}

template <typename T>
Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i) {
  Rank j;
  while (i != (j = ProperParent(this->_elem, n, i))) {
    std::swap(this->_elem[i], this->_elem[j]);
    i = j;
  }
  return i;
}

template <typename T>
void PQ_ComplHeap<T>::heapify(Rank n) {
  for (int i = LastInternal(n); InHeap(n, i); i--) percolateDown(n, i);
}

}  // namespace datastruct

#endif  // ! DATA_STRUCTURE_COMPLETE_HEAP_H_