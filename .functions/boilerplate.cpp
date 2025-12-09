#include <iostream>
#include "screen.h" // adds clearScreen()          + <iomanip> and <cstdlib>
#include "wait.h"   // adds wait(unsigned seconds) + <thread> and <chrono>
#include "colors.h" // adds color modifiers Color::FG/BG/ATTR::(Bright::)Modify
// use "clang++ -std=c++23 x.cpp -I../../../.functions-link -o x" for correct preprocessor behaviour

using namespace std;

int main() {
	char goAgain;
	
	do {
		clearScreen();
		cout << i << blue << "hello " <<  flush; wait(2); cout << yellow << "there" << r;
	} while (cout << b << "\n\n " << u << "➡︎ Go Again?" 
								<< r << b << " (" << green << "y"<< black 
								<< b << '/' << red << 'n' << r << "): "
								&& cin >> goAgain && goAgain == 'y');
	clearScreen();	
	return 0;
}