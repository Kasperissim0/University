#include <iostream>
#include <vector>

using namespace std;

vector<unsigned> findPrimes(unsigned input) {
  vector<unsigned> primes;
  if (input < 2) return primes;

  // Sieve of Eratosthenes using a byte-vector to avoid vector<bool> quirks
  vector<char> composite(input + 1, true);
  composite.at(0) = composite.at(1) = false;

  for (unsigned p = 2; p <= input / p; ++p) {
    if (!composite.at(p)) continue;
    for (unsigned m = p * p; m <= input; m += p) composite.at(m) = false;
  }

  for (unsigned i = 2; i <= input; ++i) if (composite.at(i)) primes.push_back(i);

  return primes;
}

int main () {
  unsigned n; vector<unsigned> primes;
  cout << "Insert A Positive Integer: ";
  if (!(cin >> n)) return 1; 
  cout << "All Primes Until " << n << ": " << endl; primes = findPrimes(n);
  for (size_t i = 0; i < primes.size(); ++i) cout << "[ " <<  (i + 1) << " ]   " << primes.at(i) << endl;
  return 0;
}