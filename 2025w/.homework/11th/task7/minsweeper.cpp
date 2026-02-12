//§ Preamble
  #include <iostream>
  #include <string>
  #include <cstdlib>
  #include <chrono>
  #include <thread>
  using namespace std;
//.

//? Source: https://minesweeperhub.com/basic-minesweeper-rules/
//* Task: (*) Implement the game Minesweeper using arrays (i.e. without classes from libraries)

int getUserInput(const int from, const int to, const string message = "") {
  string input, errorMessage = "❌ Invalid Input Entered, Try Again"; 
  bool validInput = false; int numericalInput;
  do {
    if (!message.empty()) cout << message << endl;
    cout << "  ➡︎ Input Range (" << from << "-" << to << "): "; getline(cin, input);

    try {
      numericalInput = stoi(input);
      validInput = true; 
      break;
    } 
    catch (...) {}
    cout << errorMessage << endl; 
    this_thread::sleep_for(chrono::seconds(2)); system("clear");
  } while(!validInput);
  return numericalInput;
}

int main() {
  bool playBoard[9][9] = {}; size_t xCoordinate, yCoordinate;
   for (size_t i = 0, max = 81; i < max; ++i)
    cout << "# " << (i + 1) << ", at [" << i / 9 << "][" << i % 9 << "]: " << playBoard[i / 9][i % 9] << endl;
}