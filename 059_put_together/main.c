#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "There was an error opening the file %s", filename);
    freeKVs(kvPairs);
    exit(EXIT_FAILURE);
  }
  char * curr = NULL;
  char * value = NULL;
  counts_t * counts = createCounts();
  size_t line_size;
  size_t char_num;
  while (getline(&curr, &line_size, f) >= 0) {
    char_num = 0;
    while (curr[char_num] != '\n' && curr[char_num] != '\0') {
      char_num++;
    }
    if (curr[char_num] == '\n') {
      curr[char_num] = '\0';
    }
    value = lookupValue(kvPairs, curr);
    addCount(counts, value);
    free(curr);
    curr = NULL;
  }
  free(curr);
  if (fclose(f) != 0) {
    fprintf(stderr, "There was an error closing file %s", filename);
    freeCounts(counts);
    freeKVs(kvPairs);
    exit(EXIT_FAILURE);
  }
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * pairs = readKVs(argv[1]);
  counts_t * c;
  char * outname;
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    c = countFile(argv[i], pairs);
    //compute the output file name from argv[i] (call this outName)
    outname = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outname, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "There was an error closing file %s", outname);
      free(outname);
      freeCounts(c);
      freeKVs(pairs);
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    free(outname);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(pairs);
  return EXIT_SUCCESS;
}
