#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

class Not_Found : public std::exception {
  virtual const char * what() const throw() { return "Index Location Not Found!\n"; }
};

class Tester;

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList<T>() : head(NULL), tail(NULL), size(0) {}

  LinkedList<T>(const LinkedList<T> & rhs) : head(NULL), tail(NULL), size(0) {
    int rhsSize = rhs.getSize();
    for (int i = 0; i < rhsSize; i++) {
      addBack(rhs[i]);
    }
  }

  LinkedList<T> & operator=(const LinkedList<T> & rhs) {
    if (this != &rhs) {
      LinkedList<T> temp(rhs);
      Node * tempHead = temp.head;
      Node * tempTail = temp.tail;
      int tempSize = temp.getSize();
      temp.head = head;
      temp.tail = tail;
      temp.size = size;
      head = tempHead;
      tail = tempTail;
      size = tempSize;
    }
    return *this;
  }

  ~LinkedList<T>() {
    Node * currentNode = tail;
    for (int i = 1; i < size; i++) {
      currentNode = currentNode->prev;
      delete currentNode->next;
    }
    delete head;
  }

  void addFront(const T & item) {
    Node * newNode = new Node(item, head, NULL);
    if (size == 0) {
      tail = newNode;
    }
    else {
      head->prev = newNode;
    }
    head = newNode;
    size++;
  }

  void addBack(const T & item) {
    Node * newNode = new Node(item, NULL, tail);
    if (size == 0) {
      head = newNode;
    }
    else {
      tail->next = newNode;
    }
    tail = newNode;
    size++;
  }

  Node * remove_helper(const T & item, Node * currentNode) {
    if (currentNode->data == item) {
      return currentNode;
    }
    else {
      if (currentNode == tail) {
        return NULL;
      }
      else {
        return remove_helper(item, currentNode->next);
      }
    }
  }

  bool remove(const T & item) {
    if (size == 0) {
      return false;
    }
    Node * currentNode = head;
    currentNode = remove_helper(item, currentNode);
    if (currentNode == NULL) {
      return false;
    }
    else if (size == 1) {
      head = NULL;
      tail = NULL;
    }
    else if (currentNode == head) {
      head = currentNode->next;
      currentNode->next->prev = NULL;
    }
    else if (currentNode == tail) {
      tail = currentNode->prev;
      currentNode->prev->next = NULL;
    }
    else {
      currentNode->prev->next = currentNode->next;
      currentNode->next->prev = currentNode->prev;
    }
    delete currentNode;
    size--;
    return true;
  }

  T & operator[](int index) throw(Not_Found) {
    if (index >= size || index < 0) {
      throw Not_Found();
    }
    else {
      Node * currentNode = head;
      if (index < size / 2) {
        for (int i = 0; i < index; i++) {
          currentNode = currentNode->next;
        }
      }
      else {
        currentNode = tail;
        for (int i = 0; i < size - index - 1; i++) {
          currentNode = currentNode->prev;
        }
      }
      return currentNode->data;
    }
  }

  const T & operator[](int index) const throw(Not_Found) {
    if (index >= size || index < 0) {
      throw Not_Found();
    }
    else {
      Node * currentNode = head;
      if (index < size / 2) {
        for (int i = 0; i < index; i++) {
          currentNode = currentNode->next;
        }
      }
      else {
        currentNode = tail;
        for (int i = 0; i < size - index - 1; i++) {
          currentNode = currentNode->prev;
        }
      }
      return currentNode->data;
    }
  }

  int find_helper(const T & item, Node * currentNode, int index) const {
    if (currentNode->data == item) {
      return index;
    }
    else {
      if (currentNode == tail) {
        return -1;
      }
      else {
        return find_helper(item, currentNode->next, index + 1);
      }
    }
  }

  int find(const T & item) const {
    int index;
    index = find_helper(item, head, 0);
    return index;
  }

  int getSize() const { return size; }

  friend class Tester;
};

#endif
