#include <iostream>
#include <string>
#include <vector>
#include "complex.hpp"
#include "matrix.hpp"
#include "random.hpp"

using namespace std;

int main (int argc, char** args) { if (argc < 2 || argc > 3) return 1;
  unsigned rowAmount, columAmount; vector<vector<Complex>> v1, v2; Matrix m1, m2;
  try {
    rowAmount = stol(args[1]);
    columAmount = (argc == 2 ? 1 : stol(args[2]));
  }
  catch (...) {
    cout << "Invalid Argument(s) Passed " << endl 
         << "Required: rowAmount columAmount" << endl;
    return 1;
  }
  for (size_t a = 0; a < rowAmount; ++a) {
    vector<Complex> temp1 = {}, temp2 = {};
    for (size_t b = 0; b < columAmount; ++b) {
      temp1.push_back({getRandomNumber(-100, 100), getRandomNumber(-100, 100)});
      temp2.push_back({getRandomNumber(-100, 100), getRandomNumber(-100, 100)});
    } v1.push_back(temp1), v2.push_back(temp2);
  } m1.setValues(v1); m2.setValues(v2);
  cout << "Displaying Matrix #1: " << endl << m1 << endl
       << "Matrix #1 Transposed: " << endl << m1.transpose() << endl
       << "Displaying Matrix #2: " << endl << m2 << endl
       << "Matrix #2 Conjugated: " << endl << m2.conjugate() << endl
       << "Matrix #1 + Matrix #2: " << endl << m1 + m2 << endl
       << "Matrix #2 - Matrix #1: " << endl << m2 - m1 << endl
       << "Matrix #1 * Matrix #2: "  << endl << m1 * m2.transpose() << endl;
  try { cout << "(Matrix #1)^2: " << endl << m1 * m1 << endl; }
  catch (const runtime_error& e) {cerr << "❌ Matrix Is Not Square, Cancelling Operation" << endl; }
  cout << "Matrix #2 * Matrix #2 Trasposed: " << endl << m2 * m2.transpose() << endl;
  return 0;
}