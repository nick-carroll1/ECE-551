#include "node.h"

Node * buildTree(uint64_t * counts) {
  priority_queue_t pq;
  Node * tempLeft;
  Node * tempRight;
  for (size_t eachChar = 0; eachChar < 257; eachChar++) {
    if (counts[eachChar] != 0) {
      pq.push(new Node(eachChar, counts[eachChar]));
    }
  }
  while (pq.size() > 1) {
    tempLeft = pq.top();
    pq.pop();
    tempRight = pq.top();
    pq.pop();
    pq.push(new Node(tempLeft, tempRight));
  }
  if (pq.size() == 1) {
    return pq.top();
  }
  else {
    return NULL;
  }
}
