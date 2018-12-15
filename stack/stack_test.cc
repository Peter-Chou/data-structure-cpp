#include "stack.h"
#include <iostream>
#include "../_share/utils.h"

using datastruct::print;

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
  std::cout << "\n the size of stack: " << s.size();
  return 0;
}