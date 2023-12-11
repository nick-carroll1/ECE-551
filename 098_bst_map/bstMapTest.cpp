#include <cassert>
#include <cstdlib>
#include <iostream>

#include "bstmap.h"

int main() {
  BstMap<int, int> myMap;
  BstMap<int, int> mapCopy(myMap);
  myMap.remove(10);
  myMap.add(5, 10);
  myMap.add(10, 15);
  assert(myMap.lookup(5) == 10);
  assert(myMap.lookup(10) == 15);
  myMap.add(5, -10);
  assert(myMap.lookup(5) == -10);
  myMap.remove(5);
  myMap.add(10, 20);
  assert(myMap.lookup(10) == 20);
  myMap.remove(10);
  myMap.add(50, 51);
  myMap.add(30, 31);
  myMap.add(60, 61);
  myMap.add(100, 101);
  myMap.add(150, 151);
  myMap.add(95, 96);
  myMap.add(90, 91);
  myMap.add(85, 86);
  myMap.add(75, 76);
  myMap.add(80, 81);
  myMap.remove(60);
  myMap.remove(60);
  myMap.remove(90);
  myMap.remove(50);
  myMap.remove(75);
  myMap.remove(100);
  myMap.remove(30);
  myMap.remove(30);
  myMap.remove(150);
  for (int i = 0; i < 10; i++) {
    myMap.add(50 + i * 8, i * 3);
    myMap.add(50 + i * 4, i * -5);
    myMap.add(50 - i * 8, i * -4);
    myMap.add(50 - i * 3, i * 5);
  }
  myMap.remove(58);
  myMap.remove(50 - 2 * 3);
  myMap.remove(50 - 8);
  myMap.remove(50);
  myMap.remove(50 - 5 * 3);
  myMap.remove(50 - 10 * 3);
  try {
    myMap.lookup(-2000);
  }
  catch (Missing_Key & e) {
    std::cout << "Caught the error\n";
  }
  for (int i = 0; i < 10; i++) {
    myMap.remove(50 - i * 8);
  }
  assert(myMap.lookup(80) == 81);
  assert(myMap.lookup(85) == 86);
  for (int i = 0; i < 10; i++) {
    mapCopy.add(50 + i * 8, i * 3);
    mapCopy.add(50 + i * 4, i * -5);
    mapCopy.add(50 - i * 8, i * -4);
    mapCopy.add(50 - i * 3, i * 5);
  }
  mapCopy.remove(58);
  mapCopy.remove(50 - 2 * 3);
  BstMap<int, int> mapCopy2(mapCopy);
  mapCopy.remove(50 - 8);
  mapCopy2.remove(50);
  mapCopy.remove(50 - 5 * 3);
  mapCopy2.remove(50 - 10 * 3);
  return EXIT_SUCCESS;
}
