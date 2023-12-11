#include <stdio.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,
            "The wrong amount of arguments were received.  Please pass in the file with "
            "the mad lib words"
            "and no additional arguments.\n");
    return EXIT_FAILURE;
  }
  else {
    catarray_t * myCatArray = parseCatsWords(argv[1], 0);
    printWords(myCatArray);
    freeCatArray(myCatArray);
    return EXIT_SUCCESS;
  }
}
