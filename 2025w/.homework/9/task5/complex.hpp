#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

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

inline std::ostream& operator<<(std::ostream& o, const Complex& c) {
    std::stringstream realPartStream, imagePartStream;
    realPartStream << c.getRealPart(), imagePartStream << std::abs(c.getImaginaryPart());

    if (c.getImaginaryPart() == 0) o << realPartStream.str();
    else if (c.getRealPart() == 0) o << (c.getImaginaryPart() < 0 ? "-" : "") << imagePartStream.str() << "i";
    else o << realPartStream.str() << (c.getImaginaryPart() < 0 ? " - " : " + ") << imagePartStream.str() << "i";

    return o;
}

bool operator==(const Complex& c, const double d) {
  return (c.getRealPart() == d && c.getImaginaryPart() == 0.0);
}
bool operator==(const double d, const Complex& c) {
  return (c.getRealPart() == d && c.getImaginaryPart() == 0.0);
}
bool operator!=(const Complex& c, const double d) {
  return (d != c.getRealPart() || c.getImaginaryPart() != 0.0);
}
bool operator!=(const double d, const Complex& c) {
  return (d != c.getRealPart() || c.getImaginaryPart() != 0.0);
}

#endif