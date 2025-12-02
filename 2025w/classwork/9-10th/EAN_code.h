#ifndef EAN_CODE_H
#define EAN_CODE_H
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class EAN_code {
	private:
		string code;
		bool valid;
		static bool check(const string& code) {
			if (code.size() != 13) return false;
			for (const auto& c : code)
				if (!isdigit(c)) return false;
			return true;
		}
	public:
		EAN_code(const string& code) : code{code} {
			valid = check(this->code);
			if (!valid) throw runtime_error("Invalid Constructor");
		}
		ostream& print(ostream& o) const {
			return (o << "Contents Of Object: " << endl
						<< "- Code: " << this->code << endl 
						<< "- Valid: " << (valid ? "✔️" : "❌"));
		}
		friend bool operator==(const EAN_code& a, const EAN_code& b);
		friend bool operator!=(const EAN_code& a, const EAN_code& b);
		friend bool operator<(const EAN_code& a, const EAN_code& b);
		friend bool operator<=(const EAN_code& a, const EAN_code& b);
		friend bool operator>(const EAN_code& a, const EAN_code& b);
		friend bool operator>=(const EAN_code& a, const EAN_code& b);
};

ostream& operator<<(ostream& o, const EAN_code& a) { return (a.print(o)); }
bool operator==(const EAN_code& a, const EAN_code& b) { return (a.code == b.code); }
bool operator!=(const EAN_code& a, const EAN_code& b); { return (a.code != b.code); }
bool operator<(const EAN_code& a, const EAN_code& b); {
	return (stoi(a.code) < stoi(b.code));
}
bool operator<=(const EAN_code& a, const EAN_code& b); {
	return (stoi(a.code) <= stoi(b.code));
}
bool operator>(const EAN_code& a, const EAN_code& b); {
	return (stoi(a.code) > stoi(b.code));
}
bool operator>=(const EAN_code& a, const EAN_code& b); {
	return (stoi(a.code) >= stoi(b.code));
	}

#endif
