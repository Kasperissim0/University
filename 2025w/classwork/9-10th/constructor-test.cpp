#include <iostream>
#include <string>
#include <stdexcept>
#include "EAN_code.h"
#include "item.h"
// #include "shop.h"
#include "screen.h" // adds clearScreen()          + <iomanip> and <cstdlib>
#include "wait.h"   // adds wait(unsigned seconds) + <thread> and <chrono>
#include "colors.h" // adds color modifiers Color::FG/BG/ATTR::(Bright::)Modify
// use "clang++ -std=c++23 x.cpp -I../../../.functions-link -o x" for correct preprocessor behaviour

using namespace std;

int main (int argn, char** args) { if (argn != 2) return 1;
	// char goAgain; 
	string temp = args[1];
	
	// do {
		clearScreen();
		// while (cin >> temp && temp != "q") {
			try {
				EAN_code i = temp;
				Item test({i, "Cookie", "The Tastiest Cookier Ever", "321232131231,22335"});
				cout << test << endl << endl;
			}
			catch (const runtime_error& e) {
				cerr << endl << r << red << "❌ ERROR: " << r << b << e.what() << endl << r;
			}
		// }
	// } while (cout << r << b << "\n\n  " << u << "➡︎ Go Again?" 
	//				  << r << b << " (" << green << "y"<< black 
	//				  << b << '/' << red << 'n' << r << "): "
	//				  && cin >> goAgain && goAgain == 'y');
	// clearScreen();	
	return 0;
}
