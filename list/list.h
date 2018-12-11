#ifndef DATA_STRUCTURE_LIST_H_
#define DATA_STRUCTURE_LIST_H_

#include "list_node.h"
#include <functional>


namespace datastruct {

template <typename T>
class List {
 public:
  // constructors
  List() { init(); }

  // 整体复制列表L
  List(const List<T>& L);

  // 复制列表L中自第r项其的n项
  List(const List<T>& L, Rank r, int n);

  // 复制列表L中自位置p起的n项
  List(ListNodePosi(T) p, int n);

  // destructors
  // 释放（包含头，尾哨兵在内的）所有节点
  ~List();

  // read-only API
  Rank size() const { return _size; }
  bool empty() const { return _size <= 0; }

  // 支持循秩访问（效率低）
  T& operator[](Rank r) const;

  // 返回首节点位置
  ListNodePosi(T) first() const { return header->succ; }

  // 返回尾节点位置
  ListNodePosi(T) last() const { return trailer->pred; }

  // 判断位置p是否对外合法
  bool valid(ListNodePosi(T) p) const {  // add const
    return p && (trailer != p) && (header != p);
  }

  // 判断列表是否已排序
  int disordered() const;

  // 无序列表中查找
  ListNodePosi(T) find(const T& e) const { return find(e, _size, trailer); }

  // 无序区间中查找
  ListNodePosi(T) find(const T& e, int n, ListNodePosi(T) p) const;

  // 有序列表中查找
  ListNodePosi(T) search(const T& e) const { return search(e, _size, trailer); }

  // 有序区间中查找
  ListNodePosi(T) search(const T& e, int n, ListNodePosi(T) p) const;

  // writeable API
  // 将e当作首节点插入
  ListNodePosi(T) insertAsFirst(const T& e);

  // 将e当作尾节点插入
  ListNodePosi(T) insertAsLast(const T& e);

  // 将e当作p的后继插入
  ListNodePosi(T) insertA(ListNodePosi(T) p, const T& e);

  // 将e当作p的前驱插入
  ListNodePosi(T) insertB(ListNodePosi(T) p, const T& e);

  // 删除合法位置p处的节点，返回被删除节点的data
  T remove(ListNodePosi(T) p);

  // 全列表归并排序
  void merge(List<T>& L) {
    merge(first(), _size, L, L.first(), L.last(), L._size);
  }

  // 列表区间排序
  void sort(ListNodePosi(T) p, int n);

  // 列表整体排序
  void sort() { sort(first(), _size); }

  // 无序列表去重
  int deduplicate();

  // 有序列表去重
  int uniquify();

  // traverse
  void traverse(std::function<void(T&)>);

 private:
  int _size;
  ListNodePosi(T) header;   // 头哨兵
  ListNodePosi(T) trailer;  // 尾哨兵

 protected:
  // 创建列表是的初始化
  void init();

  // 清楚所有节点
  int clear();

  // 复制列表中自位置p起的n项
  void copyNodes(ListNodePosi(T), int);

  // 归并
  void merge(ListNodePosi(T) &, int, List<T>&, ListNodePosi(T), int);

  // 对从p开始连续的n个节点归并排序
  void mergeSort(ListNodePosi(T) &, int);
};

// ! ----------------------------------------------------------------------
// ! Implementations of non-inline functions

template <typename T>
void List<T>::init() {
  header = new ListNode<T>;
  trailer = new ListNode<T>;
  header->succ = trailer;
  header->pred = nullptr;
  trailer->pred = header;
  trailer->succ = nullptr;
  _size = 0;
}

template <typename T>
T& List<T>::operator[](Rank r) const {
  ListNodePosi(T) p = first();
  while (0 < r--) p = p->succ;
  return p->data;
}

template <typename T>
ListNodePosi(T) List<T>::find(const T& e, int n, ListNodePosi(T) p) const {
  while (0 < n--)
    if (e == (p = p->pred)->data) return p;
  return nullptr;
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(const T& e) {
  _size++;
  return header->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast(const T& e) {
  _size++;
  return trailer->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, const T& e) {
  _size++;
  return p->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, const T& e) {
  _size++;
  return p->insertAsPred(e);
}

template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n) {
  init();
  while (n--) {
    insertAsLast(p->data);
    p = p->succ;
  }
}

template <typename T>
List<T>::List(ListNodePosi(T) p, int n) {
  copyNodes(p, n);
}

template <typename T>
List<T>::List(const List<T>& L) {
  copyNodes(L.first(), L._size);
}

template <typename T>
List<T>::List(const List<T>& L, Rank r, int n) {
  copyNodes(L[r], n);
}

template <typename T>
T List<T>::remove(ListNodePosi(T) p) {
  T e = p->data;
  p->pred->succ = p->succ;
  p->succ->pred = p->pred;
  delete p;
  _size--;
  return e;
}

template <typename T>
List<T>::~List() {
  clear();
  delete header;
  delete trailer;
}

template <typename T>
int List<T>::clear() {
  int oldSize = _size;
  while (0 < _size) remove(header->succ);
  return oldSize;
}

template <typename T>
int List<T>::deduplicate() {
  if (_size < 2) return 0;
  int oldSize = _size;
  ListNodePosi(T) p = header;
  Rank r = 0;
  while (trailer != (p = p->succ)) {  // O(n^2)
    ListNodePosi(T) q = find(p->data, r, p);
    q ? remove(q) : r++;  // 如前缀有雷同，删除前面的
  }
  return oldSize - _size;
}

template <typename T>
int List<T>::uniquify() {
  if (_size < 2) return 0;
  int oldSize = _size;
  ListNodePosi(T) p = first();
  ListNodePosi(T) q;
  while (trailer != (q = p->succ))
    if (p->data != q->data)
      p = q;
    else
      remove(q);  // 如果雷同，删除后者
  return oldSize - _size;
}

template <typename T>
ListNodePosi(T) List<T>::search(const T& e, int n, ListNodePosi(T) p) const {
  do {
    p = p->pred;
    --n;
  } while ((-1 < n) && (e < p->data));
  return p;
}

template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n) {
  mergeSort(p, n);
}

template <typename T>
void List<T>::mergeSort(ListNodePosi(T) & p, int n) {
  if (n < 2) return;
  int m = n >> 1;
  ListNodePosi(T) q = p;
  for (int i = 0; i < m; i++) q = q->succ;
  mergeSort(p, m);
  mergeSort(q, n - m);
  merge(p, m, *this, q, n - m);
}

template <typename T>
void List<T>::merge(ListNodePosi(T) & p, int n, List<T>& L, ListNodePosi(T) q,
                    int m) {
  ListNodePosi(T) pp = p->pred;
  while (0 < m)
    if ((0 < n) && (p->data <= q->data)) {
      if (q == (p = p->succ)) break;
      n--;
    } else {
      insertB(p, L.remove((q = q->succ)->pred));
      m--;
    }
  p = pp->succ;
}

template <typename T>
void List<T>::traverse(std::function<void(T&)> visit) {
  for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
    visit(p->data);
}

}  // namespace datastruct
#endif  // ! DATA_STRUCTURE_LIST_H_