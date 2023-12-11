#include "story.hpp"

#include <iostream>

std::ostream & Story::printPage(std::ostream & s, size_t pageNum) {
  /* This is the function to print a story's page.
   */
  s << pages[pageNum];
  return s;
}

std::ostream & operator<<(std::ostream & s, Story::Choice & myChoice) {
  /* This is the function that prints a page's choice.
   */
  if (myChoice.available == true) {
    s << myChoice.choice << "\n";
  }
  else {
    s << "<UNAVAILABLE>\n";
  }
  return s;
}

std::ostream & operator<<(std::ostream & s, Story::Page & myPage) {
  /* This is the function that tells the << operator how to print 
     a story's page.
  */
  s << myPage.page << "\n";
  if (myPage.type == 'N') {
    s << "What would you like to do?\n\n";
    int numChoices = myPage.choices.size();
    for (int i = 0; i < numChoices; i++) {
      s << " " << i + 1 << ". " << myPage.choices[i];
    }
  }
  else if (myPage.type == 'W') {
    s << "Congratulations! You have won. Hooray!\n";
  }
  else if (myPage.type == 'L') {
    s << "Sorry, you have lost. Better luck next time!\n\n";
  }
  return s;
}

size_t Story::getNumPages() const {
  /* This function returns the number of pages in a story.
   */
  return pages.size();
}

size_t Story::getNumChoices(size_t pageNum) const {
  /* This function returns the number of choices on a page.
   */
  return pages[pageNum].choices.size();
}

char Story::getPageType(size_t pageNum) const {
  /* This function returns a page type.
   */
  return pages[pageNum].type;
}

size_t Story::chooseNewPage(size_t pageNum, size_t choice) const {
  /* This function selects the next page based upon a choice.
   */
  return pages[pageNum].choices[choice - 1].pageReference;
}

void Story::addPage(size_t pageNum, std::string page, char type) {
  /* This function adds a page to a story.
   */
  pages.push_back(Page(page, type));
}

void Story::addChoice(size_t pageNum, std::string page, size_t pageReference) {
  /* This function adds a choice to a story.
   */
  pages[pageNum].choices.push_back(Choice(page, pageReference));
}

void Story::addChoice(size_t pageNum,
                      std::string page,
                      size_t pageReference,
                      std::string variable,
                      long int value) {
  /* This function adds a choice to a story 
     for choices that are dependent on variables.
   */
  pages[pageNum].choices.push_back(Choice(page, pageReference, value, variable));
}

void Story::addVariable(size_t pageNum, std::string variable, long int value) {
  /* This function adds a variable to a story.
   */
  variables.insert(std::pair<std::string, long int>(variable, 0));
  pages[pageNum].variables.push_back(variable);
  pages[pageNum].variableValues.push_back(value);
}

long int Story::findVariable(std::string variable) throw(std::out_of_range) {
  /* This function returns the variables value from its key.
   */
  long int value;
  try {
    value = variables.at(variable);
  }
  catch (std::out_of_range & e) {
    throw;
  }
  return value;
}

void Story::updateVariables(size_t pageNum) {
  /* This function updates the variables when
     a new page is visited.
  */
  Page * page = &pages[pageNum];
  for (size_t i = 0; i < page->variables.size(); i++) {
    variables[page->variables[i]] = page->variableValues[i];
  }
  for (size_t i = 0; i < page->choices.size(); i++) {
    if (page->choices[i].variable.size() > 0) {
      page->choices[i].available =
          variables[page->choices[i].variable] == page->choices[i].variableValue;
    }
  }
}

void Story::readStory() {
  /* This function reads the story and 
     interacts with the user.
  */
  size_t page = 0;
  size_t choice;
  Choice * thisChoice;
  do {
    updateVariables(page);
    printPage(std::cout, page);
    do {
      std::cin >> choice;
      thisChoice = &pages[page].choices[choice - 1];
      if (choice > getNumChoices(page) || choice == 0) {
        std::cout << "That is not a valid choice, please try again\n";
      }
      else if (thisChoice->available == false) {
        std::cout << "That choice is not available at this time, please try again\n";
      }
    } while (choice > getNumChoices(page) || choice == 0 ||
             thisChoice->available == false);
    page = chooseNewPage(page, choice);

  } while (getPageType(page) == 'N');
  printPage(std::cout, page);
}
