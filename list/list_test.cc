#include "list.h"
#include <algorithm>
#include <iostream>

template <typename T>
void print(T& p) {
  std::cout << p << "\t";
}

int main() {
  datastruct::List<int> ls;
  ls.insertAsLast(3);
  ls.insertAsLast(3);
  ls.insertAsLast(2);
  ls.insertAsLast(5);
  ls.insertAsLast(6);
  ls.insertAsLast(8);
  std::cout << "original list:\n";
  ls.traverse(print<int>);
  std::cout << std::endl;
  std::cout << "sort the list:\n";
  ls.sort();
  ls.traverse(print<int>);
  std::cout << std::endl;
  std::cout << "uniquify the list:\n";
  ls.uniquify();
  ls.traverse(print<int>);
  std::cout << std::endl;
  return 0;
}