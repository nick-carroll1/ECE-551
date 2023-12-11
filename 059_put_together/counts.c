#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * count_array = malloc(sizeof(*count_array));
  count_array->array_size = 0;
  return count_array;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (c->array_size == 0) {
    c->array_size++;
    c->array_pointer = malloc(sizeof(*c->array_pointer));
    c->array_pointer->string = name;
    c->array_pointer->count = 1;
  }
  else {
    for (size_t eachString = 0; eachString < c->array_size; eachString++) {
      if (name == NULL || c->array_pointer[eachString].string == NULL) {
        if (c->array_pointer[eachString].string == name) {
          c->array_pointer[eachString].count++;
          break;
        }
      }
      else {
        if (strcmp(c->array_pointer[eachString].string, name) == 0) {
          c->array_pointer[eachString].count++;
          break;
        }
      }
      if (eachString == c->array_size - 1) {
        c->array_size++;
        c->array_pointer =
            realloc(c->array_pointer, c->array_size * sizeof(*c->array_pointer));
        c->array_pointer[c->array_size - 1].string = name;
        c->array_pointer[c->array_size - 1].count = 1;
        break;
      }
    }
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  int null_flag = -1;
  for (size_t i = 0; i < c->array_size; i++) {
    if (c->array_pointer[i].string == NULL) {
      null_flag = i;
      continue;
    }
    fprintf(outFile, "%s: %d\n", c->array_pointer[i].string, c->array_pointer[i].count);
  }
  if (null_flag > -1) {
    fprintf(outFile, "<unknown>: %d\n", c->array_pointer[null_flag].count);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  /*
  for (size_t i = 0; i < c->array_size; i++) {
    free(c->array_pointer[i].string);
  }
  */
  free(c->array_pointer);
  free(c);
}
