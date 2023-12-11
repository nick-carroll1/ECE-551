#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_test(int * array, size_t n, size_t expected_ans) {
  size_t calculated_ans = maxSeq(array, n);
  if (calculated_ans != expected_ans) {
    printf("When the maxSeq function was applied to this array, the expected answer was "
           "%zu, but %zu was returned instead.",
           expected_ans,
           calculated_ans);
    exit(EXIT_FAILURE);
  }
}

int main() {
  int myArray[1] = {0};
  run_test(myArray, 0, 0);
  int myArray2[2] = {0};
  run_test(myArray2, 1, 1);
  run_test(myArray2, 2, 1);
  //run_test(myArray2, 3, 1);
  //int myArray3[4] = {0, 1, 2, 3};
  //run_test(myArray3, 4, 4);
  //int myArray4[4] = {'#', '$', '%', '&'};
  //run_test(myArray4, 4, 4);
  int myArray5[5] = {1, 2, 1, 2, 3};
  run_test(myArray5, 5, 3);
  int myArray6[4] = {0, 1, 2, 2};
  run_test(myArray6, 4, 3);
  int myArray7[5] = {1, 2, 2, 2, 3};
  run_test(myArray7, 5, 2);
  //int myArray8[10] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  //run_test(myArray8, 10, 4);
  int myArray9[5] = {1, 2, 3, 1, 2};
  run_test(myArray9, 5, 3);
  int myArray10[1] = {-0x80000000};
  run_test(myArray10, 3, 2);
  //double myArray11[4] = {9.5, 55, 200, 1000};
  //int * bad_cast = (int *)&myArray11[0];
  //run_test(bad_cast, 4, 2);
  printf("All tests were a success.\n");
  return EXIT_SUCCESS;
}
