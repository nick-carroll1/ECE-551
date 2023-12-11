#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  void testAgainstSelf(const IntList & il) {
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    int size = il.getSize();
    assert(size >= 0);
    IntList::Node * currentFront = il.head;
    for (int i = 0; i < size; i++) {
      if (i > 0) {
        currentFront = currentFront->next;
      }
      IntList::Node * currentBack = il.tail;
      for (int j = 1; j < size - i; j++) {
        currentBack = currentBack->prev;
      }
      assert(currentFront == currentBack);
      assert(il[i] == currentFront->data);
      assert(il[i] == currentBack->data);
    }
  }
  // example of another method you might want to write
  void compareIntLists(IntList & il, IntList & il2) {
    assert(il.head != il2.head);
    assert(il.head->data == il2.head->data);
    assert(il.tail != il2.tail);
    assert(il.tail->data == il2.tail->data);
    for (int i = 0; i < il.getSize(); i++) {
      assert(il[i] == il2[i]);
    }
  }
  void testAddFront() {
    IntList il;
    for (int i = 0; i < 10; i++) {
      il.addFront(i);
    }
    testAgainstSelf(il);
    IntList il2(il);
    compareIntLists(il, il2);
    IntList il3 = il;
    compareIntLists(il, il3);
    il.remove(9);
    for (int i = 0; i < 9; i++) {
      assert(il[i] == 8 - i);
    }
    for (int i = 0; i < 10; i++) {
      assert(il2[i] == 9 - i);
    }
    for (int i = 0; i < 10; i++) {
      assert(il3[i] == 9 - i);
    }
    il.remove(0);
    for (int i = 0; i < 8; i++) {
      assert(il[i] == 8 - i);
    }
    testAgainstSelf(il);
    il.remove(5);
    il3 = il;
    for (int i = 0; i < 7; i++) {
      if (il[i] > 5) {
        assert(il[i] == 8 - i);
      }
      else {
        assert(il[i] == 7 - i);
      }
    }
    for (int i = 0; i < 10; i++) {
      assert(il2[i] == 9 - i);
    }
    for (int i = 0; i < 7; i++) {
      if (il3[i] > 5) {
        assert(il3[i] == 8 - i);
      }
      else {
        assert(il3[i] == 7 - i);
      }
    }
    testAgainstSelf(il);
    testAgainstSelf(il2);
    testAgainstSelf(il3);
    IntList il4(il3);
    for (int i = 0; i < 7; i++) {
      if (il4[i] > 5) {
        assert(il4[i] == 8 - i);
      }
      else {
        assert(il4[i] == 7 - i);
      }
    }
  }

  void testAddBack() {
    IntList il;
    for (int i = 0; i < 10; i++) {
      il.addBack(i);
    }
    testAgainstSelf(il);
    IntList il2(il);
    compareIntLists(il, il2);
    IntList il3 = il;
    compareIntLists(il, il3);
    il.remove(9);
    for (int i = 0; i < 9; i++) {
      assert(il[i] == i);
    }
    il.remove(0);
    for (int i = 0; i < 8; i++) {
      assert(il[i] == i + 1);
    }
    testAgainstSelf(il);
    il3 = il;
    il.remove(5);
    for (int i = 0; i < il.getSize(); i++) {
      if (il[i] > 5) {
        assert(il[i] == i + 2);
      }
      else {
        assert(il[i] == i + 1);
      }
    }
    for (int i = 0; i < il3.getSize(); i++) {
      assert(il3[i] == i + 1);
    }
    testAgainstSelf(il);
  }
  void testRemove1() {
    IntList il;
    assert(il.remove(0) == false);
    for (int i = 0; i < 3; i++) {
      il.addBack(i);
    }
    IntList il2(il);
    IntList il3(il);
    assert(il.remove(0) == true);
    for (int i = 0; i < il.getSize(); i++) {
      assert(il[i] == i + 1);
    }
    assert(il2.remove(1) == true);
    assert(il2[0] == 0);
    assert(il2[1] == 2);
    assert(il3.remove(2) == true);
    assert(il3[0] == 0);
    assert(il3[1] == 1);
    IntList il4;
    for (int i = 0; i < 3; i++) {
      il4.addFront(i);
    }
    IntList il5(il4);
    IntList il6(il4);
    assert(il4.remove(0) == true);
    assert(il4[0] == 2);
    assert(il4[1] == 1);
    assert(il5.remove(1) == true);
    assert(il5[0] == 2);
    assert(il5[1] == 0);
    assert(il6.remove(2) == true);
    assert(il6[0] == 1);
    assert(il6[1] == 0);
    IntList il7;
    il7.addFront(1);
    il7.addFront(2);
    il7.addFront(1);
    assert(il7.remove(1) == true);
    assert(il7[0] == 2);
    assert(il7[1] == 1);
    assert(il7.remove(10) == false);
    assert(il7.remove(1) == true);
    assert(il7[0] == 2);
    assert(il7.remove(2) == true);
    assert(il7.head == NULL);
    assert(il7.tail == NULL);
  }
  // many more tester methods
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testRemove1();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
