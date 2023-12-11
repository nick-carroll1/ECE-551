#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  if (sym != NO_SYM) {
    assert(left == NULL);
    assert(right == NULL);
    theMap[sym] = b;
  }
  else {
    assert(left != NULL);
    assert(right != NULL);
    left->buildMap(b.plusZero(), theMap);
    right->buildMap(b.plusOne(), theMap);
  }
}
