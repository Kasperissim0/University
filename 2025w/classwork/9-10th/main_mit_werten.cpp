#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
#include<cctype>
#include<limits>
#include<cassert>
#include"ean_code.h"
#include"artikel.h"
#include"shop.h"
using namespace std;




int main() {

	Shop shop{"https://buyhere.com","Der beste Shop","Rabattstrasse","80","4780","Billigsdorf"};

  vector<EAN_code> eans{
		EAN_code{"1111111111111"},
		EAN_code{"2222222222222"},
		EAN_code{"3333333333333"},
		EAN_code{"4444444444444"},
		EAN_code{"5555555555555"},
		EAN_code{"6666666666666"},
		EAN_code{"7777777777777"},
		EAN_code{"8888888888888"},
		EAN_code{"9999999999999"},
		EAN_code{"1010101010101"}
	};
	vector<string> bez;
	bez.push_back("Tee");
	bez.push_back("Kaffee");
	bez.push_back("Warhammer");
	bez.push_back("Armada");
	bez.push_back("Imperial Assault");
	bez.push_back("Gummibaeren");
	bez.push_back("XWing");
	bez.push_back("TV");
	bez.push_back("Starcraft");
	bez.push_back("Dota 2");
	vector<string> bes;
	bes.push_back("Sencha Tee");
	bes.push_back("Ristretto");
	bes.push_back("Eldar Army");
	bes.push_back("CR-90");
	bes.push_back("Battle of Hoth");
	bes.push_back("Die echt guten");
	bes.push_back("Luke's");
	bes.push_back("Den groessten");
	bes.push_back("Zerg ftw");
	bes.push_back("Best game");
	vector<int> preis{
		1090,
		600,
		10423,
		3900,
		4570,
		230,
		700,
		50000,
		5900,
		1
	};
	for(size_t i{0};i<preis.size();++i) shop.addArtikel(Artikel{eans[i],bez[i],bes[i],preis[i]});
	
	cout << shop;

	//Bestellung b{77,{Bestellposition{eans[0],1,shop},Bestellposition{eans[1],6,shop},Bestellposition{eans[2],7,shop},Bestellposition{eans[3],20,shop}}};
	//
	//cout << b;


  return 0;
}
