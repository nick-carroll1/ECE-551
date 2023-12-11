#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  else if (n == 1) {
    return 1;
  }
  else {
    size_t max_len = 1;
    size_t current_len = 1;
    for (size_t i = 1; i < n; i++) {
      if (array[i] > array[i - 1]) {
        current_len++;
      }
      else {
        if (current_len > max_len) {
          max_len = current_len;
        }
        current_len = 1;
      }
    }
    if (current_len > max_len) {
      max_len = current_len;
    }
    return max_len;
  }
}
