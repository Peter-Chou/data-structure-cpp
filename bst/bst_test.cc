#include "bst.h"
#include "../_share/utils.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <unordered_set>

using datastruct::print;

typedef datastruct::BinNode<int> Node;
typedef datastruct::BinTree<int> Tree;

int main() {
  std::srand(1000);
  std::unordered_set<int> datas;
  while (datas.size() < 10) {
    datas.insert(std::move(std::rand() % 10));
  }

  datastruct::BST<int> bs;

  for (const auto& elem : datas) {
    bs.insert(elem);
  }

  std::cout << "Initial BST Tree with Breadth-First traversal:\n";
  bs.travLevel(print<int>);
  std::cout << std::endl;
  std::cout << "remove 5 from BST Tree:\n";
  bs.remove(5);
  bs.travLevel(print<int>);

  return 0;
}
