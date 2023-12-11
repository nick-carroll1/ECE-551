#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

template<typename T>
class Matrix {
 private:
  std::vector<std::vector<T> > * rows;

 public:
  Matrix() : rows(new std::vector<std::vector<T> >(0, std::vector<T>())) {}

  Matrix(int r, int c) : rows(new std::vector<std::vector<T> >(r, std::vector<T>())) {
    for (int i = 0; i < this->getRows(); i++) {
      (*rows)[i].resize(c);
    }
  }

  Matrix(const Matrix & rhs) :
      rows(new std::vector<std::vector<T> >(rhs.getRows(), std::vector<T>())) {
    for (int i = 0; i < this->getRows(); i++) {
      for (int j = 0; j < rhs.getColumns(); j++) {
        (*rows)[i].push_back(rhs[i][j]);
      }
    }
  }

  ~Matrix() { delete rows; }

  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      if (this->getRows() != rhs.getRows()) {
        delete rows;
        rows = new std::vector<std::vector<T> >(rhs.getRows(), std::vector<T>());
      }
      for (int i = 0; i < this->getRows(); i++) {
        for (int j = 0; j < rhs.getColumns(); j++) {
          (*rows)[i].push_back(rhs[i][j]);
        }
      }
    }
    return *this;
  }
  int getRows() const { return rows->size(); }
  int getColumns() const {
    if (this->getRows() > 0) {
      return (*rows)[0].size();
    }
    else {
      return 0;
    }
  }
  const std::vector<std::vector<T> > & getMatrix() const { return *rows; }
  std::vector<std::vector<T> > & getMatrix() { return *rows; }
  const std::vector<T> & operator[](int index) const {
    assert(index >= 0);
    assert(this->getRows() != 0);
    assert(index < this->getRows());
    return (*rows)[index];
  }
  std::vector<T> & operator[](int index) {
    assert(index >= 0);
    assert(this->getRows() != 0);
    assert(index < this->getRows());
    return (*rows)[index];
  }
  bool operator==(const Matrix & rhs) const {
    if (this->getRows() != rhs.getRows()) {
      return false;
    }
    if (this->getColumns() != rhs.getColumns()) {
      return false;
    }
    for (int i = 0; i < this->getRows(); i++) {
      for (int j = 0; j < this->getColumns(); j++) {
        if ((*rows)[i][j] != (*rhs.rows)[i][j]) {
          return false;
        }
      }
    }
    return true;
  }
  Matrix operator+(const Matrix & rhs) const {
    assert(this->getRows() == rhs.getRows());
    assert(this->getColumns() == rhs.getColumns());
    Matrix temp = Matrix(this->getRows(), this->getColumns());
    for (int i = 0; i < this->getRows(); i++) {
      for (int j = 0; j < this->getColumns(); j++) {
        (*temp.rows)[i][j] = (*this->rows)[i][j] + (*rhs.rows)[i][j];
      }
    }
    return temp;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  const std::vector<std::vector<T> > & myMatrix = rhs.getMatrix();
  int rows = rhs.getRows();
  int columns = rhs.getColumns();
  s << "[";
  for (int i = 0; i < rows; i++) {
    s << "{";
    for (int j = 0; j < columns; j++) {
      s << myMatrix[i][j];
      if (j != columns - 1) {
        s << ", ";
      }
    }
    s << "}";
    if (i != rows - 1) {
      s << ",\n";
    }
  }
  s << "]";
  return s;
}

#endif
