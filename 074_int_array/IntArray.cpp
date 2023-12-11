#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}
IntArray::IntArray(int n) : data(NULL), numElements(n) {
  data = new int[numElements];
}

IntArray::IntArray(const IntArray & rhs) : data(NULL), numElements(rhs.numElements) {
  data = new int[numElements];
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}

IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    numElements = rhs.numElements;
    int * temp = new int[numElements];
    for (int i = 0; i < numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    data = temp;
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index < numElements);
  return data[index];
}

int & IntArray::operator[](int index) {
  assert(index < numElements);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (*this == rhs) {
    return false;
  }
  else {
    return true;
  }
}

IntArray IntArray::operator+(const IntArray & rhs) const {
  assert(numElements == rhs.numElements);
  IntArray temp = IntArray(*this);
  for (int i = 0; i < numElements; i++) {
    temp.data[i] += rhs.data[i];
  }
  return temp;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int i = 0; i < rhs.size(); i++) {
    s << rhs[i];
    if (i < rhs.size() - 1) {
      s << ", ";
    }
  }
  s << "}";
  return s;
}
