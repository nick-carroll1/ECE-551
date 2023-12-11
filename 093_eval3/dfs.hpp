#include <vector>

#include "story.hpp"

class DFS {
  /* This object holds the non-cyclical paths through a story.
     It uses a depth-first search to find those paths.
   */
  class Node {
    /* This object tracks the path from one page to another
       given a choice during the search.
    */
   public:
    int from;
    int to;
    int choice;
    Node() : from(0), to(0), choice(0) {}
    Node(int comingFrom, int goingTo, int myChoice) :
        from(comingFrom), to(goingTo), choice(myChoice) {}
    Node(const Node & rhs) : from(rhs.from), to(rhs.to), choice(rhs.choice) {}
    Node & operator=(Node & rhs) {
      if (this != &rhs) {
        from = rhs.from;
        to = rhs.to;
        choice = rhs.choice;
      }
      return *this;
    }
    ~Node() {}
  };

 private:
  std::vector<std::vector<Node> > paths;

 public:
  void dfs(Story & myStory);
  std::ostream & printPaths(std::ostream & s);
};
