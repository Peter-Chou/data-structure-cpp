#ifndef DATA_STRUCTURE_BIN_NODE_H_
#define DATA_STRUCTURE_BIN_NODE_H_

#include <iostream>
#include "../queue/queue.h"
#include "../stack/stack.h"

namespace datastruct {
#define BinNodePosi(T) BinNode<T>*           // 节点位置
#define stature(p) ((p) ? (p)->height : -1)  // 节点高度

/******************************************
 * BinNode状态与性质的判断 (x is BinNode)
 ******************************************/
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))  // 至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))  // 同时拥有两个孩子
#define IsLeaf(x) (!HasChild(x))

/******************************************
 * 与BinNode具有特定关系的节点及指针
 ******************************************/
// p is BinNode*
#define sibling(p) /*兄弟*/ (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)

// x is BinNode*
#define uncle(x) /*叔叔*/ \
  (IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc)

// x is BinNode
#define FromParentTo(x) /*来自父亲的引用*/ \
  (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))

typedef enum { RB_RED, RB_BLACK } RBColor;  // 节点颜色

template <typename T>
struct BinNode {
  T data;
  BinNodePosi(T) parent;  // 父节点
  BinNodePosi(T) lc;      // 左孩子
  BinNodePosi(T) rc;      // 右孩子
  int height;
  int npl;  // Null Path Length（左式堆，也可直接用height代替）
  RBColor color;  // 颜色（红黑树）

  // constructors
  BinNode()
      : parent(nullptr),
        lc(nullptr),
        rc(nullptr),
        height(0),
        npl(1),
        color(RB_RED) {}
  BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr,
          BinNodePosi(T) rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED)
      : data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

  // 统计当前节点后代总数，亦即以其为根的子树的规模
  int size();

  void report() {
    std::cout << std::endl;
    std::cout << "current node: " << this->data << std::endl;
    if (this->parent)
      std::cout << "parent: " << this->parent->data << std::endl;
    if (this->lc) std::cout << "left child: " << this->lc->data << std::endl;
    if (this->rc) std::cout << "right child: " << this->rc->data << std::endl;
    std::cout << std::endl;
  }

  // 作为当前节点的左孩子插入新节点
  BinNodePosi(T) insertAsLC(const T&);

  // 作为当前节点的右孩子插入新节点
  BinNodePosi(T) insertAsRC(const T&);

  // 取当前节点的直接后继
  BinNodePosi(T) succ();

  // 子树层次遍历
  template <typename VST>
  void travLevel(VST&);

  // 子树先序遍历
  template <typename VST>
  void travPre(VST&);

  // 子树中序遍历
  template <typename VST>
  void travIn(VST&);

  // 子树后序遍历
  template <typename VST>
  void travPost(VST&);

  bool operator<(const BinNode& bn) { return data < bn.data; }
  bool operator<=(const BinNode& bn) { return data <= bn.data; }
  bool operator>(const BinNode& bn) { return data > bn.data; }
  bool operator>=(const BinNode& bn) { return data >= bn.data; }
  bool operator==(const BinNode& bn) { return data == bn.data; }
};

// ! --------------------------------------
// ! Implementations of non-inline functions

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(const T& e) {
  // 新子节点的父亲指向invoking节点
  // invoking节点的左孩子指向新子节点
  return lc = new BinNode(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(const T& e) {
  return rc = new BinNode(e, this);
}

//从当前节点出发，沿左分支不断深入，直至没有左分支的节点，沿途节点遇到后立即访问
template <typename T, typename VST>
static void visitAlongVine(BinNodePosi(T) x, VST& visit,
                           Stack<BinNodePosi(T)>& S) {
  while (x) {
    visit(x->data);
    S.push(x->rc);
    x = x->lc;
  }
}

template <typename T, typename VST>
void travPre(BinNodePosi(T) x, VST& visit) {
  Stack<BinNodePosi(T)> S;
  while (true) {
    visitAlongVine(x, visit, S);
    if (S.empty()) break;
    x = S.pop();
  }
}

template <typename T>
template <typename VST>
void BinNode<T>::travPre(VST& visit) {
  // travPre(this, visit);
  datastruct::travPre(this, visit);
}

template <typename T, typename VST>
void travIn(BinNodePosi(T) x, VST& visit) {
  Stack<BinNodePosi(T)> S;
  while (true)
    if (x) {
      S.push(x);
      x = x->lc;
    } else if (!S.empty()) {
      x = S.pop();
      visit(x->data);
      x = x->rc;
    } else
      break;
}

template <typename T>
template <typename VST>                //元素类型、操作器
void BinNode<T>::travIn(VST& visit) {  //二叉树中序遍历算法统一入口
  // travIn(this, visit);
  datastruct::travIn(this, visit);
}

template <typename T>
static void gotoHLVFL(Stack<BinNodePosi(T)>& S) {
  while (BinNodePosi(T) x = S.top())
    if (HasLChild(*x)) {
      if (HasRChild(*x)) S.push(x->rc);
      S.push(x->lc);
    } else
      S.push(x->rc);
  S.pop();
}

template <typename T, typename VST>
void travPost(BinNodePosi(T) x, VST& visit) {
  Stack<BinNodePosi(T)> S;
  if (x) S.push(x);
  while (!S.empty()) {
    if (S.top() != x->parent) gotoHLVFL(S);
    x = S.pop();
    visit(x->data);
  }
}

template <typename T>
template <typename VST>
void BinNode<T>::travPost(VST& visit) {
  // travPost(this, visit);
  datastruct::travPost(this, visit);
}

template <typename T>
template <typename VST>
void BinNode<T>::travLevel(VST& visit) {
  Queue<BinNodePosi(T)> Q;
  Q.enqueue(this);
  while (!Q.empty()) {
    BinNodePosi(T) x = Q.dequeue();
    visit(x->data);
    if (HasLChild(*x)) Q.enqueue(x->lc);
    if (HasRChild(*x)) Q.enqueue(x->rc);
  }
}

template <typename T>
BinNodePosi(T) BinNode<T>::succ() {
  BinNodePosi(T) s = this;
  if (rc) {
    s = rc;
    while (HasChild(*s)) s = s->lc;
  } else {
    while (IsRChild(*s)) s = s->parent;
    s = s->parent;
  }
  return s;
}

}  // namespace datastruct

#endif  // ! DATA_STRUCTURE_BIN_NODE_H_
