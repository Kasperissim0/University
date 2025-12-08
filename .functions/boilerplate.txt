#include <iostream>
#include "screen.h" // adds clearScreen()          + <iomanip> and <cstdlib>
#include "wait.h"   // adds wait(unsigned seconds) + <thread> and <chrono>
#include "colors.h" // adds color modifiers Color::FG/BG/ATTR::(Bright)::Modify
// use "clang++ -std=c++23 x.cpp -I../../../.functions-link -o a" for correct preprocessor behaviour

using namespace std;

int main() {
	char goAgain;
	
	do {
		clearScreen();
		cout << blue << "hello " << reset << flush; wait(2); cout << yellow << "there" << reset;
	} while (cout << bold << "\n\n " << underline << "➡︎ Go Again?" 
								<< reset << bold << " (" << green << "y"
							  << black << bold << '/' << red << 'n' << reset 
								<< "): " && cin >> goAgain && goAgain == 'y');
	clearScreen();	
	return 0;
}