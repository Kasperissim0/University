#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void sort(string& s) {
  std::sort(s.begin(), s.end(), [](char a, char b) {
    auto letterIsAVowel = [](char c) {
        string vowels = "AEIOUYaeiouy";
        return vowels.find(c) != string::npos;
    };

    bool AisAVowel = letterIsAVowel(a), BisAVowel = letterIsAVowel(b);

    if (AisAVowel && !BisAVowel) return true;
    if (!AisAVowel && BisAVowel) return false;
    return a < b;
  });
}

int main() {
  string input;
  cout << "Insert A String With Letters Only: "; cin >> input; for (char c : input) if (isdigit(c)) return 1;
  sort(input);
  cout << "The String Sorted Alphabetically:  " << input << endl;
  return 0;
}