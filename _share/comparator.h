#ifndef DATA_STRUCTURE_SHARE_COMPARATOR_H_
#define DATA_STRUCTURE_SHARE_COMPARATOR_H_

namespace datastruct {

template <typename T>
static bool lt(T* a, T* b) {
  return lt(*a, *b);
}  // less than
template <typename T>
static bool lt(T& a, T& b) {
  return a < b;
}  // less than
template <typename T>
static bool eq(T* a, T* b) {
  return eq(*a, *b);
}  // equal
template <typename T>
static bool eq(T& a, T& b) {
  return a == b;
}  // equal

}  // namespace datastruct
#endif  // ! DATA_STRUCTURE_SHARE_COMPARATOR_H_