#ifndef ZIP_H
#define ZIP_H

#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
#include"city.h"

using namespace std;

struct ZIP {
  inline const static vector<City> cities{
	  {"1010","Wien"},
	  {"1020","Wien"},
	  {"1080","Wien"},
	  {"1090","Wien"},
	  {"1110","Wien"},
	  {"1100","Wien"},
	  {"1300","Mannswörth"},
	  {"4099","Wiesen"},
	  {"8051","Graz"},
	  {"8036","Graz"},
	  {"8047","Hart bei Graz"},
	  {"05020","Salzburg"},
	  {"5026","Salzburg"}
  };

  string code;

  bool check() {
  	for (size_t i = 0; i < cities.size(); ++i) if (code == cities.at(i).zip) return true;
  	return false;
  }
  void print() {
  	size_t index; bool found = false;
  	for (size_t i = 0; i < cities.size(); ++i) 
  		if (code == cities.at(i).zip) { index = i; found = true; }
  	if (found) cout << cities.at(index).zip << " : " << cities.at(index).name << endl;
  	else throw runtime_error("Current Index Is Not Valid");
  }
};

#endif
