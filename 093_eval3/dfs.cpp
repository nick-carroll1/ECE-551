#include "dfs.hpp"

#include <set>
#include <stack>

void DFS::dfs(Story & myStory) {
  /* This is a depth-first search function to find the non-cyclical
     paths in a story.
  */
  std::vector<Node> currentPath;
  std::stack<Node> todo;
  std::set<int> visited;
  Node currentNode;
  int currentPage = 0;
  int potentialPage;
  todo.push(currentNode);
  while (todo.empty() == false) {
    currentNode = todo.top();
    currentPage = currentNode.to;
    todo.pop();
    visited.insert(currentPage);
    while (currentPath.size() > 0 && currentNode.from != currentPath.back().to) {
      currentPath.pop_back();
    }
    if (currentNode.to != 0) {
      currentPath.push_back(currentNode);
    }
    if (myStory.getPageType(currentPage) != 'W') {
      for (size_t i = 0; i < myStory.getNumChoices(currentPage); i++) {
        potentialPage = myStory.chooseNewPage(currentPage, i + 1);
        if (visited.find(potentialPage) == visited.end()) {
          todo.push(Node(currentPage, potentialPage, i + 1));
        }
      }
    }
    else {
      paths.push_back(currentPath);
      currentPath.pop_back();
    }
  }
}

std::ostream & DFS::printPaths(std::ostream & s) {
  /* This function prints all of the non-cyclical paths in a story.
   */
  for (size_t i = 0; i < paths.size(); i++) {
    for (size_t j = 0; j < paths[i].size(); j++) {
      s << paths[i][j].from << "(" << paths[i][j].choice << "), ";
    }
    s << paths[i][paths[i].size() - 1].to << "(win)\n";
  }
  return s;
}
