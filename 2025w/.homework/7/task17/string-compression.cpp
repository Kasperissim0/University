#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

struct CompressedChar {
  unsigned amount;
  char type;
};

ostream& operator<< (ostream& o, const vector<CompressedChar>& v);
ostream& operator<< (ostream& o, const CompressedChar& c);

struct CompressedString {
  struct Info {
    string original;
    vector<CompressedChar> compressed;
  } string;
  vector<CompressedChar> compressString() {
    vector<CompressedChar> compactString; CompressedChar compactChar;
    auto &s = string.original;

    // clog << "\x1b[31m" << "                                          Full String: " << "\x1b[33m" << s << "\x1b[0m" << endl;
    for (size_t i = 0; i < s.size(); ++i) {
      // clog << "1. " << "\x1b[34m" << "Processing: " << "\x1b[33m" << "'" << s.at(i) << "'" << "\x1b[0m" <<  " @ Index " <<  "\x1b[31m" << i << "\x1b[0m" << endl;
      // clog << "2. " << "\x1b[31m" << "String Left: " << "\x1b[33m" << s.substr(i, s.length()) << "\x1b[0m" << endl;
      compactChar.amount = 1; compactChar.type = s.at(i);
      
      for (size_t a = (i + 1); a < s.size(); ++a) {
        if (s.at(a) == compactChar.type) ++compactChar.amount; 
        else break;
      }
      if (compactChar.amount > 1) i += (compactChar.amount - 1);
      // clog << "3. " <<  "\x1b[32m" << "Adding: " << "\x1b[33m" << compactChar << "\x1b[0m" << endl
      //     << "4. " <<  "\x1b[35m" << "State Before Addition: " << "\x1b[0m" << compactString << endl;
      compactString.push_back(compactChar);
      // clog << "5. " <<  "\x1b[36m" << "State After Addition: " << "\x1b[0m" << compactString << endl << endl;
    }
    return (this->string.compressed = compactString);
  }
};

string sort(const string& s) {
  string temp = s;
  std::sort(temp.begin(), temp.end(), [](char a, char b) {
    auto letterIsAVowel = [](char c) {
        string vowels = "AEIOUYaeiouy";
        return vowels.find(c) != string::npos;
    };

    bool AisAVowel = letterIsAVowel(a), BisAVowel = letterIsAVowel(b);

    if (AisAVowel && !BisAVowel) return true;
    if (!AisAVowel && BisAVowel) return false;
    return a < b;
  });
  return temp;
}

ostream& operator<< (ostream& o, const vector<CompressedChar>& v) {
  size_t size = v.size(); // // clog << "Size: " << "\x1b[31m" << size << "\x1b[0m" << ", Content: " << "\x1b[33m";
  for (size_t i = 0; i < size; ++i) o << (v.at(i).amount > 1 ? to_string(v.at(i).amount) : "") << v.at(i).type;
  return o << "\x1b[0m" ;
}
ostream& operator<< (ostream& o, const CompressedChar& c) {
  o << (c.amount == 1 ? "" : to_string(c.amount)) << c.type;
  return o;
}


int main() {
  CompressedString input; auto &fullString = input.string.original; auto &compactString = input.string.compressed;
  cout << "Insert A String With Letters Only: "; cin >> fullString; for (char c : fullString) if (!isalpha(c)) return 1;
  system("clear");
  cout << "The Original String:               " << "\x1b[33m" << fullString << "\x1b[0m" << endl;  input.compressString();
  cout << "The Original String Compressed:    " << "\x1b[33m" << compactString << "\x1b[0m" << endl;  fullString = sort(fullString);
  cout << "The String Sorted Alphabetically:  " << "\x1b[33m" << fullString << "\x1b[0m" << endl;  input.compressString();
  cout << "The Alphabetical String Compressed: " << "\x1b[33m" << compactString << "\x1b[0m" << endl;
  return 0;
}