#include<iostream>
#include<string>
#include<vector>
#include"city.h"
#include"zip.h"
#include"address.h"

using namespace std;


vector<vector<Address>> group (const vector<Address>& addresses) {
	vector<vector<Address>> output; vector<string> collected;
	for (const auto& address : addresses) {
		string current = address.z.code; vector<Address> temp; bool saved = false;
		for (const auto& code : collected)
			if (code == current) saved = true;
		if (saved) continue; 
		for (const auto& address : addresses)
			if (address.z.code == current) temp.push_back(address);
		collected.push_back(current);
		output.push_back(temp);
	}
	return output;
}
 
vector<string> split(string str, char delim = ',') {
  vector<string> ret;
  string current;
  for (const auto& c : str)
    if (c == delim) {
      ret.push_back(current);
      current.clear();
    }
    else
      current.push_back(c);
  ret.push_back(current);
  return ret;
}

bool check_data(vector<string> data, size_t size) {
  if (data.size() != size)
    return false;
  for (const auto& field : data)
    if (field.empty())
      return false;
  return true;
}

void read_data(vector<Address>& addresses) {
  string line;
  while (getline(cin,line)) {
    vector<string> data{split(line)};
    if (!check_data(data, 5))
      throw runtime_error("illegal input format (address)");
    addresses.push_back(Address{data.at(0),data.at(1),data.at(2),data.at(3),{data.at(4)}});
  }

  if (addresses.empty())
    throw runtime_error("illegal input format (file)");
}

int main() {
  vector<Address> addresses;

  try {
    read_data(addresses);

    cout << "\nAddresses: \n\n";
    for (auto& address : addresses) { //const intentionally not used
      address.print();
    }

  }
  catch(runtime_error& e) {
    cerr << "Error: " << e.what() << '\n';
    cerr << "\nProgram terminated!\n";
  }
  return 0;
}
