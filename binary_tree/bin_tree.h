#ifndef DATA_STRUCTURE_BIN_TREE_H_
#define DATA_STRUCTURE_BIN_TREE_H_

#include "../_share/comparator.h"
#include "../_share/release.h"
#include "bin_node.h"
#include <algorithm>

namespace datastruct {

template <typename T>
class BinTree {
 public:
  BinTree() : _size(0), _root(NULL) {}
  ~BinTree() {
    if (_size > 0) remove(_root);
  }

  // 返回规模
  int size() const { return _size; }

  // 判断是否为空
  bool empty() const { return !_root; }

  // 返回树根
  BinNodePosi(T) root() const { return _root; }

  // 插入根节点
  BinNodePosi(T) insertAsRoot(const T& e);

  // e作为x的左孩子（原无）插入
  BinNodePosi(T) insertAsLC(BinNodePosi(T) x, const T& e);

  // e作为x的右孩子（原无）插入
  BinNodePosi(T) insertAsRC(BinNodePosi(T) x, const T& e);

  // T作为x左子树接入
  BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>*& S);

  // T作为x右子树接入
  BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>*& S);

  // 删除以位置x处节点为根的子树，返回该子树原先的规模
  int remove(BinNodePosi(T) x);

  // 将子树x从当前树中摘除，并将其转换为一颗独立子树
  BinTree<T>* secede(BinNodePosi(T) x);

  // 层次遍历
  template <typename VST>
  void travLevel(VST& visit) {
    if (_root) _root->travLevel(visit);
  }

  // 先序遍历
  template <typename VST>
  void travPre(VST& visit) {
    if (_root) _root->travPre(visit);
  }

  // 中序遍历
  template <typename VST>
  void travIn(VST& visit) {
    if (_root) _root->travIn(visit);
  }

  // 后序遍历
  template <typename VST>
  void travPost(VST& visit) {
    if (_root) _root->travPost(visit);
  }

  bool operator<(const BinTree<T>& t) {
    return _root && t._root && lt(_root, t._root);
  }

  bool operator==(const BinTree<T>& t) {
    return _root && t._root && (_root == t._root);
  }

 protected:
  int _size;             // 规模
  BinNodePosi(T) _root;  // 根节点

  // 更新节点x的高度
  virtual int updateHeight(BinNodePosi(T) x);

  // 更新节点x及其祖先的高度
  void updateHeightAbove(BinNodePosi(T) x);
};

// ! --------------------------------------
// ! Implementations of non-inline functions

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x) {
  return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) {
  while (x) {
    updateHeight(x);
    x = x->parent;
  }
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(const T& e) {
  _size = 1;
  return _root = new BinNode<T>(e);  // 将e当作根节点插入空的二叉树
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, const T& e) {
  _size++;
  x->insertAsRC(e);
  updateHeightAbove(x);
  return x->rc;  // 返回新的叶节点
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, const T& e) {
  _size++;
  x->insertAsLC(e);
  updateHeightAbove(x);
  return x->lc;  // 返回新的叶节点
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& S) {
  if ((x->rc = S->_root)) x->rc->parent = x;
  _size += S->_size;
  updateHeightAbove(x);
  S->_root = nullptr;
  S->_size = 0;
  release(S);
  S = nullptr;
  return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>*& S) {
  if ((x->lc = S->_root)) x->lc->parent = x;
  _size += S->_size;
  updateHeightAbove(x);
  S->_root = nullptr;
  S->_size = 0;
  release(S);
  S = nullptr;
  return x;
}

template <typename T>
static int removeAt(BinNodePosi(T) x) {
  if (!x) return 0;
  int n = 1 + removeAt(x->lc) + removeAt(x->rc);
  release(x->data);
  release(x);
  return n;
}

template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {
  FromParentTo(*x) = nullptr;
  updateHeightAbove(x->parent);
  int n = removeAt(x);
  _size -= n;
  return n;
}

template <typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x) {
  FromParentTo(*x) = nullptr;
  updateHeightAbove(x->parent);
  BinTree<T>* S = new BinTree<T>;
  S->_root = x;
  x->parent = nullptr;
  S->_size = x->size();
  _size -= S->_size;
  return S;
}

}  // namespace datastruct

#endif  // ! DATA_STRUCTURE_BIN_TREE_H_
