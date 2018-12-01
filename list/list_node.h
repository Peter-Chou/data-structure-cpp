#ifndef DATA_STRUCTURE_LIST_NODE_H_
#define DATA_STRUCTURE_LIST_NODE_H_

namespace datastruct {

typedef int Rank;
#define ListNodePosi(T) ListNode<T>*

template <typename T>
struct ListNode {
  T data;
  ListNodePosi(T) pred;
  ListNodePosi(T) succ;

  // constructors
  ListNode() {}
  ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr)
      : data(e), pred(p), succ(s) {}

  // API
  // insert the node next to current node
  ListNodePosi(T) insertAsPred(T const& e);

  // insert the node ahead of current node
  ListNodePosi(T) insertAsSucc(T const& e);
};

// ***************************************************************
// * implementation of non-inline template methods

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(const T& e) {
  ListNodePosi(T) x = new ListNode(e, pred, this);
  pred->succ = x;
  pred = x;
  return x;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(const T& e) {
  ListNodePosi(T) x = new ListNode(e, this, succ);
  succ->pred = x;
  succ = x;
  return x;
}
}  // namespace datastruct
#endif  // ! DATA_STRUCTURE_LIST_NODE_H_