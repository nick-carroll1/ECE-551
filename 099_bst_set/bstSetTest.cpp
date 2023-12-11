#include <cassert>
#include <cstdlib>
#include <iostream>

#include "bstset.h"

int main() {
  BstSet<int> set;
  BstSet<int> setCopy(set);
  set.remove(10);
  assert(set.contains(10) == false);
  set.add(50);
  assert(set.contains(50) == true);
  set.remove(10);
  set.add(5);
  set.add(10);
  assert(set.contains(10) == true);
  set.add(5);
  assert(set.contains(5) == true);
  set.remove(5);
  set.add(10);
  assert(set.contains(10) == true);
  set.remove(10);
  set.add(50);
  set.add(30);
  set.add(60);
  set.add(100);
  set.add(150);
  set.add(95);
  set.add(90);
  set.remove(60);
  set.remove(60);
  set.remove(90);
  set.remove(50);
  set.remove(75);
  set.remove(100);
  set.remove(30);
  set.remove(30);
  set.remove(150);
  for (int i = 0; i < 10; i++) {
    set.add(50 + i * 8);
    set.add(50 + i * 4);
    set.add(50 - i * 8);
    set.add(50 - i * 3);
  }
  set.remove(58);
  set.remove(50 - 2 * 3);
  set.remove(50 - 8);
  set.remove(50);
  set.remove(50 - 5 * 3);
  set.remove(50 - 10 * 3);
  BstSet<int> setCopy2(set);
  return EXIT_SUCCESS;
}
