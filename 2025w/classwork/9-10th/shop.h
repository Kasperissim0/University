#ifndef SHOP_H
#define SHOP_H
#include <iostream>
#include <string>
#include<vector>
#include <stdexcept>
#include "EAN_code.h"
#include "item.h"

using namespace std;

class Shop {
	private:
	string url, name, road, zip, city;
	vector<Item> items;
	public:
		ostream& print(ostream& o) const {
			return (o << );
		}
};

ostream& operator<<(ostream& o, Shop& s) { return s.print(o); }

#endif

/*
Modul PR1
Programmierung 1 VU 051010
R1
Uebungseinheit 9
02.12.2025
WS 2025
Diese Unterlagen sind auf der Lehrplattform verfügbar
Programmierung 1 VU – erreichte Meilensteine
✓ Achte Übungseinheit am 25.11.25
✓ Strukturen
Aktueller Meilenstein:
Neunte Übungseinheit heute, am Di, den 02.12.25
2
Das waren die Aufgaben:
Klassen
Operatorüberladung
Vorbereitung für die neunte Übungseinheit
• Sie sollten verstehen, was eine Klasse (bzw. Struktur) ist.
• Sie sollten den Unterschied zwischen Klasse und Struktur kennen.
• Sie sollten die grundlegenden Begriffe (Instanzen, Instanzvariablen, Methoden, Instanziierung)
kennen.
• Sie sollten Operatorüberladung kennen.
• Sie können eine einfache Klasse (bzw. Struktur) mit Ausgabeoperator schreiben und wissen über die
Aufteilung in Header- (.h) und Implementierungsdatei (.cpp) Bescheid.
3
□ Definition einfacher Klassen
□ Verwendung der Klassen in einem Hauptprogramm
Ziel: Sie werden in die Lage versetzt, Klassen für die Programmierung
einzusetzen und sie in ein Interface (Header-Datei) und eine
Implementierung (cpp-Datei) zu trennen.
Was Sie heute erwartet
4
Beispiel: Webshop
• Erstellen Sie eine Klasse EAN_code. Ein EAN_code ist ein String mit 13 Ziffern. Schreiben Sie eine
Klassenmethode check, die überprüft, ob ein String ein gültiger EAN_code ist, einen Konstruktor, der
als Parameter einen String hat und wenn möglich ein entsprechendes EAN_code Objekt erzeugt.
Weiters Vergleichsoperatoren (==, !=, <, <=, >, >=) und eine Methode print zur Ausgabe eines
EAN_code-Objekts.
• Erstellen Sie eine Klasse Item (Artikel). Ein Artikel hat einen EAN_code, eine Bezeichnung (name,
nicht leerer String), eine Beschreibung (description, eventuell leerer String) und einen Preis
(price, int in Eurocent; positiv). Artikel sollen mittels print Methode im oben dargestellten Format
ausgegeben werden können.
• Erstellen Sie eine Klasse Shop. Ein Shop hat eine URL, eine Bezeichnung (name) und eine Adresse
bestehend aus Straße (road), Hausnummer (street_number), Postleitzahl (zip_code) und Ort
(city) - alle Felder sind beliebige, nicht leere Strings. Zusätzlich gibt es eine Liste der Artikel im
Angebot (items). Ein Shop soll mittels print Methode im oben dargestellten Format ausgegeben
werden können.
• Trennen Sie alle Klassen in Interface (.h) und Implementierung (.cpp) und schreiben Sie ein
Hauptprogramm um die Funktionalität zu testen.
Tipp: Daten zum Testen können in Form von Literalen im Programm vorgegeben werden.
(in daten.txt finden sich Initialisierungslisten, die kopiert werden können)
5
1234567890128: Bonbonniere 25,40 Euro
24 exquisite Schokoladestücke + eine Überraschung
https://buyhere.com
Der beste Shop
Rabattstrasse 80
4780 Billigsdorf
...
Artikel1
Artikel2
---
Klassen Artikel und Shop: Methoden
• Realisieren Sie Mutatoren (setter-Methoden) für die Instanzvariablen in der Klasse Artikel:
◦ Alle Mutatoren müssen das Objekt in einem konsistenten Zustand hinterlassen.
◦ Der Versuch, illegale Werte zu setzen, soll zum Werfen einer Exception führen.
• Realisieren Sie folgende Methoden in der Klasse Shop:
◦ Item& find_item(const EAN_code&): Der Artikel mit dem angegebenen EAN_code wird
im Angebot gesucht und eine Referenz auf den Artikel wird retourniert (z.B. um den Artikel
anschließend zu bearbeiten). Es ist eine Exception zu werfen, wenn kein entsprechender Artikel im
Angebot ist.
◦ void add_item(const Item&): Ein zusätzlicher Artikel wird zum Sortiment hinzugefügt.
Falls bereits ein Artikel mit demselben EAN-Code im Angebot ist, ist eine Exception zu werfen.
6
Erweiterung Shop: Artikel aus Angebot entfernen
• Erweitern Sie die Klasse Shop um eine Methode bool del_item(const EAN_code&), die den
entsprechenden Artikel, so vorhanden, aus dem Angebot entfernt. Es ist true zu retournieren, wenn
der Artikel entfernt werden konnte, false sonst.
7
Erweiterung Artikel: Kategorien
• Erstellen Sie ein enum Category mit Werten wie Clothing, Electronics, Game etc.
• Erweitern Sie die Klasse Item um eine zusätzliche Instanzvariable für die Kategorie des Artikels und
ändern Sie Ein-/Ausgabe- und Editierfunktionen so, dass auch die Kategorie eines Artikels eingegeben
und editiert werden kann und entsprechend mit ausgegeben wird.
• Erweitern Sie die Klasse Artikel um eine Methode bool in_category(Category), die true
retourniert, wenn der Artikel der Kategorie angehört und false sonst.
8
Erweiterung Shop: Statistiken und Rabatt
• Erstellen Sie eine Methode statistics, die den billigsten und den teuersten Artikel im Angebot,
sowie den durchschnittlichen Preis retourniert. (Definieren Sie eine passende Struktur für den
Datentyp des Returnwerts der Methode.)
• Sehen Sie für die Methode statistics einen Parameter vor, der es gestattet, eine Liste von
Kategorien vorzugeben. Bei der Berechnung der Statistik sollen nur Artikel berücksichtigt werden, die
einer der Kategorien, die in der Liste enthalten sind, angehören. Ist die Liste leer, so sollen alle Artikel
in die Berechnung mit einbezogen werden.
• Erstellen Sie eine Methode discount, die die Preise aller Artikel einer bestimmten Kategorie um einen
vorgegebenen Prozentsatz verändert. (Kategorie und Prozentsatz sind als Parameter an die Funktion
zu übergeben, zu retournieren ist die Anzahl der Artikel, für die sich der Preis verändert hat.)
• Verwenden Sie keine getter-Methoden, oder friend-Deklarationen, um auf die Werte der
Instanzvariablen in Item-Objekten zuzugreifen, sondern erweitern Sie die Klasse Item um
Methoden, die von statistics aufgerufen werden können, um das gewünschte Resultat zu
ermitteln.
9
Erweiterung Shop: Simples interaktives Testprogramm
• Realisieren Sie ein simples menügesteuertes Programm zum Testen Ihrer Klassen. Ein Dialog könnte
wie im folgenden Beispiel aussehen (Eingaben sind fett und unterstrichen dargestellt):
10
Artikel h(inzufuegen, b(earbeiten: b
EAN-Code? 1234567890128
1234567890128: Bonbonniere 25,40 Euro
24 exquisite Schokoladestücke + eine Überraschung
aendern B(ezeichnung, Be(schreibung, P(reis, F(ertig: e
...
Erweiterung Shop: Artikelliste sortieren
• Führen Sie folgende Änderungen an der Klasse Shop durch:
• Halten Sie die Artikelliste (das Warenangebot) nach EAN_code sortiert.
• Verwenden Sie Insertion Sort beim Einfügen neuer Artikel, um die Liste sortiert zu halten.
• Verwenden Sie bei der Suche nach Artikeln mittels EAN_code Binary Search.
11
Erweiterung EAN_code: Prüfziffer
• Ändern Sie die Methode check, sodass sie prüft, ob ein EAN_code plausibel ist. Verwenden Sie dazu
die Prüfziffer (erste Ziffer) des Codes. Die Prüfziffer wird berechnet, indem die Ziffern von rechts nach
links abwechselnd mit 3 und 1 gewichtet werden und die Summe modulo 10 ermittelt wird. Die
Prüfziffer ist die Differenz dieser Summe zu 10 modulo 10.
• z.B.: 1234567890128: (1*1+2*3+3*1+4*3+5*1+6*3+7*1+8*3+9*1+0*3+1*1+2*3)%10 = 2
(10-2)%10 = 8.
• Verändern Sie den Konstruktor so, dass bei einer falschen Prüfziffer eine Exception geworfen wird.
• Verändern Sie den Konstruktor außerdem so, dass auch 12stellige Codes als Parameter akzeptiert
werden und die nötige Prüfziffer automatisch berechnet und hinzugefügt wird.
12
Änderung EAN_code
• Um Speicherplatz zu sparen, soll die Speicherung des EAN_codes in einer Variablen vom Typ uint64_t
statt in einer String Variablen erfolgen.
• Ändern Sie Ihre Methoden entsprechend (beachten Sie, dass führende Nullen im EAN-Code erlaubt
sind).
• Lassen Sie das Interface der Klasse EAN_code unverändert, so dass die neue Version der Klasse
weiterhin mit allen anderen Klassen zusammenarbeiten kann.
• Welche Änderungen müssen Sie trotzdem in der Header-Datei durchführen. (Dies ist ein Beispiel für
die in C++ leider nicht konsequent durchgezogene Trennung von Interface und Implementierung. Die
Klassen, die EAN_code verwenden, müssen neu kompiliert werden, nur die neue Library
dazuzubinden reicht nicht aus. Es gibt Techniken, dieses Problem zu umgehen, allerdings werden
dazu C++ -Konzepte benötigt, die wir erst später kennen lernen werden.)
• Anmerkung: uint64_t muss nicht auf allen Systemen angeboten werden. Der Datentyp wird in der
Headerdatei cstdint definiert, die auf almighty bereits mit iostream inkludiert wird.
13
Erweiterung EAN_code: Barcode erstellen / lesen
• Aus einem EAN_code wird mittels eines recht komplexen Verfahrens ein Barcode erstellt (siehe
https://en.wikipedia.org/wiki/International_Article_Number#Binary_encoding_of_data_digits_into_E
AN-13_barcode).
• Erstellen Sie eine Methode to_barcode, die einen String liefert, der aus '|'–Zeichen und Leerzeichen
entsprechend den Strichen und Abständen im Barcode besteht.
• Erstellen Sie eine weitere Methode from_barcode, die eine Stringrepräsentation eines Barcodes
(wie im vorherigen Punkt beschrieben) Parameter erhält und den im Objekt gespeicherten EAN_code
entsprechend setzt, bzw. eine Exception wirft, wenn der Barcode keinen korrekten EAN_code
darstellt.
14
Erweiterung Shop: URL prüfen
• Prüfen Sie die URL, die im Shop angegeben wird, auf syntaktische Korrektheit (siehe
https://en.wikipedia.org/wiki/URL#Syntax).
• Die optionalen Teile authority part, query und fragment müssen nicht berücksichtigt werden.
15
16
 Definition und Verwendung von Klassen (inklusive Ausgabeoperator)
Ziel erreicht! Sie haben Klassen mit Instanzvariablen, Methoden und
Ausgabeoperator definiert und diese in Ihrem Programm verwendet.
Was haben Sie heute geschafft:
Applaus! Applaus!
https://www.youtube.com/watch?v=barWV7RWkq0
*/
