#include "function.h"

int binarySearchHelper(Function<int, int> * f, int low, int high, int min, int max) {
  if (high == low) {
    return low;
  }
  int x = (high + low) / 2;
  int y;
  if (x == min) {
    return min;
  }
  if (x == max) {
    return max;
  }
  if (x == low or x == high) {
    y = f->invoke(high);
    if (y <= 0) {
      return high;
    }
    if (y > 0) {
      return low;
    }
  }
  y = f->invoke(x);
  if (y == 0) {
    return x;
  }
  if (y > 0) {
    return binarySearchHelper(f, low, x, min, max);
  }
  else {
    return binarySearchHelper(f, x, high, min, max);
  }
}

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  return binarySearchHelper(f, low, high, low, high - 1);
}
