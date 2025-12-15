#include "screen.hpp"  // adds clearScreen()
#include "wait.hpp"    // adds wait(unsigned seconds)
#include "colors.hpp"  // adds color modifiers Color::FG/BG/ATTR::(Bright::)Modify
#include "random.hpp"  // adds "gen" variable with type generation methods
#include "outputs.hpp" // adds << overloads for common classes (vectors, maps, ...)
//* use "clang++ -std=c++23 x.cpp -I../../../.functions-link -o x" to compile
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main (int argc, char** args) { // if (argc != ) return 1;
	char goAgain;
  
	do { clearScreen();
  	try {
      // cout << "🚧 Attempting To Delete " << gen.getFile() << endl; 
      gen.deleteFile();
      // cout << "✅ Succesfully Deleted " << gen.getFile() << endl;
    } catch (const runtime_error& e) { cerr << "❌ ERROR: " << e.what() << endl; }
		cout << Color::FG::Bright::YELLOW << "List Of Random Chars: " << r << endl; wait(1);
    cout << gen.setFile("test").setAmount(5)
                               .writeValues<char>(' ', '~')
                               .readValues<string>()
         << endl;
    try {
      // cout << "🚧 Attempting To Delete " << gen.getFile() << endl; 
      gen.deleteFile();
      // cout << "✅ Succesfully Deleted " << gen.getFile() << endl;
    } catch (const runtime_error& e) { cerr << "❌ ERROR: " << e.what() << endl; } 
	} while (cout << r  << b << "\n\n  " << u << "➡︎ Go Again?"
								<< r << b << " (" << green << "y"<< black
								<< b << '/' << red << 'n' << r << "): "
								&& cin >> goAgain && goAgain == 'y');
	clearScreen();
	return 0;
}