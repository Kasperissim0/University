#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

using namespace std;

ostream& operator<<(ostream& output, const vector<ssize_t>& v) {
  size_t current = 0;
  if (v.empty()) output << "No Elements Avaliable";
  else 
    for (size_t i = 0, size = v.size(); i < size; ++i) {
      output << left << setw(v.size() * 0.01) << "Element #" << ++current << ": ";
      output << right << setw(v.size() * 0.009) << v.at(i) << endl;
    }
  return output;
}

void quickSort(vector<ssize_t>& v, size_t start, size_t end) { if (end <= start) return;
  size_t pivotIndex = [&]{
    size_t tailIndex = start; auto& pivot = v.at(end);

    for (size_t index = start; index < end; ++index) if (v.at(index) < pivot) swap(v.at(tailIndex++), v.at(index));
    swap(v.at(tailIndex), v.at(end));
    return tailIndex;
  }();

  if (pivotIndex > 0 && (pivotIndex - 1) >= start) quickSort(v, start, (pivotIndex - 1));
  quickSort(v, (pivotIndex + 1), end);
}

int main(int argc, char** argv) { if (argc < 2) return 1;
  vector<ssize_t> numbers;

  if (!filesystem::exists((string)argv[1])) {
    for (size_t i = 1, size = argc; i < size; ++i) { 
      try { numbers.push_back(static_cast<ssize_t>(stol((string)argv[i]))); }
      catch (...) { cerr << "❌ Skipping: \"" << argv[i] << "\"" << endl; }
    } if (numbers.empty()) return 1;
  }
  else {
    ifstream file((string)argv[1]); ssize_t temp;
    while (file >> temp) numbers.push_back(temp); 
    file.close();
  }

  quickSort(numbers, 0, (numbers.size() - 1));
  cout << endl << "📉 List Sorted By Ascending Value 📉" << endl << numbers << endl;
  return 0;
}