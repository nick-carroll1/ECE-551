#include "test-bsearch.hpp"

#include <cassert>
#include <cmath>

int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  unsigned remaining;
  if (low == high) {
    remaining = 0;
  }
  else if (high > low) {
    remaining = log2(high - low) + 1;
  }
  else {
    remaining = log2(low - high) + 1;
  }
  CountedIntFn wrapperFunction(remaining, f, mesg);
  assert(binarySearchForZero(&wrapperFunction, low, high) == expected_ans);
}

class linearFunction : public Function<int, int> {
 private:
  int slope;
  int intercept;

 public:
  linearFunction(int mySlope, int myIntercept) : slope(mySlope), intercept(myIntercept) {}
  virtual int invoke(int arg) { return slope * arg + intercept; }
};

int main() {
  linearFunction testFunction1(2, 0);
  const char * mesg = "The binary search exceeded O(log(N)) iterations";
  check(&testFunction1, -2, 2, 0, mesg);
  check(&testFunction1, 1, 1, 1, mesg);
  check(&testFunction1, 1, 10, 1, mesg);
  check(&testFunction1, -10, -1, -2, mesg);
  check(&testFunction1, -10, 0, -1, mesg);
  check(&testFunction1, -10, 1, 0, mesg);
  check(&testFunction1, 0, 10, 0, mesg);
  check(&testFunction1, 0, 0, 0, mesg);
  linearFunction testFunction2(5, 1);
  check(&testFunction2, -10, 10, -1, mesg);
  return EXIT_SUCCESS;
}
