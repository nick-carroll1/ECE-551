#ifndef __SUNSPOTS_H__
#define __SUNSPOTS_H__

#include <stdio.h>

struct ss_monthly_tag {
  double num;
  unsigned year;
  unsigned month;
};
typedef struct ss_monthly_tag ss_monthly_t;

ss_monthly_t parseLine(char * line);

void meanFilter(ss_monthly_t * data, size_t n, ss_monthly_t * mean, unsigned w);

double findLocalMax(ss_monthly_t * data, size_t n);

double calcSsPeriod(double * timeStamps, size_t n);

#endif
