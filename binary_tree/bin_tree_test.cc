#include "bin_tree.h"
#include "../_share/utils.h"
#include <iostream>
#include <queue>


using datastruct::print;

typedef datastruct::BinNode<int> Node;
typedef datastruct::BinTree<int> Tree;

void buildBinTree(Tree*, int num);

int main() {
  datastruct::BinTree<int> bs;
  std::cout << "build the binary tree with 10 item:\n";
  buildBinTree(&bs, 10);
  std::cout << std::endl;
  std::cout << "Pre-Order traversal:\n";
  bs.travPre(print<int>);
  std::cout << std::endl;
  std::cout << "In-Order traversal:\n";
  bs.travIn(print<int>);
  std::cout << std::endl;
  std::cout << "Post-Order traversal:\n";
  bs.travPost(print<int>);
  std::cout << std::endl;
  std::cout << "Breadth-First traversal:\n";
  bs.travLevel(print<int>);
  return 0;
}

void buildBinTree(Tree* bs, int num) {
  std::queue<Node*> Q;
  for (int i = 0; i < num; ++i) {
    if (bs->empty()) {
      auto f = bs->insertAsRoot(i + 1);
      Q.push(f);
    } else {
      auto e = Q.front();
      if (e->lc) {
        auto f = bs->insertAsRC(e, i + 1);
        Q.push(f);
        Q.pop();
      } else {
        auto f = bs->insertAsLC(e, i + 1);
        Q.push(f);
      }
    }
  }
}