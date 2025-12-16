#include <iostream>
#include "complex.hpp"

using namespace std;

int main() {
  Complex c1(2),c2(3,-4); double d1=2, d2(3);

  cout << c2 << " is " << (c2==d2 ? "" : "not ") << "equal to " << d2 << endl 
       << c1 << " is " << (c1!=d1 ? "not " : "") << "equal to " << d1 << endl 
       << d1 << " is " << (d1==c1 ? "" : "not ") << "equal to " << c1 << endl 
       << d2 << " is " << (d2!=c2 ? "not " : "") << "equal to " << c2 << endl 
       << "The Complex Conjugate Of " << c2 << " is " << c2.conj() << endl;
  return 0;
}
