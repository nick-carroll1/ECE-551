#include <stdio.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr,
            "The wrong amount of arguments were received.  Please pass in the file with "
            "our mad lib words and a story "
            "input template and no additional arguments.\n");
    return EXIT_FAILURE;
  }
  else {
    char * myStory = readFile(argv[2]);
    catarray_t * myCatArray = parseCatsWords(argv[1], 0);
    parsed_story * myParsed_story = parseStory(myStory, myCatArray, 0);
    printStory(myParsed_story);
    free(myStory);
    freeCatArray(myCatArray);
    return EXIT_SUCCESS;
  }
}
