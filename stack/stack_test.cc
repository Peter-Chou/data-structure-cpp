#include "stack.h"
#include <iostream>

template <typename T>
void print(T& p) {
  std::cout << p << "\t";
}

int main() {
  datastruct::Stack<int> s;
  std::cout << "is stack empty?  Re: " << std::boolalpha << s.empty()
            << std::endl;
  s.push(5);
  s.push(3);
  std::cout << "push 5 & 3 into stack:\nNow stack: ";
  s.traverse(print<int>);
  std::cout << std::endl << "after pop operation:\nNow stack: ";
  s.pop();
  s.traverse(print<int>);
  std::cout << std::endl
            << "is stack empty?  Re: " << std::boolalpha << s.empty()
            << std::endl;
  return 0;
}