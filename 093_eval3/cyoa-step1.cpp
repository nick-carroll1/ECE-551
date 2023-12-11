#include <cstdlib>
#include <iostream>

#include "story.hpp"
#include "textParser.hpp"

int main(int argc, char ** argv) {
  /* This is the program that prints Step 1
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
  size_t pages = myStory.getPages().size();
  for (size_t i = 0; i < pages; i++) {
    std::cout << "Page " << i << "\n"
              << "==========\n";
    myStory.printPage(std::cout, i);
  }
  return EXIT_SUCCESS;
}
