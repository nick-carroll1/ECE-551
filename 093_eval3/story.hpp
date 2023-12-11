#ifndef INCLUDED_STORY_H
#define INCLUDED_STORY_H

#include <map>
#include <sstream>
#include <string>
#include <vector>

class Story {
  /* This is a class that defines the story.
     The story contains a vector of pages,
     and a map of variables that are tracked
     during the story.
   */
  class Choice {
    /* This is a class that defines what a choice is.
       A choice consists of what the choice is (its string) 
       and its consequences (what page it takes you to).
       The choice also tracks which variables it is dependent on,
       what those variables values need to be for the choice to be available,
       and whether or not the choice is currently available based upon the variable
       value.
    */
   public:
    std::string choice;
    size_t pageReference;
    long int variableValue;
    std::string variable;
    bool available;
    Choice(std::string text, size_t page) :
        choice(text),
        pageReference(page),
        variableValue(0),
        variable(std::string()),
        available(true) {}
    Choice(std::string text, size_t page, long int value, std::string newVar) :
        choice(text),
        pageReference(page),
        variableValue(value),
        variable(newVar),
        available(false) {}
    Choice(const Choice & rhs) :
        choice(std::string(rhs.choice)),
        pageReference(rhs.pageReference),
        variableValue(rhs.variableValue),
        variable(std::string(rhs.variable)),
        available(rhs.available) {}
    Choice & operator=(const Choice & rhs) {
      if (this != &rhs) {
        choice = std::string(rhs.choice);
        pageReference = rhs.pageReference;
        variableValue = rhs.variableValue;
        variable = std::string(rhs.variable);
        available = rhs.available;
      }
      return *this;
    }
    ~Choice() {}
  };

  class Page {
    /* This is a class that defines what a page is.
       A page consists of the string for the page
       and includes a vector of potential choices
       associated with the page, and the type of page.
       Additionally the page also tracks which variables get updated
       when the page is visited, and what the variable values should be
       when the page is visited.
    */
   public:
    std::string page;
    char type;
    std::vector<Choice> choices;
    std::vector<std::string> variables;
    std::vector<long int> variableValues;
    Page(std::string text, char pageType) :
        page(text),
        type(pageType),
        choices(std::vector<Choice>()),
        variables(std::vector<std::string>()),
        variableValues(std::vector<long int>()) {}
    Page(const Page & rhs) :
        page(std::string(rhs.page)),
        type(rhs.type),
        choices(std::vector<Choice>(rhs.choices)),
        variables(std::vector<std::string>(rhs.variables)),
        variableValues(std::vector<long int>(rhs.variableValues)) {}
    Page & operator=(const Page & rhs) {
      if (this != &rhs) {
        page = std::string(rhs.page);
        type = rhs.type;
        choices = std::vector<Choice>(rhs.choices);
        variables = std::vector<std::string>(rhs.variables);
        variableValues = std::vector<long int>(rhs.variableValues);
      }
      return *this;
    }
    ~Page() {}
  };

 private:
  std::vector<Page> pages;
  std::map<std::string, long int> variables;

 public:
  Story() : pages(std::vector<Page>()), variables(std::map<std::string, long int>()) {}
  Story(const Story & rhs) :
      pages(std::vector<Page>(rhs.pages)),
      variables(std::map<std::string, long int>(rhs.variables)) {}
  Story & operator=(const Story & rhs) {
    if (this != &rhs) {
      pages = std::vector<Page>(rhs.pages);
      variables = std::map<std::string, long int>(rhs.variables);
    }
    return *this;
  }
  ~Story() {}
  void addPage(size_t pageNum, std::string page, char type);
  void addChoice(size_t pageNum, std::string choice, size_t pageReference);
  void addChoice(size_t pageNum,
                 std::string choice,
                 size_t pageReference,
                 std::string variable,
                 long int value);
  void addVariable(size_t pageNum, std::string variable, long int value);
  std::ostream & printPage(std::ostream & s, size_t pageNum);
  size_t getNumPages() const;
  size_t getNumChoices(size_t pageNum) const;
  char getPageType(size_t pageNum) const;
  size_t chooseNewPage(size_t pageNum, size_t choice) const;
  std::vector<Page> & getPages() { return pages; }
  long int findVariable(std::string variable) throw(std::out_of_range);
  void updateVariables(size_t pageNum);
  void readStory();
  friend std::ostream & operator<<(std::ostream & s, Page & mypage);
  friend std::ostream & operator<<(std::ostream & s, Choice & myChoice);
};

#endif
