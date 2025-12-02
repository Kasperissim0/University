#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "functions/screen.h" // adds clearScreen()          + <iomanip> and <cstdlib>
#include "functions/wait.h"   // adds wait(unsigned seconds) + <thread> and <chrono>
#include "city.h"
#include "zip.h"
#include "address.h"
							// use  "clang++ x.cpp -I.. -o a" for correct preprocessor behaviour

using namespace std;ged

int main() {
	char goAgain; string zip; ZIP z;
	
	do {
		clearScreen();
		cout << "Insert A ZIP Code: "; cin >> zip; z.code = zip; clearScreen();
		cout << " Existence Check:" << endl << "- Current ZIP Code ";
		if (z.check()) cout << "Exists" << endl;
		else cout << "Does NOT Exist" << endl;
		cout << "\n Value Extraction:" << endl << "- ";
		try { z.print(); }
		catch (const runtime_error& e) { cout << "ERROR: " << e.what() << endl; }
	} while(cout << "\n\nGo Again? (y/n): " && cin >> goAgain && goAgain == 'y');
	clearScreen();	
	return 0;
}
