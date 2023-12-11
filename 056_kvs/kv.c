#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t * readLines(const char * fname, kvarray_t * array_pointer) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "There was an error opening the file %s", fname);
    free(array_pointer);
    exit(EXIT_FAILURE);
  }
  kvpair_t * myArray = NULL;
  char * curr = NULL;
  size_t line_size;
  while (getline(&curr, &line_size, f) >= 0) {
    array_pointer->array_length++;
    myArray = realloc(myArray, (array_pointer->array_length) * sizeof(*myArray));
    myArray[array_pointer->array_length - 1].key = curr;
    curr = NULL;
  }
  free(curr);
  if (fclose(f) != 0) {
    fprintf(stderr, "There was an error closing file %s", fname);
    freeKVs(array_pointer);
    exit(EXIT_FAILURE);
  }
  return myArray;
}

void splitPairs(kvarray_t * array_pointer) {
  for (size_t i = 0; i < array_pointer->array_length; i++) {
    size_t j = 0;
    int eq_counter = 0;
    while (array_pointer->kvpair[i].key[j] != '\n' &&
           array_pointer->kvpair[i].key[j] != '\0') {
      if (array_pointer->kvpair[i].key[j] == '=' && eq_counter == 0) {
        array_pointer->kvpair[i].key[j] = '\0';
        array_pointer->kvpair[i].value = &array_pointer->kvpair[i].key[j + 1];
        eq_counter++;
      }
      j++;
    }
    if (array_pointer->kvpair[i].key[j] == '\n') {
      array_pointer->kvpair[i].key[j] = '\0';
    }
  }
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  if (fname == NULL) {
    fprintf(stderr, "No file name was given");
    exit(EXIT_FAILURE);
  }
  kvarray_t * array_pointer = malloc(sizeof(*array_pointer));
  array_pointer->array_length = 0;
  array_pointer->kvpair = readLines(fname, array_pointer);
  splitPairs(array_pointer);
  return array_pointer;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t eachPair = 0; eachPair < pairs->array_length; eachPair++) {
    free(pairs->kvpair[eachPair].key);
  }
  free(pairs->kvpair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t eachPair = 0; eachPair < pairs->array_length; eachPair++) {
    printf("key = '%s' value = '%s'\n",
           pairs->kvpair[eachPair].key,
           pairs->kvpair[eachPair].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t eachPair = 0; eachPair < pairs->array_length; eachPair++) {
    if (strcmp(pairs->kvpair[eachPair].key, key) == 0) {
      return pairs->kvpair[eachPair].value;
    }
  }
  return NULL;
}
