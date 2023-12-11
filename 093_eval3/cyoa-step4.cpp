#include <cstdlib>
#include <iostream>

#include "story.hpp"
#include "textParser.hpp"

int main(int argc, char ** argv) {
  /* This is the program that runs Step 4
   */
  if (argc != 2) {
    std::cerr << "Inappropriate number of arguments were provided.";
    return EXIT_FAILURE;
  }
  Story myStory = Story();
  TextParser myParser;
  try {
    myParser.parseFile(argv[1], myStory);
  }
  catch (std::exception & e) {
    std::cerr << e.what();
    return EXIT_FAILURE;
  }
  myStory.readStory();
  return EXIT_SUCCESS;
}
