#ifndef ADRESS_H
#define ADRESS_H

#include <string>
#include "zip.h"

using namespace std;

struct Address {
	string name, surname, road, street;
	ZIP z;
	
	void print() {
		char s = ' '; size_t i = 0; 
		cout << ++i << ". " << name << s << surname << s << road << s << street;
	}
};

#endif
