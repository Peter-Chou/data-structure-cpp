#include "../_share/utils.h"
#include "complete_heap.h"

using datastruct::print;

int main() {
  int ARRSIZE = 8;
  int arr[] = {1, 3, 15, 6, 8, 2, 10, 9};
  std::cout << "initial array:\n";
  for (int i = 0; i < ARRSIZE; i++) {
    std::cout << arr[i] << "\t";
  }
  std::cout << std::endl;

  datastruct::PQ_ComplHeap<int> pq(arr, 8);
  std::cout << "array after heapify:\n";
  std::cout << "first max item in arrary: " << pq.delMax() << std::endl;
  std::cout << "second max item in arrary: " << pq.getMax() << std::endl;

  return 0;
}