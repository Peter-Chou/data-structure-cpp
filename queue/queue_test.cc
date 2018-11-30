#include "queue.h"
#include <iostream>

template <typename T>
void print(T& p) {
  std::cout << p << "\t";
}

int main() {
  datastruct::Queue<int> s;
  std::cout << "is queue empty?  Re: " << std::boolalpha << s.empty()
            << std::endl;
  s.enqueue(5);
  s.enqueue(3);
  std::cout << "enqueue 5 & 3 into stack:\nNow stack: ";
  s.traverse(print<int>);
  std::cout << std::endl << "after dequeue operation:\nNow stack: ";
  s.dequeue();
  s.traverse(print<int>);
  s.enqueue(7);
  std::cout << "\nenqueue 7 into stack:\nNow stack: ";
  s.traverse(print<int>);
  std::cout << "\nthe front of the queue: " << s.front() << std::endl;
  std::cout << std::endl
            << "is queue empty?  Re: " << std::boolalpha << s.empty()
            << std::endl;
  return 0;
}