#include <iostream>
#include "vector.h"

template <typename U>
void square(U&);

int main() {
  Vector<int> arr;
  arr.insert(0, 9);
  arr.insert(0, 4);
  arr.traverse(square);
  for (int i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << "\t";
  }
  return 0;
}

template <typename U>
void square(U& item) {
  item *= item;
}