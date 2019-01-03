
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

  // 按照"3 +
  // 4"结构，连接3个节点及4颗子树，返回充足之后的局部子树根节点位置（即b）
  // 上层节点指向子树根节点的连接由上层调用者完成
  BinNodePosi(T)
      connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
                BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));

  // 对x及其父亲、祖父左统一旋转调整，返回调整之后局部子树根节点位置
  // 上层节点指向子树根节点的连接由上层调用者完成
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

template <typename T>
BinNodePosi(T) BST<T>::connect34(BinNodePosi(T) a, BinNodePosi(T) b,
                                 BinNodePosi(T) c, BinNodePosi(T) T0,
                                 BinNodePosi(T) T1, BinNodePosi(T) T2,
                                 BinNodePosi(T) T3) {
  a->lc = T0;
  if (T0) T0->parent = a;
  a->rc = T1;
  if (T1) T1->parent = a;
  this->updateHeight(a);
  c->lc = T2;
  if (T2) T2->parent = c;
  c->rc = T3;
  if (T3) T3->parent = c;
  this->updateHeight(c);
  b->lc = a;
  a->parent = b;
  b->rc = c;
  c->parent = b;
  this->updateHeight(b);
  return b;
}

template <typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v) {  // v为非空孙辈节点
  BinNodePosi(T) p = v->parent;
  BinNodePosi(T) g = p->parent;
  if (IsLChild(*p))     /* zig */
    if (IsLChild(*v)) { /* zig-zig */
      p->parent = g->parent;
      return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
    } else { /* zig-zag */
      v->parent = g->parent;
      return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
    }
  else                    /* zag */
      if (IsRChild(*v)) { /* zag-zag */
    p->parent = g->parent;
    return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
  } else {
    v->parent = g->parent;
    return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
  }
}

}  // namespace datastruct

#endif  // ! DATA_STRUCTURE_BIN_SEARCH_TREE_H_
