#include <stdio.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  char * myStory;
  catarray_t * myCatArray;
  int do_not_repeat;
  switch (argc) {
    case 3:
      myStory = readFile(argv[2]);
      do_not_repeat = 0;
      myCatArray = parseCatsWords(argv[1], do_not_repeat);
      break;
    case 4:
      if (strcmp(argv[1], "-n") != 0) {
        fprintf(stderr,
                "If you are passing an option, please put it before passing the file "
                "arguments\n");
        return EXIT_FAILURE;
      }
      else {
        myStory = readFile(argv[3]);
        do_not_repeat = 1;
        myCatArray = parseCatsWords(argv[2], do_not_repeat);
      }
      break;
    default:
      fprintf(
          stderr,
          "The wrong amount of arguments were received.  Please pass in the file with "
          "our mad lib words and a story "
          "input template and no additional arguments.\n");
      return EXIT_FAILURE;
  }
  parsed_story * myParsed_story = parseStory(myStory, myCatArray, do_not_repeat);
  printStory(myParsed_story);
  free(myStory);
  myCatArray->n +=
      do_not_repeat;  // Increment size of array to include dummy category if do_not_repeat flag so that this memory can be freed
  freeCatArray(myCatArray);
  return EXIT_SUCCESS;
}
