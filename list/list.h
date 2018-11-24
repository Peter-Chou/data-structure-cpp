#ifndef DATA_STRUCTURE_LIST_H_
#define DATA_STRUCTURE_LIST_H_

#include <functional>
#include "list_node.h"

namespace datastruct {

template <typename T>
class List {
 private:
  int _size;
  ListNodePosi(T) header;
  ListNodePosi(T) trailer;

 protected:
  void init();
  int clear();
  void copyNodes(ListNodePosi(T), int);
  void merge(ListNodePosi(T) &, int, ListNodePosi(T), int);
  void mergeSort(ListNodePosi(T) &, int);
  void selectionSort(ListNodePosi(T), int);
  void insertionSort(ListNodePosi(T), int);

 public:
  // constructors
  List() { init(); }
  List(const List<T>& L);
  List(const List<T>& L, Rank r, int n);
  List(ListNodePosi(T) p, int n);
  // destructors
  ~List();
  // read-only API
  Rank size() const { return _size; }
  bool empty() const { return _size <= 0; }
  T& operator[](Rank r) const;
  ListNodePosi(T) first() const { return header->succ; }
  ListNodePosi(T) last() const { return trailer->pred; }
  bool valid(ListNodePosi(T) p) const {  // add const
    return p && (trailer != p) && (header != p);
  }
  int disordered() const;
  ListNodePosi(T) find(const T& e) const { return find(e, _size, trailer); }
  ListNodePosi(T) find(const T& e, int n, ListNodePosi(T) p) const;
  ListNodePosi(T) search(const T& e) const { return search(e, _size, trailer); }
  ListNodePosi(T) search(const T& e, int n, ListNodePosi(T) p) const;
  ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
  ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }
  // writeable API
  ListNodePosi(T) insertAsFirst(const T& e);
  ListNodePosi(T) insertAsLast(const T& e);
  ListNodePosi(T) insertA(ListNodePosi(T) p, const T& e);
  ListNodePosi(T) insertB(ListNodePosi(T) p, const T& e);
  T remove(ListNodePosi(T) p);
  void merge(List<T>& L) {
    merge(first(), size, L, L.first(), L.last(), L._size);
  }
  void sort(ListNodePosi(T) p, int n);
  void sort() { sort(first(), _size); }
  int deduplicate();
  int uniquify();
  void reverse();
  // traverse
  void traverse(std::function<void(T&)>);
};

// ! ----------------------------------------------------------------------
// ! Implementations of non-inline functions

template <typename T>
void List<T>::traverse(std::function<void(T&)> visit) {
  for (int i = 0; i < _size; i++) visit(_elem[i]);
}

}  // namespace datastruct
#endif  // ! DATA_STRUCTURE_LIST_H_