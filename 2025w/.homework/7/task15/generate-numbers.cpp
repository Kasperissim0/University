#include <iostream>
#include <filesystem>
#include <fstream>
#include <random>

using namespace std;

static const string FILE_NAME = "input.txt";

ssize_t getRandomNumber (const ssize_t& minValue, const ssize_t& maxValue) {
  std::random_device randomSeed;
  std::mt19937 generateSeed(randomSeed());
  std::uniform_int_distribution<ssize_t> distributionRange(minValue, maxValue);

  return distributionRange(generateSeed);
}

int main(int argc, char** argv) { if (argc < 2 || argc > 4) return 1;
  size_t amountOfNumbers; ssize_t minNumber = numeric_limits<ssize_t>::min(), 
                                  maxNumber = numeric_limits<ssize_t>::max();
  try { 
    ssize_t temp = stol((string)argv[1]);
    if (temp < 0) { cerr << "❌ Invalid Input: Must Be A Positive Integer" << endl; return 1; }
    amountOfNumbers = static_cast<size_t>(temp);
  }
  catch (const invalid_argument& e) { cerr << "❌ Invalid Input: Not A Number" << endl; return 1; }
  catch (const out_of_range& e) { cerr << "❌ Invalid Input: Too Large" << endl; return 1; }
  if (argc >= 3) { 
    try { minNumber = stol((string)argv[2]); }
    catch(...) { cerr << "❌ Invalid Input: Using Default" << endl; }
  }
  if (argc == 4) {
    try { maxNumber = stol((string)argv[3]); }
    catch(...) { cerr << "❌ Invalid Input: Using Default" << endl; }
  }
  if (minNumber > maxNumber) {
    cerr << "❌ Invalid Input: " << minNumber << " > " << maxNumber << endl; 
    return 1;
  }

  ofstream file(FILE_NAME); if (!file.is_open()) return 1;
  cout << "🚧 Generating " << amountOfNumbers 
       << " Numbers In The Range From " << minNumber << " to " << maxNumber << endl;
  for (size_t i = 0; i < amountOfNumbers; ++i) file << getRandomNumber(minNumber, maxNumber) << endl;
  cout << "✅ Finished - Results In: \"" << FILE_NAME << "\"" << endl; file.close();
  return 0;
}