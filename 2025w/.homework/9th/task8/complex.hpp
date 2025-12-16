#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Complex {
  private:
    double realPart, imaginaryPart;
  public:
    Complex(const double a = 0, const double b = 0) : realPart {a}, imaginaryPart {b} {}
    Complex conj() {
      return Complex(realPart, -imaginaryPart);
    }
    double getRealPart() const {
      return realPart;
    }
    double getImaginaryPart() const {
      return imaginaryPart;
    }
};

inline ostream& operator<<(ostream& o, const Complex& c) {
    stringstream realPartStream, imagePartStream;
    realPartStream << c.getRealPart(), imagePartStream << abs(c.getImaginaryPart());

    if (c.getImaginaryPart() == 0) o << realPartStream.str();
    else if (c.getRealPart() == 0) o << (c.getImaginaryPart() < 0 ? "-" : "") << ((c.getImaginaryPart() == 1) ? "" : (imagePartStream.str())) << "i";
    else o << realPartStream.str() << (c.getImaginaryPart() < 0 ? " - " : " + ") << ((c.getImaginaryPart() == 1) ? "" : (imagePartStream.str())) << "i";

    return o;
}

bool operator==(const Complex& c1, const Complex& c2) {
  return (c1.getRealPart() == c2.getRealPart() && c2.getImaginaryPart() == c2.getImaginaryPart());
}
bool operator==(const Complex& c, const double d) {
  return (c.getRealPart() == d && c.getImaginaryPart() == 0.0);
}
bool operator==(const double d, const Complex& c) {
  return (c.getRealPart() == d && c.getImaginaryPart() == 0.0);
}
bool operator!=(const Complex& c1, const Complex& c2) {
  return (c1.getRealPart() != c2.getRealPart() || c2.getImaginaryPart() != c2.getImaginaryPart());
}
bool operator!=(const Complex& c, const double d) {
  return (d != c.getRealPart() || c.getImaginaryPart() != 0.0);
}
bool operator!=(const double d, const Complex& c) {
  return (d != c.getRealPart() || c.getImaginaryPart() != 0.0);
}
Complex operator+(const Complex& c) {
  return c;
}
Complex operator+(const Complex& c1, const Complex& c2) {
  return Complex((c1.getRealPart() + c2.getRealPart()), (c1.getImaginaryPart() + c2.getImaginaryPart()));
}
Complex operator-(const Complex& c) {
  return Complex((-c.getRealPart()), (-c.getImaginaryPart()));
}
Complex operator-(const Complex& c1, const Complex& c2) {
  return (c1 + -c2);
}
Complex operator*(const Complex& c1, const Complex& c2) {
  return Complex(((c1.getRealPart() * c2.getRealPart()) - (c1.getImaginaryPart() * c2.getImaginaryPart())), 
                ((c1.getRealPart() * c2.getImaginaryPart()) + (c1.getImaginaryPart() * c2.getRealPart())));
}
Complex operator+= (Complex& c1, const Complex& c2) {
  Complex construct = c1 + c2;
  return c1 = construct, c1;
}

#endif