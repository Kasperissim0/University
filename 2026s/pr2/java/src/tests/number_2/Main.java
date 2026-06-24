//Setzen Sie in Zeile 2 Ihre Packagebezeichnung ein.
package tests.number_2;

import a12429280.*;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.TreeMap;
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
		var avg = potions.stream().mapToDouble(Potion::getWeight).average().orElse(0); var iterators = potions.stream()
				.collect(Collectors.partitioningBy(potion -> potion.getWeight() >= avg))
				.entrySet().stream().map(entry -> entry.getValue().stream()
				.sorted(((entry.getKey() ? Comparator.comparingInt(Potion::getPrice).reversed() : Comparator.comparingInt(Potion::getPrice))))
				.iterator()).toList();
		List<Potion> result = new ArrayList<>(); var flip = false; var la = iterators.getFirst(); var lb = iterators.getLast();
		
		while (la.hasNext() && lb.hasNext()) {
			if (flip) {
				result.add(la.next());
				result.add(lb.next());
			} else {
				result.add(lb.next());
				result.add(la.next());
			}
			flip = !flip;
		}
		return result.toArray(Potion[]::new);
	}
	// Methoden für Beispiel 1 Ende

	// Methoden für Beispiel 2
	// Diese Methode muss komplettiert werden
	public static TreeMap<Integer, Integer> mapItemsPerPriceCategory(List<MagicItem> items) {
		return items.stream().collect(Collectors.groupingBy(
			item -> item.getPrice() % 100,
			()   -> new TreeMap<>(Comparator.reverseOrder()),
			Collectors.summingInt(MagicItem::getWeight)
		));
	}
	// Methoden für Beispiel 2 Ende

	// Methoden für Beispiel 3 
	// Beispiel 3 wird in den Klassen Spell,
	// AttackingSpell und HazardousSpell gelöst
	// Methoden für Beispiel 3 Ende
	
	// Methoden für Beispiel 4
	// Diese Methode muss komplettiert werden
	public static List<Potion> selectPotions(List<Potion> list) {
		return list.stream().filter(potion -> Checks_Do_Not_Change.doSelect(potion::checkName)).toList();
	}
	// Methoden für Beispiel 4 Ende
}