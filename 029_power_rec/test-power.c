#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned calculated_value = power(x, y);
  if (calculated_value != expected_ans) {
    printf("Error: power function this the output of power(%d, %d) is %d, but it should "
           "be %d",
           x,
           y,
           calculated_value,
           expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main() {
  run_check(0, 0, 1);
  run_check(0, 1, 0);
  run_check(10, 0, 1);
  run_check(1, 10, 1);
  run_check(2, 7, 128);
  run_check(10, 3, 1000);
  run_check(-1, 1, -1);
  run_check('2', 2, 2500);
  printf("All of the test cases were a success.\n");
  return EXIT_SUCCESS;
}
