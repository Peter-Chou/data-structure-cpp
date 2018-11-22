#include "vector.h"
#include <algorithm>
#include <iostream>

template <typename U>
void square(U&);

template <typename T>
void show(T& item) {
  std::cout << item << "\t";
}

template <typename T>
struct Show {
  void operator()(T& item) { std::cout << item << "\t"; }
};

int main() {
  Show<int> show_item;
  Vector<int> arr;
  arr.insert(0, 2);
  arr.insert(0, 4);
  arr.insert(1, 5);
  std::cout << "original vector:\n";
  arr.traverse(show);
  std::cout << "\ninsert 7 at the head:\n";
  arr.insert(0, 7);
  arr.traverse(show);
  std::cout << "\nsquare each element in vector:\n";
  arr.traverse(square);
  arr.traverse(show);
  std::cout << "\nsort vector:\n";
  arr.sort();
  for (auto x : arr) {
    std::cout << x << "\t";
  }
  std::cout << "\nunsort the vector:\n";
  arr.unsort();
  arr.traverse(show);
  std::cout << "\nremove 4 from vector:\n";
  arr.remove(2);
  // arr.traverse(show);
  arr.traverse(show_item);
  std::cout << "\ncurrent vector size: " << arr.size() << std::endl;
  return 0;
}

template <typename U>
void square(U& item) {
  item *= item;
}