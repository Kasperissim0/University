#include <iostream>
#include <string>
#include <stdexcept>
#include "EAN_code.h"
#include "screen.h" // adds clearScreen()          + <iomanip> and <cstdlib>
#include "wait.h"   // adds wait(unsigned seconds) + <thread> and <chrono>
// use "clang++ file.cpp -I../../../.functions-link -o a" for correct preprocessor behaviour

using namespace std;

int main() {
	char goAgain; string temp;
	
	do {
		clearScreen();
		while (cin >> temp && temp != "q") {
			try {
				EAN_code i = temp;
				cout << i << endl;
			}
			catch (const runtime_error& e) {
				cerr << "❌ ERROR: " << e.what() << endl;
			}
		}
	} while(cout << "\n\nGo Again? (y/n): " && cin >> goAgain && goAgain == 'y');
	// clearScreen();	
	return 0;
}
