#ifndef INCLUDED_TEXTPARSER_H
#define INCLUDED_TEXTPARSER_H

#include "story.hpp"

class Invalid_Number : public std::exception {
  /* This is an exception for an invalid number.
   */
  virtual const char * what() const throw() { return "Number outside acceptable range"; }
};

class Invalid_Page_Type : public std::exception {
  /* This is an exception for an invalid page type.
   */
  virtual const char * what() const throw() {
    return "This line has an invalid page type";
  }
};

class Bad_Format : public std::exception {
  /* This is an exception for an issue with the format of a line.
   */
  virtual const char * what() const throw() {
    return "This line has a necessary delimiter at the end of it";
  }
};

class File_Error : public std::exception {
  /* This is an exception for an error with the file.
   */
  virtual const char * what() const throw() { return "There was an error with the file"; }
};

class TextParser {
  /* This is a class that reads a file and 
     adds the information to a story.
  */
 public:
  void parseFile(char * filename, Story & story);
  void addPage(std::string line,
               Story & story,
               std::string path,
               size_t ampersandLocation);
  void addChoice(std::string line, Story & story);
  void addChoice(std::string line, Story & story, size_t bracketLocation);
  void addVariable(std::string line, Story & story, size_t dollarSignLocation);
};

#endif
