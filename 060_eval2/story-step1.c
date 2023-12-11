#include <stdio.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,
            "The wrong amount of arguments were received.  Please pass in the story "
            "input template and no additional arguments.\n");
    return EXIT_FAILURE;
  }
  else {
    char * myStory = readFile(argv[1]);
    parsed_story * myParsed_story = parseStory(myStory, NULL, 0);
    printStory(myParsed_story);
    free(myStory);
    return EXIT_SUCCESS;
  }
}
