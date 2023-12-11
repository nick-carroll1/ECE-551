#include "textParser.hpp"

#include <climits>
#include <cstdlib>
#include <fstream>
#include <string>

#include "story.hpp"

void numChecker(size_t number, char * numCheck) throw(Invalid_Number) {
  /* Error Checking to ensure a number is Valid
   */
  if (number == ULONG_MAX || numCheck[0] != '\0') {
    throw Invalid_Number();
  }
}

void TextParser::addPage(std::string line,
                         Story & story,
                         std::string path,
                         size_t ampersandLocation) {
  /* This is the Code for a Page definition
	     */
  char * numCheck = NULL;
  size_t page = strtoul(line.substr(0, ampersandLocation).c_str(), &numCheck, 10);
  /* Error Checking
	     */
  numChecker(page, numCheck);
  if (page != story.getPages().size()) {
    throw Invalid_Number();
  }
  char type = line.at(ampersandLocation + 1);
  switch (type) {
      /* Error check to ensure a page type is W, L, or N
	       */
    case 'W':
      break;
    case 'L':
      break;
    case 'N':
      break;
    default:
      throw Invalid_Page_Type();
  }
  std::ifstream pageStream(
      std::string(path).append("/").append(line.substr(ampersandLocation + 3)).c_str());
  if (pageStream.fail()) {
    throw File_Error();
  }
  std::string pageText;
  std::getline(pageStream, pageText, '\0');
  if (pageStream.fail()) {
    throw File_Error();
  }
  pageStream.close();
  story.addPage(page, pageText, type);
}

void TextParser::addChoice(std::string line, Story & story) {
  /* This is the Code for a Choice definition
   */
  char * numCheck = NULL;
  size_t firstColon = line.find(":", 0);
  if (firstColon == std::string::npos) {
    throw Bad_Format();
  }
  size_t secondColon = line.find(":", firstColon + 1);
  if (firstColon == std::string::npos) {
    throw Bad_Format();
  }
  size_t page = strtoul(line.substr(0, firstColon).c_str(), &numCheck, 10);
  numChecker(page, numCheck);
  if (page >= story.getPages().size()) {
    throw Invalid_Number();
  }
  size_t pageReference = strtoul(
      line.substr(firstColon + 1, secondColon - firstColon - 1).c_str(), &numCheck, 10);
  numChecker(pageReference, numCheck);
  if (story.getPages()[page].type != 'N') {
    throw Invalid_Page_Type();
  }
  std::string choice = std::string(line, secondColon + 1);
  story.addChoice(page, choice, pageReference);
}
void TextParser::addChoice(std::string line, Story & story, size_t bracketLocation) {
  /* This is the code for parsing a Choice that is
     dependent on a variable.
  */
  if (bracketLocation == std::string::npos) {
    throw Bad_Format();
  }
  char * numCheck = NULL;
  size_t page = strtoul(line.substr(0, bracketLocation).c_str(), &numCheck, 10);
  numChecker(page, numCheck);
  if (page >= story.getPages().size()) {
    throw Invalid_Number();
  }
  size_t equalSignLocation = line.find("=", bracketLocation);
  if (equalSignLocation == std::string::npos) {
    throw Bad_Format();
  }
  std::string variable =
      line.substr(bracketLocation + 1, equalSignLocation - bracketLocation - 1);
  size_t secondBracketLocation = line.find("]", equalSignLocation);
  if (secondBracketLocation == std::string::npos) {
    throw Bad_Format();
  }
  long int value = strtol(
      line.substr(equalSignLocation + 1, secondBracketLocation - equalSignLocation - 1)
          .c_str(),
      &numCheck,
      10);
  size_t firstColon = line.find(":", 0);
  if (firstColon == std::string::npos) {
    throw Bad_Format();
  }
  size_t secondColon = line.find(":", firstColon + 1);
  if (secondColon == std::string::npos) {
    throw Bad_Format();
  }
  size_t pageReference = strtoul(
      line.substr(firstColon + 1, secondColon - firstColon - 1).c_str(), &numCheck, 10);
  std::string choice = std::string(line, secondColon + 1);
  numChecker(pageReference, numCheck);
  if (story.getPages()[page].type != 'N') {
    throw Invalid_Page_Type();
  }
  story.addChoice(page, choice, pageReference, variable, value);
}

void TextParser::addVariable(std::string line, Story & story, size_t dollarSignLocation) {
  /* This is the code for parsing a Variable definition
   */
  if (dollarSignLocation == std::string::npos) {
    throw Bad_Format();
  }
  char * numCheck = NULL;
  size_t pageReference =
      strtoul(line.substr(0, dollarSignLocation).c_str(), &numCheck, 10);
  size_t equalSignLocation = line.find("=", dollarSignLocation);
  if (equalSignLocation == std::string::npos) {
    throw Bad_Format();
  }
  std::string variable =
      line.substr(dollarSignLocation + 1, equalSignLocation - dollarSignLocation - 1);
  long int value = strtol(line.substr(equalSignLocation + 1).c_str(), &numCheck, 10);
  story.addVariable(pageReference, variable, value);
}

void TextParser::parseFile(char * filepath, Story & story) {
  /* This function parses a story.txt file based on the rules 
     of the README.
  */
  std::string path(filepath);
  std::ifstream file(std::string(path).append("/story.txt").c_str());
  if (file.fail()) {
    throw File_Error();
  }
  size_t ampersandLocation;
  std::string line;
  while (file.good()) {
    std::getline(file, line);
    if (line.size() > 0) {
      ampersandLocation = line.find("@");
      if (ampersandLocation != std::string::npos) {
        try {
          addPage(line, story, path, ampersandLocation);
        }
        catch (std::exception & e) {
          file.close();
          throw;
        }
      }
      else {
        size_t dollarSignLocation = line.find("$");
        if (dollarSignLocation != std::string::npos) {
          try {
            addVariable(line, story, dollarSignLocation);
          }
          catch (std::exception & e) {
            file.close();
            throw;
          }
        }
        else {
          size_t bracketLocation = line.find("[");
          if (bracketLocation != std::string::npos) {
            try {
              addChoice(line, story, bracketLocation);
            }
            catch (std::exception & e) {
              file.close();
              throw;
            }
          }
          else {
            try {
              addChoice(line, story);
            }
            catch (std::exception & e) {
              file.close();
              throw;
            }
          }
        }
      }
    }
  }
  file.close();
}
