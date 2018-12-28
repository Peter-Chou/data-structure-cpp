
#ifndef DATA_STRUCTURE_BIN_SEARCH_TREE_H_
#define DATA_STRUCTURE_BIN_SEARCH_TREE_H_

#include "../binary_tree/bin_tree.h"
#include <utility>

namespace datastruct {

#define EQUAL(e, v) (!(v) || (e) == (v)->data)

template <typename T>
class BST : public BinTree<T> {
 public:
  // 在BST中查找关键码e
  virtual BinNodePosi(T) & search(const T& e);

  // 插入
  virtual BinNodePosi(T) insert(const T& e);

  // 删除
  virtual bool remove(const T& e);

 protected:
  // "命中"节点的父亲
  BinNodePosi(T) _hot;

  // 按照"3 + 4"结构，连接3个节点及4颗子树
  BinNodePosi(T)
      connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
                BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));

  // 对x及其父亲、祖父左统一旋转调整
  BinNodePosi(T) rotateAt(BinNodePosi(T) x);
};

// ! ----------------------------------------------------------------------
// ! Implementations of non-inline functions

// 在以v为跟的BST子树中查找关键码，返回时，返回值指向命中节点，hot指向其父亲
template <typename T>
    static BinNodePosi(T) &
    searchIn(BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot) {
  if (EQUAL(e, v)) return v;
  hot = v;
  while (true) {
    BinNodePosi(T)& c = (e < hot->data) ? hot->lc : hot->rc;
    if (EQUAL(e, c)) return c;
    hot = c;
  }
}

template <typename T>
    BinNodePosi(T) & BST<T>::search(const T& e) {
  return searchIn(this->_root, e, _hot = nullptr);
}

template <typename T>
BinNodePosi(T) BST<T>::insert(const T& e) {
  BinNodePosi(T)& x = search(e);
  if (x) return x;
  x = new BinNode<T>(e, _hot);
  this->_size++;
  // _size++;
  this->updateHeightAbove(x);
  return x;
}

template <typename T>
bool BST<T>::remove(const T& e) {
  BinNodePosi(T)& x = search(e);
  if (!x) return false;
  removeAt(x, _hot);
  this->_size--;
  this->updateHeightAbove(_hot);
  return true;
}

template <typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T) & x, BinNodePosi(T) & hot) {
  BinNodePosi(T) w = x;
  BinNodePosi(T) succ = nullptr;
  if (!HasLChild(*x))
    succ = x = x->rc;
  else if (!HasRChild(*x))
    succ = x = x->lc;
  else {
    w = w->succ();
    std::swap(x->data, w->data);
    BinNodePosi(T) u = w->parent;
    ((u == x) ? u->rc : u->lc) = succ = w->rc;
  }
  hot = w->parent;
  if (succ) succ->parent = hot;
  release(w->data);
  release(w);
  return succ;
}

}  // namespace datastruct

#endif  // ! DATA_STRUCTURE_BIN_SEARCH_TREE_H_
