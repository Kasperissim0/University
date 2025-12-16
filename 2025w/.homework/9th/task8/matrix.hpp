#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
#include <cassert>
#include "complex.hpp"

using namespace std;

class Matrix {
  private:
    size_t rowAmount, columnAmount;
    vector<vector<Complex>> values;
  public:
    Matrix() {
      values = {{}};
      rowAmount = columnAmount = 0;
    }
    Matrix(vector<vector<Complex>> values) : values{values} {
      rowAmount = values.size(), columnAmount = values.at(0).size();
    }
    vector<Complex> getRow(const size_t row) const {
      return values.at(row);
    }
    vector<Complex> getColumn(const size_t column) const {
      vector<Complex> construct;
      for (size_t i = 0; i < rowAmount; ++i) construct.push_back(values.at(i).at(column));
      return construct;
    }
    Complex getEntry(const size_t row = 0, const size_t column = 0) const {
      return values.at(row).at(column);
    }
    size_t getRowAmount() const {
      return rowAmount;
    }
    size_t getColumnAmount() const {
      return columnAmount;
    }
    Matrix setValues(vector<vector<Complex>> values) {
      this->values = values, this->rowAmount = values.size(), this->columnAmount = values.at(0).size();
      return *this;
    }
    Matrix transpose() {
      Matrix construct; vector<vector<Complex>> newValues;
      for (size_t a = 0; a < columnAmount; ++a) newValues.push_back(getColumn(a));
      return construct.setValues(newValues);
    }
    Matrix conjugate() {
      Matrix construct; vector<vector<Complex>> newValues;
      for (size_t a = 0; a < rowAmount; ++a) {
        vector<Complex> temp = {};
        for (size_t b = 0; b < columnAmount; ++b) {
          temp.push_back(values.at(a).at(b).conj());
        } newValues.push_back(temp);
      }
      return construct.setValues(newValues);
    }
    
};

inline ostream& operator<< (ostream& o, const vector<Complex> v) {
  for (size_t i = 0; i < v.size(); ++i) {
    o << left << setw(8) << (i == 0 ? " | " : "");
    o << left << setw(8) << v.at(i);
    o << right << setw(8) << " | ";
  }
  return o;
}
inline ostream& operator<< (ostream& o, const Matrix m) {
  for (size_t i = 0; i < m.getRowAmount(); ++i) o << m.getRow(i) << endl;
  return o;
}
Matrix operator+(const Matrix& m) {
  return m;
}
Matrix operator+(const Matrix& m1, const Matrix& m2) {
  if (m1.getRowAmount() != m2.getRowAmount() || m1.getColumnAmount() != m2.getColumnAmount()) 
    throw runtime_error("Invalid Matrix Dimensions For Operation ("
                                                                    + to_string(m1.getRowAmount()) + "x"
                                                                    + to_string(m1.getColumnAmount()) + " AND "
                                                                    + to_string(m2.getRowAmount()) + "x"
                                                                    + to_string(m2.getColumnAmount()) + ")" );
  Matrix construct; vector<vector<Complex>> values;
  for (size_t a = 0; a < m1.getRowAmount(); ++a) {
    vector<Complex> temp = {}; 
    for (size_t b = 0; b < m1.getColumnAmount(); ++b) {
      temp.push_back(m1.getEntry(a, b) + m2.getEntry(a, b));
    }
    values.push_back(temp);
  }
  return construct.setValues(values);
}
Matrix operator-(const Matrix& m) {
  Matrix construct; vector<vector<Complex>> values;
  for (size_t a = 0; a < m.getRowAmount(); ++a) {
    vector<Complex> temp = {};
    for (size_t b = 0; b < m.getColumnAmount(); ++b) {
      temp.push_back(-m.getEntry(a, b));
    }
    values.push_back(temp);
  }
  return construct.setValues(values);
}
Matrix operator-(const Matrix& m1, const Matrix& m2) {
  return (m1 + -m2);
}
Matrix operator*(const Matrix& m1, const Matrix& m2) {
  if (m1.getColumnAmount() != m2.getRowAmount()) 
    throw runtime_error("Invalid Matrix Dimensions For Operation ("
                                                                    + to_string(m1.getRowAmount()) + "x"
                                                                    + to_string(m1.getColumnAmount()) + " AND "
                                                                    + to_string(m2.getRowAmount()) + "x"
                                                                    + to_string(m2.getColumnAmount()) + ")" );
  const size_t newRows = m1.getRowAmount(), newColumns = m2.getColumnAmount(), size = m1.getColumnAmount(); assert(size == m2.getRowAmount());
  Matrix construct; vector<vector<Complex>> values;
  // clog << "m1 is: " << m1.getRowAmount() << "x" << m1.getColumnAmount() << endl
  //      << "m2 is: " << m2.getRowAmount() << "x" << m2.getColumnAmount() << endl;
  for (size_t a = 0; a < newRows; ++a) {
    vector<Complex> temp = {};
    for (size_t b = 0; b < newColumns; ++b) {
      Complex value = {};
      for (size_t c = 0; c < size; ++c) {
        // clog << "Acessing:" << endl 
        //      << "- m1.at(" << c << ").at(" << b << ") = " << m1.getEntry(c, b) << endl
        //      << "- m2.at(" << b << ").at(" << c << ") = " << m2.getEntry(b, c) << endl;
        value += (m1.getEntry(a, c) * m2.getEntry(c, b));
        // clog << "value: " << value << endl
        //      << "a: " << a << " b: " << b << " c: " << c << endl;
      }
      temp.push_back(value);
    } 
    values.push_back(temp);
  }
  return construct.setValues(values);
}
bool operator==(const Matrix& m1, const Matrix& m2) {
  bool differencesExist = false;
  if (m1.getRowAmount() != m2.getRowAmount() || 
      m1.getColumnAmount() != m2.getColumnAmount()) return false;
  for (size_t a = 0; a < m1.getRowAmount(); ++a) {
    for (size_t b = 0; b < m1.getColumnAmount(); ++b) {
      if (m1.getEntry(a, b) != m2.getEntry(a, b)) 
        differencesExist = true;
    }
  }
  return (differencesExist ? false : true);
}
bool operator!=(const Matrix& m1, const Matrix& m2) {
  return !(m1 == m2);
}


#endif