#ifndef ADRESS_H
#define ADRESS_H

#include <string>
#include <iomanip>
#include "zip.h"

using namespace std;

 size_t i = 0; 

struct Address {
	string name, surname, road, street;
	ZIP z;
	
	void print() {
		string s = " ";
		string person = "'" + name + s + surname + "'",
				 adress = "@" + s + road + s + street,
		       content = to_string(++i) + ". " + person + s + adress;
		cout << content << " | "; z.print();
	}
};

#endif
