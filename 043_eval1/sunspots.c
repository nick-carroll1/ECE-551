#include "sunspots.h"

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

void parse_error() {
  fprintf(stderr, "There was an error parsing this line of data.");
  exit(EXIT_FAILURE);
}

void check_errno() {
  if (errno != 0) {
    parse_error();
  }
}

void check_format(char * line) {
  for (int i = 0; i < 8; i++) {
    switch (i) {
      case 4:
        if (line[i] != '-') {
          parse_error();
        }
        break;
      case 7:
        if (line[i] != ',') {
          parse_error();
        }
        break;
      default:
        if (isdigit(line[i]) == 0) {
          parse_error();
        }
        break;
    }
  }
}

ss_monthly_t parseLine(char * line) {
  // WRITE ME
  ss_monthly_t ans;
  ans.year = 0;
  ans.month = 0;
  ans.num = 0;
  check_format(line);
  /* In accordance with Man page guidance for strtol and strtod, 
     setting errno to 0 before calling these functions, 
     then checking errno to ensure it is still zero.  
     If it changes at any point during these function calls: 
     exit failure */
  errno = 0;
  ans.year = strtol(line, NULL, 10);
  check_errno();
  ans.month = strtol(&line[5], NULL, 10);
  check_errno();
  ans.num = strtod(&line[8], NULL);
  check_errno();
  if (ans.year < 0 || ans.year > 9999 || ans.month < 1 || ans.month > 12 || ans.num < 0) {
    parse_error();
  }
  return ans;
}

void meanFilter(ss_monthly_t * data, size_t n, ss_monthly_t * mean, unsigned w) {
  // WRITE ME
  if (n == 0) {
    fprintf(stderr, "Error: The size of the data passed to this function is zero.");
    exit(EXIT_FAILURE);
  }
  if (w > n) {
    fprintf(
        stderr,
        "Error: The mean filter window is larger than the data it's being applied to.");
    exit(EXIT_FAILURE);
  }
  if (w == 0) {
    fprintf(stderr, "Error The mean filter window size is zero.");
    exit(EXIT_FAILURE);
  }
  if (w % 2 != 1) {
    fprintf(stderr, "Error: The window size should be odd.");
    exit(EXIT_FAILURE);
  }
  int windowStart;
  double count;
  double sum;
  for (size_t eachData = 0; eachData < n; eachData++) {
    windowStart = ((int)eachData) - ((int)w) / 2;
    count = 0;
    sum = 0;
    for (unsigned windowPoint = 0; windowPoint < w; windowPoint++) {
      if (windowStart + windowPoint >= 0 && windowStart + windowPoint < n) {
        sum += data[windowStart + windowPoint].num;
        count++;
      }
    }
    mean[eachData].month = data[eachData].month;
    mean[eachData].year = data[eachData].year;
    if (count == 0) {
      mean[eachData].num = 0;
    }
    else {
      mean[eachData].num = sum / count;
    }
  }
}

double findLocalMax(ss_monthly_t * data, size_t n) {
  // WRITE ME
  if (n == 0) {
    fprintf(stderr, "Error: The size of the data passed to this function is zero.");
    exit(EXIT_FAILURE);
  }
  double max = 0;
  int argmax = 0;
  for (size_t eachData = 0; eachData < n; eachData++) {
    if (data[eachData].num > max) {
      max = data[eachData].num;
      argmax = eachData;
    }
  }
  return ((double)data[argmax].year) + ((double)data[argmax].month) / 12.0;
}

double calcSsPeriod(double * timeStamps, size_t n) {
  //WRITE ME
  if (n < 2) {
    fprintf(stderr, "Error: The data for this calculation is too small.");
    exit(EXIT_FAILURE);
  }
  double differences[n - 1];
  for (size_t eachTime = 1; eachTime < n; eachTime++) {
    differences[eachTime - 1] = timeStamps[eachTime] - timeStamps[eachTime - 1];
  }
  double sum = 0;
  double count = 0;
  for (size_t i = 0; i < n - 1; i++) {
    sum += differences[i];
    count++;
  }
  if (count == 0) {
    fprintf(stderr, "Error: division by zero.");
    exit(EXIT_FAILURE);
  }
  else {
    return sum / count;
  }
}
