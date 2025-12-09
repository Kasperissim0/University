#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>
#include <stdexcept>
#include "EAN_code.h"

using namespace std;

class Item {
	private:
	EAN_code code;
	string name, description = "";
	struct Price {
		private:
			unsigned euros, cents;
			string full;
		public:
		Price(string input) {
			string euros, cents, sign = "€"; char point = '.', comma = ','; 
			bool commaSeparator, noCents = false;
			// Check Validity
			for (const auto& c : input)
				if (!isdigit(c) && c != point && c != comma) 
					throw runtime_error("Passed Input Not A Valid Number");
			// Determine Separator
			if (input.find(point) != string::npos &&
				 input.find(comma) != string::npos) throw runtime_error("Use Only 1 Separator");
			if (input.find(point) != string::npos) commaSeparator = false;
			else if (input.find(comma) != string::npos) commaSeparator = true;
			else noCents = true;
			// Construct Strings
			if (!noCents) {
				try {
					const auto& separator = input.find((commaSeparator ? comma : point));
					if (separator == string::npos)
						throw runtime_error("Failed To Create Iterator For Separator");
					euros = input.substr(0, separator);
					cents = input.substr(separator + 1, input.size());
				}
				catch (const out_of_range& e) {
					cerr << endl << e.what() << endl;
					throw runtime_error("Failed To Create Iterator For Separator"); 
				}
			}
			else euros = input;
			// Convert To Integers
			try {
				this->euros = stoul(euros);
				this->cents = (noCents ? 0 : stoul(cents));
				string modifiedEuros = [&] {
					string output, &input = euros; 
					for (size_t i = (input.size() - 1), addComma = 0; i >= 0; --i, ++addComma) {
						if (i != (input.size() - 1) && i < input.size() && addComma % 3 == 0) 
							output = comma + output;
						if (i > input.size()) break;
						output = input.at(i) + output;
					}
					return output;
				}();
				this->full = modifiedEuros + point + to_string(this->cents) + " " + sign;
				// Comma/Point Choice Is Due To Personal Preference
			}
			catch (const invalid_argument& e) {
				cerr << endl << e.what() << endl;
				throw runtime_error("Failed To Convert: " + euros + " OR "
																      + cents + "To Integers"); 
			}
			catch (const out_of_range& e)     {
				cerr << endl << e.what() << endl;
				throw runtime_error("Failed To Convert: " + euros + " OR "
																      + cents + " To Integers");
			}	
		}
		string getFullPrice() const {
			return full;
		}
		unsigned getEuroAmount() const {
			return euros;
		} 
		unsigned getCentAmount() const {
			return cents;
		}
	} price;
	public:
		Item(EAN_code code, string name, string description, string price)
		: code{code}, description{description}, price{price} {
			if (name.empty()) throw runtime_error("Name Cannot Be Empty");
			else this->name = name;
		}
		ostream& print(ostream& o) const {
			return (o << code.getCode() << ": " << name << " " 
						 << price.getFullPrice() << endl << "> " << description);
		}

};

ostream& operator<<(ostream& o, Item& i) { return i.print(o); }

#endif
