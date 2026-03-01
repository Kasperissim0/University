//§ Preamble
  #include <chrono>
  #include <cstddef>
  #include <cstdlib>
  #include <iostream>
  #include <string>
  #include <thread>
  #include "random.hpp"
  using namespace std;
//.

//? Source(s):  https://moodle.univie.ac.at/mod/extserver/view.php?id=19368923
//?             https://minesweeperhub.com/basic-minesweeper-rules/
//?             https://en.wikipedia.org/wiki/Minesweeper_(video_game)
//* Task: Implement the game Minesweeper using arrays (i.e. without classes from libraries)
  
constexpr size_t DIMENSION = 9;

void printBoard(bool board[DIMENSION][DIMENSION]) {
  auto v = "|", h = "---", x = "X", q = "?", s = " ";
  char index = 'A';

  cout << s << s << s;
  for (size_t i = 0; i < DIMENSION; ++i)
    cout << s << index++ << s;
  cout << endl;
  cout << s << s << s;
  for (size_t i = 0; i < DIMENSION; ++i)
    cout << h;
  cout << endl;
  for (size_t a = 0; a < DIMENSION; ++a) {
    cout << (a + 1) << s << v;
    for (size_t b = 0; b < DIMENSION; ++b) {
      cout << s << ((board[a][b]) ? x : q) << s;
    }
    cout << v << endl;
  }
  cout << s << s << s;
  for (size_t i = 0; i < DIMENSION; ++i)
    cout << h;
  cout << endl;
}
int getUserInput(const int from, const int to, const string message = "") {
  string input, errorMessage = "❌ Invalid Input Entered, Try Again";
  bool validInput = false; int numericalInput;

  do {
    if (!message.empty()) cout << message << endl;
    cout << "  ➡︎ Input Range (" << from << "-" << to << "): ";
    getline(cin, input);

    try {
      numericalInput = stoi(input);
      validInput = true;
      break;
    } catch (...) {}
    cout << errorMessage << endl;
    this_thread::sleep_for(chrono::seconds(2));
    system("clear");
  } while (!validInput);
  
  return numericalInput;
}

int main(int n, char* args[]) {
  bool playBoard[DIMENSION][DIMENSION] = {}; 
  size_t xCoordinate, yCoordinate;

  for (size_t a = 0; a < DIMENSION; ++a)
    for (size_t b = 0; b < DIMENSION; ++b)
      playBoard[a][b] = gen.generate<bool>();

  // do {
  printBoard(playBoard);
  cout << endl << "Choose Row/Column:" << endl;

  // } while ();
  return 0;
}