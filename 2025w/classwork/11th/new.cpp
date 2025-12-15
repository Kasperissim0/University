#include <iostream>
#include "screen.hpp" // adds clearScreen()          + <iomanip> and <cstdlib>
#include "wait.hpp"   // adds wait(unsigned seconds) + <thread> and <chrono>
#include "colors.hpp" // adds color modifiers Color::FG/BG/ATTR::(Bright::)Modify
// use "clang++ -std=c++23 x.cpp -I../../../.functions-link -o x" to compile successfully

using namespace std;

int main (int argc, char** args) { // if (argc != ) return 1;
	char goAgain;
	
	do { clearScreen();
		cout << r  << i << Color::FG::Bright::BLUE << "hello " <<  flush; wait(2); 
		cout << Color::FG::Bright::YELLOW << "there";
	} while (cout << r  << b << "\n\n  " << u << "➡︎ Go Again?" 
								<< r << b << " (" << green << "y"<< black 
								<< b << '/' << red << 'n' << r << "): "
								&& cin >> goAgain && goAgain == 'y');
	clearScreen();	
	return 0;
}