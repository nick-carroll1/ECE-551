#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void printLines(std::vector<std::string> & myVector) {
  while (myVector.size() > 0) {
    std::cout << myVector[0] << "\n";
    myVector.erase(myVector.begin());
  }
}

void add_to_vector(std::istream & stream, std::vector<std::string> & myVector) {
  std::string curr;
  while (std::getline(stream, curr)) {
    myVector.push_back(curr);
  }
}

int main(int argc, char ** argv) {
  std::vector<std::string> lines;
  std::string curr;
  if (argc == 1) {
    add_to_vector(std::cin, lines);
    std::sort(lines.begin(), lines.end());
    printLines(lines);
  }
  else {
    std::ifstream file;
    for (int i = 1; i < argc; i++) {
      file.open(argv[i]);
      if (file.fail()) {
        std::cerr << "There was an error reading this file:" << argv[i] << "\n";
        return EXIT_FAILURE;
      }
      add_to_vector(file, lines);
      file.close();
      std::sort(lines.begin(), lines.end());
      printLines(lines);
    }
  }
  return EXIT_SUCCESS;
}
