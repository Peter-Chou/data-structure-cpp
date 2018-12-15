#ifndef DATA_STRUCTURE_SHARE_UTILS_H_
#define DATA_STRUCTURE_SHARE_UTILS_H_

#include <iostream>

namespace datastruct {

template <typename T>
void print(T& p) {
  std::cout << p << "\t";
}

}  // namespace datastruct

#endif  // ! DATA_STRUCTURE_SHARE_UTILS_H_