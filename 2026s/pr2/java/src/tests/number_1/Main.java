//Setzen Sie in Zeile 2 Ihre Packagebezeichnung ein.
package tests.number_1;

import a12429280.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.stream.Collectors;

public class Main {
	
	public static void main(String[] args) {
		System.out.println("Achtung: hier findet nur ein grober Funktionalitätscheck statt.");
		System.out.println("Die eigentliche Beurteilung wird zu einem späteren Zeitpunkt durchgeführt.");

		// Hier die Aufgaben dekommentieren, die implementiert wurden
		// und geprüft werden sollen.
		// Nur dekommentierte Aufgaben werden beurteilt!
		Checks_Do_Not_Change.checkTask1(); //Aufgabe 1
		Checks_Do_Not_Change.checkTask2(); //Aufgabe 2
		Checks_Do_Not_Change.checkTask3(); //Aufgabe 3
		Checks_Do_Not_Change.checkTask4(); //Aufgabe 4
	}

	// Methoden für Beispiel 1
	// Diese Methode muss komplettiert werden
	public static Potion[] sortPotions(List<Potion> potions) {
		var lists = potions.stream().collect(Collectors.groupingBy(potion -> (potion.getPrice() % 3))); var iterators = List.of(
			lists.getOrDefault(0, List.of()).stream().sorted(Comparator.comparingInt(Potion::getWeight)).iterator(),
			lists.getOrDefault(1, List.of()).iterator(),
			lists.getOrDefault(2, List.of()).stream().sorted(Comparator.comparingInt(Potion::getWeight).reversed()).iterator()
		); List<Potion> result = new ArrayList<>(); var elementsLeft = true;
		
		while (elementsLeft) {
			elementsLeft = false;
			for (var it : iterators) {
				if (it.hasNext()) {
					result.add(it.next());
					elementsLeft = true;
				}
			}
		}
		return result.toArray(Potion[]::new);
	}
	// Methoden für Beispiel 1 Ende

	// Methoden für Beispiel 2
	// Diese Methode muss komplettiert werden
	public static TreeMap<Integer, TreeSet<MagicItem>> mapItemsPerPriceCategory(List<MagicItem> items) {
		return items.stream().collect(Collectors.groupingBy(
			potion -> (String.valueOf(potion.getPrice()).charAt(0) - '0'),
			TreeMap::new,
			Collectors.toCollection(() -> new TreeSet<>(Comparator.comparingInt(MagicItem::getWeight).reversed()))
		));
	}
	// Methoden für Beispiel 2 Ende

	// Methoden für Beispiel 3 
	// Beispiel 3 wird in den Klassen Spell,
	// AttackingSpell und AttackingProtectionSpell gelöst
	// Methoden für Beispiel 3 Ende
	
	// Methoden für Beispiel 4
	// Diese Methode muss komplettiert werden
	public static List<Potion> selectPotions(List<Potion> list) {
		return list.stream().filter(potion -> Checks_Do_Not_Change.doSelect(potion::checkName)).toList();
	}
	// Methoden für Beispiel 4 Ende
}