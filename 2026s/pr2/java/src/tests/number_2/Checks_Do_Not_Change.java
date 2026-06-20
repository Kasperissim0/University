//Setzen Sie in Zeile 2 Ihre Packagebezeichnung ein
package tests.number_2;

import a12429280.*;
// Machen Sie ab hier keine Änderungen in dieser Datei!
// Es werden 0 Punkte vergeben, wenn Sie hier Änderungen durchführen!

//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠

//      NO!                          MNO!
//     MNO!!         [NBK]          MNNOO!
//   MMNO!                           MNNOO!!
// MNOONNOO!   MMMMMMMMMMPPPOII!   MNNO!!!!
// !O! NNO! MMMMMMMMMMMMMPPPOOOII!! NO!
//       ! MMMMMMMMMMMMMPPPPOOOOIII! !
//        MMMMMMMMMMMMPPPPPOOOOOOII!!
//        MMMMMOOOOOOPPPPPPPPOOOOMII!
//        MMMMM..    OPPMMP    .,OMI!
//        MMMM::   o.,OPMP,.o   ::I!!
//          NNM:::.,,OOPM!P,.::::!!
//         MMNNNNNOOOOPMO!!IIPPO!!O!
//         MMMMMNNNNOO:!!:!!IPPPPOO!
//          MMMMMNNOOMMNNIIIPPPOO!!
//             MMMONNMMNNNIIIOO!
//           MN MOMMMNNNIIIIIO! OO
//          MNO! IiiiiiiiiiiiI OOOO
//     NNN.MNO!   O!!!!!!!!!O   OONO NO!
//    MNNNNNO!    OOOOOOOOOOO    MMNNON!
//      MNNNNO!    PPPPPPPPP    MMNON!
//         OO!                   ON!

//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠
//☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.TreeMap;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Checks_Do_Not_Change {
	//*************************************************************************
	//*************************************************************************
	// Weiterlesen auf eigene Gefahr ...
	// Hier befinden sich nur die für das Testen verwendeten Programmteile
	//*************************************************************************
	//*************************************************************************
	// Hier sind keine Änderungen des vorgegebenen Codes erlaubt
	private static ArrayList<Spell> spellsList = new ArrayList<>(
			Arrays.asList(
					new AttackingSpell("Attack", 10, MagicLevel.ADEPT,
							true, false, 10),
					new AttackingSpell("Attack 1", 20, MagicLevel.EXPERT,
							false, true, 30),
					new AttackingSpell("Attack 2", 30, MagicLevel.NOOB,
							false, false, 20),
					new AttackingSpell("Attack 3", 15, MagicLevel.STUDENT,
							true, true, 15),
					new AttackingSpell("Attack 4", 17, MagicLevel.ADEPT,
							true, false, 12),
					new AttackingSpell("Attack 5", 21, MagicLevel.EXPERT,
							false, true, 9),
					new AttackingSpell("Attack 6", 9, MagicLevel.NOOB,
							false, false, 17),
					new AttackingSpell("Attack 7", 13, MagicLevel.STUDENT,
							true, true, 8),
					new HealingSpell("Heal", 10, MagicLevel.ADEPT,
							true, false, 10),
					new HealingSpell("Heal 1", 20, MagicLevel.EXPERT,
							false, true, 30),
					new HealingSpell("Heal 2", 30, MagicLevel.NOOB,
							false, false, 20),
					new HealingSpell("Heal 3", 15, MagicLevel.STUDENT,
							true, true, 15),
					new HealingSpell("Heal 4", 17, MagicLevel.ADEPT,
							true, false, 12))
			);
	static {
		spellsList.add(new ProtectingSpell("Protect", 5, MagicLevel.NOOB,
				new HashSet<AttackingSpell>(Arrays.asList(
						(AttackingSpell)spellsList.get(0)))));
		spellsList.add(new ProtectingSpell("Protect 1", 10, MagicLevel.NOOB,
				new HashSet<AttackingSpell>(Arrays.asList(
						(AttackingSpell)spellsList.get(3),
						(AttackingSpell)spellsList.get(6),
						(AttackingSpell)spellsList.get(1)))));
	}
	//String name, int usages, int price, int weight, int health, int mana, List<Spell> spells
	private static ArrayList<MagicItem> itemsList = new ArrayList<>(
			Arrays.asList(
					new HealthPotion("Health potion", 10, 24, 12, 20),
					new ManaPotion("Mana potion", 4, 10, 5, 7),
					new Concoction("Concoction", 1, 3, 15, 15, -3, 
							new ArrayList<Spell>()),
					new Scroll("Scroll", 15, 28, 2, spellsList.get(0)),
					new ManaPotion("Mana potion 1", 9, 13, 22, 50),
					new Scroll("Scroll 1", 21, 4, 7, spellsList.get(1)),
					new HealthPotion("Health potion 1", 10, 27, 19, 16),
					new Concoction("Bad Days", 2, 22, 17, -2, 7, 
							new ArrayList<Spell>()),
					new Concoction("Good Morning", 1, 20, 8, 19, 3, 
							new ArrayList<Spell>()),
					new Concoction("Omen", 3, 30, 31, -2, 7, 
							new ArrayList<Spell>()),
					new Concoction("Surprise", 5, 21, 21, -2, 7, 
							new ArrayList<Spell>()),
					new Concoction("sunrise", 2, 26, 14, -2, 7, 
							new ArrayList<Spell>()),
					new Concoction("Ahoi", 4, 25, 4, -2, 7, 
							new ArrayList<Spell>()))
			); 
	//String name, int usages, int price, int weight, int health, int mana, List<Spell> spells
    private static ArrayList<Concoction> additionalConcoctions = new ArrayList<>(
    		Arrays.asList(
					new Concoction("Stun", 1, 30, 25, -2, 7, 
							new ArrayList<Spell>()),
					new Concoction("bleed", 4, 35, 30, -2, 7, 
							new ArrayList<Spell>()),
					new Concoction("Happy", 7, 20, 35, -2, 7, 
							new ArrayList<Spell>()),
					new Concoction("Fun", 10, 70, 45, -2, 7, 
							new ArrayList<Spell>()))
    		);
    private static ArrayList<Potion> additionalPotions = new ArrayList<>(
    		Arrays.asList(
					new HealthPotion("Bleed", 10, 18, 40, 20),
					new ManaPotion("Fun", 4, 2, 35, 7),
					new HealthPotion("Fun", 10, 56, 33, 20),
					new ManaPotion("Stun", 4, 8, 37, 7))
    		);
    public static ArrayList<Concoction> someMoreConcoctions = new ArrayList<>(
    		Arrays.asList(
					new Concoction("Fun", 2, 75, 50, -2, 7, 
							new ArrayList<Spell>()),
					new Concoction("Happy", 2, 19, 51, -2, 7, 
							new ArrayList<Spell>()),
					new Concoction("Happier", 4, 40, 52, -2, 7, 
							new ArrayList<Spell>()),
					new Concoction("Fun", 5, 74, 53, -2, 7, 
							new ArrayList<Spell>()),
					new Concoction("Fun", 5, 69, 54, -2, 7, 
							new ArrayList<Spell>()),
					new Concoction("Happy", 4, 17, 55, -2, 7, 
							new ArrayList<Spell>())
    				)
    		);
    		
    //name level basicHP HP basicMP MP money knownSpells protectedFrom carryingCapacity inventory
    private static ArrayList<Wizard> wizardsList = new ArrayList<>(
    		Arrays.asList(
    				new Wizard("Harry", MagicLevel.EXPERT, 100, 100, 1000, 1000,
    						1234, new HashSet<Spell>(),
    						new HashSet<AttackingSpell>(), 100,
    						new HashSet<Tradeable>()),
    				new Wizard("Hermione", MagicLevel.EXPERT, 1000, 1000, 1000, 1000,
    						12, new HashSet<Spell>(),
    						new HashSet<AttackingSpell>(), 100,
    						new HashSet<Tradeable>()),
    				new Wizard("Voldemort", MagicLevel.EXPERT, 1000, 1000, 1000, 1000,
    						7, new HashSet<Spell>(spellsList),
    						new HashSet<AttackingSpell>(), 100,
    						new HashSet<Tradeable>())
    		));
	public static void checkTask1() {
	try {
		System.out.println("\nÜberprüfung Aufgabe 1");
		Class<?> potionClass = Potion.class;
		Field nameField = getFieldForClass(potionClass,"name");
		if (nameField==null)
			return;
		nameField.setAccessible(true);
		Field weightField = getFieldForClass(potionClass,"weight");
		if (weightField==null)
			return;
		weightField.setAccessible(true);
		Field priceField = getFieldForClass(potionClass,"price");
		if (priceField==null)
			return;
		priceField.setAccessible(true);
		Field usagesField = getFieldForClass(potionClass,"usages");
		if (usagesField==null)
			return;
		usagesField.setAccessible(true);
		List<Potion> pList = itemsList.stream()
				.filter(o->o instanceof Potion).map(o->(Potion)o).toList();
		String inputPotions = pList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		String result = resultTask1ToString(Main.sortPotions(pList), nameField, priceField, weightField);
		String expectedResult = "[Omen; 30; 31], [Concoction; 3; 15], [Mana potion; 10; 5], [Health potion 1; 27; 19], [Bad Days; 22; 17], [Good Morning; 20; 8], [Health potion; 24; 12], [Surprise; 21; 21], [Mana potion 1; 13; 22], [Ahoi; 25; 4]";
		if (!checkTask1Result(inputPotions, result, expectedResult))
			return;

		pList = itemsList.stream()
				.filter(o->o instanceof Potion)
				.map(o->(Potion)o)
				.collect(Collectors.toCollection(ArrayList::new));
		pList.addAll(additionalPotions.stream()
				.filter(o->o instanceof Potion)
				.map(o->(Potion)o)
				.toList());
		inputPotions = pList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		result = resultTask1ToString(Main.sortPotions(pList), nameField, priceField, weightField);
		expectedResult = "[Fun; 56; 33], [Concoction; 3; 15], [Mana potion; 10; 5], [Omen; 30; 31], [Surprise; 21; 21], [Good Morning; 20; 8], [Bad Days; 22; 17], [Bleed; 18; 40], [Mana potion 1; 13; 22], [Health potion; 24; 12], [Ahoi; 25; 4], [Stun; 8; 37], [Fun; 2; 35], [sunrise; 26; 14]";
		if (!checkTask1Result(inputPotions, result, expectedResult))
			return;

		pList.addAll(additionalConcoctions);
		pList.addAll(someMoreConcoctions);
		inputPotions = pList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		result = resultTask1ToString(Main.sortPotions(pList), nameField, priceField, weightField);
		expectedResult = "[Fun; 75; 50], [Concoction; 3; 15], [Mana potion; 10; 5], [Fun; 74; 53], [Fun; 70; 45], [Mana potion 1; 13; 22], [Good Morning; 20; 8], [Fun; 69; 54], [Fun; 56; 33], [Surprise; 21; 21], [Bad Days; 22; 17], [Happier; 40; 52], [Omen; 30; 31], [Health potion; 24; 12], [Ahoi; 25; 4], [Happy; 20; 35], [Happy; 19; 51], [sunrise; 26; 14], [Health potion 1; 27; 19], [Bleed; 18; 40], [Happy; 17; 55], [Stun; 30; 25], [bleed; 35; 30], [Stun; 8; 37]";
		if (!checkTask1Result(inputPotions, result, expectedResult))
			return;
		
		ArrayList<Potion> symmetricList = new ArrayList<>(
				Arrays.asList(
						new HealthPotion("Health potion", 10, 4, 12, 20),
						new ManaPotion("Mana potion", 4, 5, 17, 7),
						new Concoction("Concoction", 1, 3, 8, 15, -3, 
								new ArrayList<Spell>()),
						new ManaPotion("Mana potion 1", 9, 7, 10, 50),
						new HealthPotion("Health potion 1", 2, 2, 6, 16),
						new Concoction("Bad Days", 2, 1, 7, -2, 7, 
								new ArrayList<Spell>())
		));
		pList = symmetricList;
		inputPotions = pList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		result = resultTask1ToString(Main.sortPotions(pList), nameField, priceField, weightField);
		expectedResult = "[Mana potion 1; 7; 10], [Bad Days; 1; 7], [Health potion 1; 2; 6], [Mana potion; 5; 17], [Health potion; 4; 12], [Concoction; 3; 8]";
		if (!checkTask1Result(inputPotions, result, expectedResult))
			return;

		pList = new ArrayList<>();
		inputPotions = pList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		result = resultTask1ToString(Main.sortPotions(pList), nameField, priceField, weightField);
		expectedResult = "";
		if (!checkTask1Result(inputPotions, result, expectedResult))
			return;
		
		pList = new ArrayList<>(
				Arrays.asList(
						new HealthPotion("Health potion", 10, 4, 12, 20),
						new ManaPotion("Mana potion", 4, 5, 5, 7),
						new Concoction("Concoction", 1, 3, 12, 15, -3, 
								new ArrayList<Spell>()),
						new ManaPotion("Mana potion 1", 9, 7, 10, 50),
						new HealthPotion("Health potion 1", 2, 6, 10, 16),
						new Concoction("Bad Days", 2, 8, 10, -2, 7, 
								new ArrayList<Spell>())
		));
		inputPotions = pList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		result = resultTask1ToString(Main.sortPotions(pList), nameField, priceField, weightField);
		expectedResult = "[Bad Days; 8; 10], [Mana potion; 5; 5]";
		if (!checkTask1Result(inputPotions, result, expectedResult))
			return;

		System.out.println("OK \u2713");
	} catch (Throwable t) {
		System.out.println("Unerwartete Exception "+t.getMessage());
		System.out.println("Fehler \u2717");
	}
	}
	
	private static String resultTask1ToString(Potion[] l, Field nameField, Field priceField, Field weightField) {
		return Arrays.stream(l)
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
	}

	public static boolean checkTask1Result(String inputPotions, 
			String result, String expectedResult) {
		if (!expectedResult.equals(result)) {
			System.out.println("Aufruf der Methode sortPotions mit den Parametern"
					+ " (nur die relevanten Werte 'name', 'price' und 'weight' werden"
					+ " angezeigt)\npotions = ["+inputPotions+"]\n"
					+ "liefert:\n\t"+result+"\naber das erwartete Ergebnis ist\n\t"
					+expectedResult);
			System.out.println("Fehler \u2717");
			return false;
		}
		else
			return true;
	}
	public static void checkTask2() {
	try {
		System.out.println("\nÜberprüfung Aufgabe 2");
		Class<?> magicItemClass = MagicItem.class;
		Field nameField = getFieldForClass(magicItemClass,"name");
		if (nameField==null)
			return;
		nameField.setAccessible(true);
		Field priceField = getFieldForClass(magicItemClass,"price");
		if (priceField==null)
			return;
		priceField.setAccessible(true);
		Field weightField = getFieldForClass(magicItemClass,"weight");
		if (weightField==null)
			return;
		weightField.setAccessible(true);
		List<MagicItem> iList = itemsList.stream().toList();
		TreeMap<Integer, Integer> tm = Main.mapItemsPerPriceCategory(iList);
		String inputList = iList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		String result = tm.entrySet().stream().map(o->o.getKey().toString()
				+": "+o.getValue())
				//.stream() //.sorted(Comparator.comparing(elem -> getMyFieldValue(nameField, elem)))
				//.map(e->objFieldsToString(e, nameField, priceField))
				//.collect(Collectors.joining(", ")))
				.collect(Collectors.joining("\n\t"));
		String expectedResult = "30: 31\n"
				+ "	28: 2\n"
				+ "	27: 19\n"
				+ "	26: 14\n"
				+ "	25: 4\n"
				+ "	24: 12\n"
				+ "	22: 17\n"
				+ "	21: 21\n"
				+ "	20: 8\n"
				+ "	13: 22\n"
				+ "	10: 5\n"
				+ "	4: 7\n"
				+ "	3: 15";
		if (!checkTask2Result(inputList, result, expectedResult))
			return;
		
		iList = itemsList.stream().collect(Collectors.toCollection(ArrayList::new));
		iList.addAll(additionalPotions);
		iList.addAll(someMoreConcoctions);
		tm = Main.mapItemsPerPriceCategory(iList);
		inputList = iList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		result = tm.entrySet().stream().map(o->o.getKey().toString()
				+": "+o.getValue())
				//.stream() //.sorted(Comparator.comparing(elem -> getMyFieldValue(nameField, elem)))
				//.map(e->objFieldsToString(e, nameField, priceField))
				//.collect(Collectors.joining(", ")))
				.collect(Collectors.joining("\n\t"));
		expectedResult = "75: 50\n"
				+ "	74: 53\n"
				+ "	69: 54\n"
				+ "	56: 33\n"
				+ "	40: 52\n"
				+ "	30: 31\n"
				+ "	28: 2\n"
				+ "	27: 19\n"
				+ "	26: 14\n"
				+ "	25: 4\n"
				+ "	24: 12\n"
				+ "	22: 17\n"
				+ "	21: 21\n"
				+ "	20: 8\n"
				+ "	19: 51\n"
				+ "	18: 40\n"
				+ "	17: 55\n"
				+ "	13: 22\n"
				+ "	10: 5\n"
				+ "	8: 37\n"
				+ "	4: 7\n"
				+ "	3: 15\n"
				+ "	2: 35";
		if (!checkTask2Result(inputList, result, expectedResult))
			return;
		
		iList = someMoreConcoctions.stream().collect(Collectors.toCollection(ArrayList::new));
		tm = Main.mapItemsPerPriceCategory(iList);
		inputList = iList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		result = tm.entrySet().stream().map(o->o.getKey().toString()
				+": "+o.getValue())
				//.stream() //.sorted(Comparator.comparing(elem -> getMyFieldValue(nameField, elem)))
				//.map(e->objFieldsToString(e, nameField, priceField))
				//.collect(Collectors.joining(", ")))
				.collect(Collectors.joining("\n\t"));
		expectedResult = "75: 50\n"
				+ "	74: 53\n"
				+ "	69: 54\n"
				+ "	40: 52\n"
				+ "	19: 51\n"
				+ "	17: 55";
		if (!checkTask2Result(inputList, result, expectedResult))
			return;
		
		iList = additionalPotions.stream().collect(Collectors.toCollection(ArrayList::new));
		tm = Main.mapItemsPerPriceCategory(iList);
		inputList = iList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		result = tm.entrySet().stream().map(o->o.getKey().toString()
				+": "+o.getValue())
				//.stream() //.sorted(Comparator.comparing(elem -> getMyFieldValue(nameField, elem)))
				//.map(e->objFieldsToString(e, nameField, priceField))
				//.collect(Collectors.joining(", ")))
				.collect(Collectors.joining("\n\t"));
		expectedResult = "56: 33\n"
				+ "	18: 40\n"
				+ "	8: 37\n"
				+ "	2: 35";
		if (!checkTask2Result(inputList, result, expectedResult))
			return;

		iList = new ArrayList<>();
		tm = Main.mapItemsPerPriceCategory(iList);
		inputList = iList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		result = tm.entrySet().stream().map(o->o.getKey().toString()
				+": "+o.getValue())
				//.stream() //.sorted(Comparator.comparing(elem -> getMyFieldValue(nameField, elem)))
				//.map(e->objFieldsToString(e, nameField, priceField))
				//.collect(Collectors.joining(", ")))
				.collect(Collectors.joining("\n\t"));
		expectedResult = "";
		if (!checkTask2Result(inputList, result, expectedResult))
			return;
		
		iList = new ArrayList<>(
				Arrays.asList(
						new HealthPotion("Health potion", 10, 912345678, 12, 20),
						new ManaPotion("Mana potion", 4, 97854632, 5, 7),
						new Concoction("Concoction", 1, 1032547678, 13, 15, -3, 
								new ArrayList<Spell>()),
						new ManaPotion("Mana potion 1", 9, 9375648, 10, 50),
						new HealthPotion("Health potion 1", 2, 9999, 11, 16),
						new Concoction("Bad Days", 2, 9287499, 14, -2, 7, 
								new ArrayList<Spell>())
		));
		tm = Main.mapItemsPerPriceCategory(iList);
		inputList = iList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		result = tm.entrySet().stream().map(o->o.getKey().toString()
				+": "+o.getValue())
				//.stream() //.sorted(Comparator.comparing(elem -> getMyFieldValue(nameField, elem)))
				//.map(e->objFieldsToString(e, nameField, priceField))
				//.collect(Collectors.joining(", ")))
				.collect(Collectors.joining("\n\t"));
		expectedResult = "99: 25\n"
				+ "	78: 25\n"
				+ "	48: 10\n"
				+ "	32: 5";
		if (!checkTask2Result(inputList, result, expectedResult))
			return;
		
		iList = new ArrayList<>(
				Arrays.asList(
						new HealthPotion("Health potion", 10, 912345678, 12, 20),
						new ManaPotion("Mana potion", 4, 97854632, 5, 7),
						new Concoction("Concoction", 1, 1032547678, 13, 15, -3, 
								new ArrayList<Spell>()),
						new ManaPotion("Mana potion 1", 9, 9375626, 10, 50),
						new HealthPotion("Health potion 1", 2, 9999, 11, 16),
						new Concoction("Bad Days", 2, 9287499, 14, -2, 7, 
								new ArrayList<Spell>()),
						new HealthPotion("Health potion", 10, 912345678, 12, 20),
						new ManaPotion("Mana potion", 4, 97854632, 5, 7),
						new Concoction("Concoction", 1, 1032547678, 13, 15, -3, 
								new ArrayList<Spell>()),
						new ManaPotion("Mana potion 1", 9, 9375648, 10, 50),
						new HealthPotion("Health potion 1", 2, 9999, 11, 16),
						new Concoction("Bad Days", 2, 9287499, 14, -2, 7, 
								new ArrayList<Spell>()),
						new HealthPotion("Health potion", 10, 912345678, 12, 20),
						new ManaPotion("Mana potion", 4, 97854632, 5, 7),
						new Concoction("Concoction", 1, 1032547678, 13, 15, -3, 
								new ArrayList<Spell>()),
						new ManaPotion("Mana potion 1", 9, 9375626, 10, 50),
						new HealthPotion("Health potion 1", 2, 9999, 11, 16),
						new Concoction("Bad Days", 2, 9287499, 14, -2, 7, 
								new ArrayList<Spell>()),
						new HealthPotion("Health potion", 10, 912345678, 12, 20),
						new ManaPotion("Mana potion", 4, 97854632, 5, 7),
						new Concoction("Concoction", 1, 1032547678, 13, 15, -3, 
								new ArrayList<Spell>()),
						new ManaPotion("Mana potion 1", 9, 9375648, 10, 50),
						new HealthPotion("Health potion 1", 2, 9999, 11, 16),
						new Concoction("Bad Days", 2, 9287499, 14, -2, 7, 
								new ArrayList<Spell>())
		));
		tm = Main.mapItemsPerPriceCategory(iList);
		inputList = iList.stream()
				.map(o->objFieldsToString(o, nameField, priceField, weightField))
				.collect(Collectors.joining(", "));
		result = tm.entrySet().stream().map(o->o.getKey().toString()
				+": "+o.getValue())
				//.stream() //.sorted(Comparator.comparing(elem -> getMyFieldValue(nameField, elem)))
				//.map(e->objFieldsToString(e, nameField, priceField))
				//.collect(Collectors.joining(", ")))
				.collect(Collectors.joining("\n\t"));
		expectedResult = "99: 100\n"
				+ "	78: 100\n"
				+ "	48: 20\n"
				+ "	32: 20\n"
				+ "	26: 20";
		if (!checkTask2Result(inputList, result, expectedResult))
			return;
		
		System.out.println("OK \u2713");
	} catch (Throwable t) {
		System.out.println("Unerwartete Exception "+t.getMessage());
		System.out.println("Fehler \u2717");
	}
	} 
	
	/*
	private static String resultTask2ToString(Set<Potion> potions,
			Field nameField) {
		return potions.stream()
				.map(o->objFieldsToString(o, nameField))
				.sorted()
				.collect(Collectors.joining(", "));
	}
	*/
	
	private static boolean checkTask2Result(String inputList,
			String result, String expectedResult) {
		if (!expectedResult.equals(result)) {
			System.out.println("Aufruf der Methode mapItemsPerPriceCategory mit den Parametern"
					+ " (nur die relevanten Wert 'name', 'price' und 'weight' für"
					+ " MagicItems werden"
					+ " angezeigt)\n"
					+ "items = ["+inputList+"] \n"
					+ "liefert:\n\t"+result+"\naber das erwartete Ergebnis ist\n\t"
					+ expectedResult);
			System.out.println("Fehler \u2717");
			return false;
		}
		else
			return true;
	}

	@SuppressWarnings("unchecked")
	public static void checkTask3() {
	try {
		System.out.println("\nÜberprüfung Aufgabe 3");
		Class<?> theSpellClass;
		try {
			theSpellClass = Class.forName(Spell.class.getPackage().getName()+".HazardousSpell");
		} catch (ClassNotFoundException e) {
			System.out.println("Klasse HazardousSpell nicht implementiert in package "+Wizard.class.getPackage().getName());
			System.out.println("Fehler \u2717");
			return;
		}
		//String name, int manaCost, MagicLevel levelNeeded, boolean type, boolean percentage, int amount
		AttackingSpell apsSpell = null;
		try {
			apsSpell = (AttackingSpell)theSpellClass.getConstructor(String.class, int.class, MagicLevel.class, boolean.class, boolean.class, int.class)
				.newInstance("Test Spell", 20, MagicLevel.NOOB, true, false, 7);
		} catch (InstantiationException | IllegalAccessException | IllegalArgumentException | InvocationTargetException
				| NoSuchMethodException | SecurityException e) {
			System.out.println("Class HazardousSpell Konstruktor kann nicht aufgerufen werden");
			System.out.println("Fehler \u2717");
			return;
		}
		String originalSpell = apsSpell.toString();
		
		Class<?> wizardClass = Wizard.class;
		Field wizKnownSpellsField = getFieldForClass(wizardClass, "knownSpells"); 
		if (wizKnownSpellsField==null)
			return;
		wizKnownSpellsField.setAccessible(true);
		Field wizHPField = getFieldForClass(wizardClass,"HP");
		if (wizHPField==null)
			return;
		wizHPField.setAccessible(true);
		Field wizMPField = getFieldForClass(wizardClass,"MP");
		if (wizMPField==null)
			return;
		wizMPField.setAccessible(true);
		Field wizProtectedFromField = getFieldForClass(wizardClass,"protectedFrom");
		if (wizProtectedFromField==null)
			return;
		wizProtectedFromField.setAccessible(true);
		Field theSpellManaCostField = getFieldForClass(theSpellClass,"manaCost");
		if (theSpellManaCostField==null)
			return;
		theSpellManaCostField.setAccessible(true);
		Field theSpellAmountField = getFieldForClass(theSpellClass,"amount");
		if (theSpellAmountField==null)
			return;
		theSpellAmountField.setAccessible(true);
		Field theSpellTypeField = getFieldForClass(theSpellClass,"type");
		if (theSpellTypeField==null)
			return;
		theSpellTypeField.setAccessible(true);
		Field theSpellPercentageField = getFieldForClass(theSpellClass,"percentage");
		if (theSpellPercentageField==null)
			return;
		theSpellPercentageField.setAccessible(true);

		Wizard theWizard = wizardsList.get(0);
		String originalWizard = getWizardString(theWizard, wizProtectedFromField);
		if (!theWizard.learn(apsSpell)) {
			System.out.println(originalWizard);
			System.out.println("konnte HazardousSpell");
			System.out.println(apsSpell);
			System.out.println("nicht lernen.");
			System.out.println("Implementierung nicht spezifikationskonform.");
			System.out.println("Fehler \u2717");
			return;
		}
		try {
			if (((Set<Spell>)(wizKnownSpellsField.get(theWizard))).size()!=1
					|| !((Set<Spell>)(wizKnownSpellsField.get(theWizard))).contains(apsSpell)) {
				System.out.println(originalWizard);
				System.out.println("hat HazardousSpell");
				System.out.println(apsSpell);
				System.out.println("nicht korrekt gelernt");
				System.out.println("Implementierung nicht spezifikationskonform.");
				System.out.println("Fehler \u2717");
				return;
			}
		} catch (IllegalArgumentException | IllegalAccessException | ClassCastException e) {
			System.out.println(originalWizard);
			System.out.println("hat HazardousSpell");
			System.out.println(apsSpell);
			System.out.println("nicht korrekt gelernt");
			System.out.println("Implementierung nicht spezifikationskonform.");
			System.out.println("Fehler \u2717");
			return;
		}

		Wizard theSecondWizard = wizardsList.get(1);
		String originalSecondWizard = getWizardString(theSecondWizard, wizProtectedFromField);
		if (!theSecondWizard.learn(apsSpell)) {
			System.out.println(originalSecondWizard);
			System.out.println("konnte HazardousSpell");
			System.out.println(apsSpell);
			System.out.println("nicht lernen.");
			System.out.println("Implementierung nicht spezifikationskonform.");
			System.out.println("Fehler \u2717");
			return;
		}
		try {
			if (((Set<Spell>)(wizKnownSpellsField.get(theSecondWizard))).size()!=1
					|| !((Set<Spell>)(wizKnownSpellsField.get(theSecondWizard))).contains(apsSpell)) {
				System.out.println(originalSecondWizard);
				System.out.println("hat HazardousSpell");
				System.out.println(apsSpell);
				System.out.println("nicht korrekt gelernt");
				System.out.println("Implementierung nicht spezifikationskonform.");
				System.out.println("Fehler \u2717");
				return;
			}
		} catch (IllegalArgumentException | IllegalAccessException | ClassCastException e) {
			System.out.println(originalSecondWizard);
			System.out.println("hat HazardousSpell");
			System.out.println(apsSpell);
			System.out.println("nicht korrekt gelernt");
			System.out.println("Implementierung nicht spezifikationskonform.");
			System.out.println("Fehler \u2717");
			return;
		}

		originalWizard = getWizardString(theWizard, wizProtectedFromField);
		originalSecondWizard = getWizardString(theSecondWizard, wizProtectedFromField);
		String expectedResultWizard = "{[Harry(****): 90/100 980/1000; 1234 Knuts; knows [[Test Spell(*): 20 mana; -7 HP]]; carries []] protectedFrom: []}";
		String expectedResultSecondWizard = "{[Hermione(****): 993/1000 1000/1000; 12 Knuts; knows [[Test Spell(*): 20 mana; -7 HP]]; carries []] protectedFrom: []}";
		if (!theWizard.castSpell(apsSpell, theSecondWizard)) {
			System.out.println(originalWizard);
			System.out.println("castSpell HazardousSpell "+ originalSpell + " zum ersten Mal auf\n" + originalSecondWizard + "sollte true retournieren");
			System.out.println("Aber false wurde retourniert");
			System.out.println("Fehler \u2717");
			return;
		};
		String resultWizard = getWizardString(theWizard, wizProtectedFromField);
		String resultSecondWizard = getWizardString(theSecondWizard, wizProtectedFromField);
		if (!resultWizard.equals(expectedResultWizard) || !resultSecondWizard.equals(expectedResultSecondWizard)) {
			System.out.println(originalWizard);
			System.out.println("castSpell HazardousSpell " + originalSpell +" zum ersten Mal auf\n" + originalSecondWizard);
			if (!resultWizard.equals(expectedResultWizard)) {
				System.out.println("sollte Harry auf " + expectedResultWizard + " ändern.");
				System.out.println("aber der Zustand änderte sich auf " + resultWizard);
			}
			if (!resultSecondWizard.equals(expectedResultSecondWizard)) {
				System.out.println("sollte Hermione auf " + expectedResultSecondWizard + " ändern.");
				System.out.println("aber der Zustand änderte sich auf " + resultSecondWizard);
			}
			System.out.println("Fehler \u2717");
			return;
		}

		originalWizard = getWizardString(theWizard, wizProtectedFromField);
		originalSecondWizard = getWizardString(theSecondWizard, wizProtectedFromField);
		expectedResultWizard = "{[Harry(****): 70/100 960/1000; 1234 Knuts; knows [[Test Spell(*): 20 mana; -7 HP]]; carries []] protectedFrom: []}";
		expectedResultSecondWizard = "{[Hermione(****): 986/1000 1000/1000; 12 Knuts; knows [[Test Spell(*): 20 mana; -7 HP]]; carries []] protectedFrom: []}";
		if (!theWizard.castSpell(apsSpell, theSecondWizard)) {
			System.out.println(originalSecondWizard);
			System.out.println("castSpell HazardousSpell "+ originalSpell + " zum zweiten Mal auf\n" + originalSecondWizard + "sollte true retournieren");
			System.out.println("Aber false wurde retourniert");
			System.out.println("Fehler \u2717");
			return;
		};
		resultWizard = getWizardString(theWizard, wizProtectedFromField);
		resultSecondWizard = getWizardString(theSecondWizard, wizProtectedFromField);
		if (!resultWizard.equals(expectedResultWizard) || !resultSecondWizard.equals(expectedResultSecondWizard)) {
			System.out.println(originalWizard);
			System.out.println("castSpell HazardousSpell " + originalSpell +" zum zweiten Mal auf\n" + originalSecondWizard);
			if (!resultWizard.equals(expectedResultWizard)) {
				System.out.println("sollte Harry auf " + expectedResultWizard + " ändern.");
				System.out.println("aber der Zustand änderte sich auf " + resultWizard);
			}
			if (!resultSecondWizard.equals(expectedResultSecondWizard)) {
				System.out.println("sollte Hermione auf " + expectedResultSecondWizard + " ändern.");
				System.out.println("aber der Zustand änderte sich auf " + resultSecondWizard);
			}
			System.out.println("Fehler \u2717");
			return;
		}

		originalWizard = getWizardString(theWizard, wizProtectedFromField);
		originalSecondWizard = getWizardString(theSecondWizard, wizProtectedFromField);
		expectedResultWizard = "{[Harry(****): 40/100 940/1000; 1234 Knuts; knows [[Test Spell(*): 20 mana; -7 HP]]; carries []] protectedFrom: []}";
		expectedResultSecondWizard = "{[Hermione(****): 979/1000 1000/1000; 12 Knuts; knows [[Test Spell(*): 20 mana; -7 HP]]; carries []] protectedFrom: []}";
		if (!theWizard.castSpell(apsSpell, theSecondWizard)) {
			System.out.println(originalWizard);
			System.out.println("castSpell HazardousSpell "+ originalSpell + " zum dritten Mal auf\n" + originalSecondWizard + "sollte true retournieren");
			System.out.println("Aber false wurde retourniert");
			System.out.println("Fehler \u2717");
			return;
		};
		resultWizard = getWizardString(theWizard, wizProtectedFromField);
		resultSecondWizard = getWizardString(theSecondWizard, wizProtectedFromField);
		if (!resultWizard.equals(expectedResultWizard) || !resultSecondWizard.equals(expectedResultSecondWizard)) {
			System.out.println(originalWizard);
			System.out.println("castSpell HazardousSpell " + originalSpell +" zum dritten Mal auf\n" + originalSecondWizard);
			if (!resultWizard.equals(expectedResultWizard)) {
				System.out.println("sollte Harry auf " + expectedResultWizard + " ändern.");
				System.out.println("aber der Zustand änderte sich auf " + resultWizard);
			}
			if (!resultSecondWizard.equals(expectedResultSecondWizard)) {
				System.out.println("sollte Hermione auf " + expectedResultSecondWizard + " ändern.");
				System.out.println("aber der Zustand änderte sich auf " + resultSecondWizard);
			}
			System.out.println("Fehler \u2717");
			return;
		}

		/*
		((Set<AttackingSpell>)wizProtectedFromField.get(theWizard)).clear();
		((Set<AttackingSpell>)wizProtectedFromField.get(theSecondWizard)).clear();
		theSpellManaCostField.setInt(apsSpell,5);
		theSpellTypeField.setBoolean(apsSpell, false);
		theSpellPercentageField.setBoolean(apsSpell, true);
		theSpellAmountField.setInt(apsSpell, 10);
		originalSpell = apsSpell.toString();
		*/
		originalWizard = getWizardString(theWizard, wizProtectedFromField);
		originalSecondWizard = getWizardString(theSecondWizard, wizProtectedFromField);
		expectedResultWizard = "{[Harry(****): 40/100 940/1000; 1234 Knuts; knows [[Test Spell(*): 20 mana; -7 HP]]; carries []] protectedFrom: []}";
		expectedResultSecondWizard = "{[Hermione(****): 979/1000 1000/1000; 12 Knuts; knows [[Test Spell(*): 20 mana; -7 HP]]; carries []] protectedFrom: []}";
		if (!theWizard.castSpell(apsSpell, theSecondWizard)) {
			System.out.println(originalWizard);
			System.out.println("castSpell HazardousSpell "+ originalSpell + " zum vierten auf\n" + originalSecondWizard + "sollte true retournieren");
			System.out.println("Aber false wurde retourniert");
			System.out.println("Fehler \u2717");
			return;
		};
		resultWizard = getWizardString(theWizard, wizProtectedFromField);
		resultSecondWizard = getWizardString(theSecondWizard, wizProtectedFromField);
		if (!resultWizard.equals(expectedResultWizard) || !resultSecondWizard.equals(expectedResultSecondWizard)) {
			System.out.println(originalWizard);
			System.out.println("castSpell HazardousSpell " + originalSpell +" zum vierten Mal auf\n" + originalSecondWizard);
			if (!resultWizard.equals(expectedResultWizard)) {
				System.out.println("sollte Harry auf " + expectedResultWizard + " ändern.");
				System.out.println("aber der Zustand änderte sich auf " + resultWizard);
			}
			if (!resultSecondWizard.equals(expectedResultSecondWizard)) {
				System.out.println("sollte Hermione auf " + expectedResultSecondWizard + " ändern.");
				System.out.println("aber der Zustand änderte sich auf " + resultSecondWizard);
			}
			System.out.println("Fehler \u2717");
			return;
		}

		wizHPField.set(theWizard, 81);
		originalWizard = getWizardString(theWizard, wizProtectedFromField);
		originalSecondWizard = getWizardString(theSecondWizard, wizProtectedFromField);
		expectedResultWizard = "{[Harry(****): 41/100 920/1000; 1234 Knuts; knows [[Test Spell(*): 20 mana; -7 HP]]; carries []] protectedFrom: []}";
		expectedResultSecondWizard = "{[Hermione(****): 972/1000 1000/1000; 12 Knuts; knows [[Test Spell(*): 20 mana; -7 HP]]; carries []] protectedFrom: []}";
		if (!theWizard.castSpell(apsSpell, theSecondWizard)) {
			System.out.println(originalSecondWizard);
			System.out.println("castSpell HazardousSpell "+ originalSpell + " zum vierten Mal auf\n" + originalSecondWizard + "sollte true retournieren");
			System.out.println("Aber false wurde retourniert");
			System.out.println("Fehler \u2717");
			return;
		};
		resultWizard = getWizardString(theWizard, wizProtectedFromField);
		resultSecondWizard = getWizardString(theSecondWizard, wizProtectedFromField);
		if (!resultWizard.equals(expectedResultWizard) || !resultSecondWizard.equals(expectedResultSecondWizard)) {
			System.out.println(originalWizard);
			System.out.println("castSpell HazardousSpell " + originalSpell +" zum vierten Mal auf\n" + originalSecondWizard);
			if (!resultWizard.equals(expectedResultWizard)) {
				System.out.println("sollte Harry auf " + expectedResultWizard + " ändern.");
				System.out.println("aber der Zustand änderte sich auf " + resultWizard);
			}
			if (!resultSecondWizard.equals(expectedResultSecondWizard)) {
				System.out.println("sollte Hermione auf " + expectedResultSecondWizard + " ändern.");
				System.out.println("aber der Zustand änderte sich auf " + resultSecondWizard);
			}
			System.out.println("Fehler \u2717");
			return;
		}

		originalWizard = getWizardString(theWizard, wizProtectedFromField);
		originalSecondWizard = getWizardString(theSecondWizard, wizProtectedFromField);
		expectedResultWizard = "{[Harry(****): 41/100 920/1000; 1234 Knuts; knows [[Test Spell(*): 20 mana; -7 HP]]; carries []] protectedFrom: []}";
		expectedResultSecondWizard = "{[Hermione(****): 972/1000 1000/1000; 12 Knuts; knows [[Test Spell(*): 20 mana; -7 HP]]; carries []] protectedFrom: []}";
		if (!theWizard.castSpell(apsSpell, theSecondWizard)) {
			System.out.println(originalWizard);
			System.out.println("castSpell HazardousSpell "+ originalSpell + " zum fünften Mal auf\n" + originalSecondWizard + "sollte true retournieren");
			System.out.println("Aber false wurde retourniert");
			System.out.println("Fehler \u2717");
			return;
		};
		resultWizard = getWizardString(theWizard, wizProtectedFromField);
		resultSecondWizard = getWizardString(theSecondWizard, wizProtectedFromField);
		if (!resultWizard.equals(expectedResultWizard) || !resultSecondWizard.equals(expectedResultSecondWizard)) {
			System.out.println(originalWizard);
			System.out.println("castSpell HazardousSpell " + originalSpell +" zum fünften Mal auf\n" + originalSecondWizard);
			if (!resultWizard.equals(expectedResultWizard)) {
				System.out.println("sollte Harry auf " + expectedResultWizard + " ändern.");
				System.out.println("aber der Zustand änderte sich auf " + resultWizard);
			}
			if (!resultSecondWizard.equals(expectedResultSecondWizard)) {
				System.out.println("sollte Hermione auf " + expectedResultSecondWizard + " ändern.");
				System.out.println("aber der Zustand änderte sich auf " + resultSecondWizard);
			}
			System.out.println("Fehler \u2717");
			return;
		}

		System.out.println("OK \u2713");
	} catch (Throwable t) {
		System.out.println("Unerwartete Exception "+t.getMessage());
		System.out.println("Fehler \u2717");
		return;
	}
	}

	private static String getWizardString(Wizard w, Field protectedFrom) {
		try {
			return "{" + w.toString() + " protectedFrom: " + protectedFrom.get(w).toString() + "}";
		} catch (IllegalArgumentException | IllegalAccessException e) {
			System.out.println("auf Instanzvariable protectedFrom des Wizard Objekts konnte nicht zugegriffen werden");
			System.out.println("Implementierung nicht spezifikationskonform.");
			System.out.println("Fehler \u2717");
		}
		return "";
	}
	
	private static int theIntVal = 0;
	private static int callCount = 0;
	private static int trueCount = 0;
	public static boolean doSelect(Function<Integer, Boolean> p) {
		++callCount;
		if (p.apply(theIntVal)) {
			++trueCount;
			return true;
		}
		return false;
	}

	public static void checkTask4() {
	try {
		System.out.println("\nÜberprüfung Aufgabe 4");
		Class<?> potionsClass = Potion.class;
		Field nameField = getFieldForClass(potionsClass, "name"); 
		if (nameField==null)
			return;
		nameField.setAccessible(true);
		Field priceField = getFieldForClass(potionsClass, "price"); 
		if (priceField==null)
			return;
		priceField.setAccessible(true);
		Field usagesField = getFieldForClass(potionsClass, "usages"); 
		if (usagesField==null)
			return;
		usagesField.setAccessible(true);
		Field weightField = getFieldForClass(potionsClass, "weight"); 
		if (weightField==null)
			return;
		weightField.setAccessible(true);
		List<Potion> potionsList = itemsList
				.stream()
				.filter(i->i instanceof Potion)
				.map(o -> (Potion)o)
				.toList();

		theIntVal = 1;
		String expectedResult = "[Health potion], [Mana potion], [Concoction], [Mana potion 1], [Health potion 1], [Bad Days], [Good Morning], [Omen], [Surprise], [sunrise], [Ahoi]";
		int expectedCallCount = 11;
		int expectedTrueCount = 11;
		List<Potion> resultList = Main.selectPotions(potionsList).stream().toList();
		if (callCount != expectedCallCount || trueCount != expectedTrueCount) {
			System.out.println("Anzahl der Aufrufe von Checks_Do_Not_Change.doSelect: " + callCount + " (sollte " + expectedCallCount + " sein)"
					+ " Anzahl der true Ergebnisse: " + trueCount + " (sollte " + expectedTrueCount + " sein)");
			System.out.println("Fehler \u2717");
			return;
		}
		String resultString = resultTask4ToString(resultList, nameField, priceField, weightField);
		if (!checkTask4Result(resultString, expectedResult, theIntVal))
			return;

		theIntVal = 2;
		expectedResult = "[Health potion], [Mana potion], [Concoction], [Mana potion 1], [Health potion 1], [Bad Days], [Good Morning], [Surprise], [sunrise]";
		callCount = 0;
		trueCount = 0;
		expectedCallCount = 11;
		expectedTrueCount = 9;
		resultList = Main.selectPotions(potionsList).stream().toList();
		if (callCount != expectedCallCount || trueCount != expectedTrueCount) {
			System.out.println("Anzahl der Aufrufe von Checks_Do_Not_Change.doSelect: " + callCount + " (sollte " + expectedCallCount + " sein)"
					+ " Anzahl der true Ergebnisse: " + trueCount + " (sollte " + expectedTrueCount + " sein)");
			System.out.println("Fehler \u2717");
			return;
		}
		resultString = resultTask4ToString(resultList, nameField, priceField, weightField);
		if (!checkTask4Result(resultString, expectedResult, theIntVal))
			return;

		theIntVal = 3;
		expectedResult = "[Concoction], [Good Morning]";
		callCount = 0;
		trueCount = 0;
		expectedCallCount = 11;
		expectedTrueCount = 2;
		resultList = Main.selectPotions(potionsList).stream().toList();
		if (callCount != expectedCallCount || trueCount != expectedTrueCount) {
			System.out.println("Anzahl der Aufrufe von Checks_Do_Not_Change.doSelect: " + callCount + " (sollte " + expectedCallCount + " sein)"
					+ " Anzahl der true Ergebnisse: " + trueCount + " (sollte " + expectedTrueCount + " sein)");
			System.out.println("Fehler \u2717");
			return;
		}
		resultString = resultTask4ToString(resultList, nameField, priceField, weightField);
		if (!checkTask4Result(resultString, expectedResult, theIntVal))
			return;

		theIntVal = 4;
		expectedResult = "";
		callCount = 0;
		trueCount = 0;
		expectedCallCount = 11;
		expectedTrueCount = 0;
		resultList = Main.selectPotions(potionsList).stream().toList();
		if (callCount != expectedCallCount || trueCount != expectedTrueCount) {
			System.out.println("Anzahl der Aufrufe von Checks_Do_Not_Change.doSelect: " + callCount + " (sollte " + expectedCallCount + " sein)"
					+ " Anzahl der true Ergebnisse: " + trueCount + " (sollte " + expectedTrueCount + " sein)");
			System.out.println("Fehler \u2717");
			return;
		}
		resultString = resultTask4ToString(resultList, nameField, priceField, weightField);
		if (!checkTask4Result(resultString, expectedResult, theIntVal))
			return;
		
		potionsList = new ArrayList<>(potionsList);
		potionsList.add(new HealthPotion("Aaaah", 1, 1, 1, 1));
		theIntVal = 4;
		expectedResult = "[Aaaah]";
		callCount = 0;
		trueCount = 0;
		expectedCallCount = 12;
		expectedTrueCount = 1;
		resultList = Main.selectPotions(potionsList).stream().toList();
		if (callCount != expectedCallCount || trueCount != expectedTrueCount) {
			System.out.println("Anzahl der Aufrufe von Checks_Do_Not_Change.doSelect: " + callCount + " (sollte " + expectedCallCount + " sein)"
					+ " Anzahl der true Ergebnisse: " + trueCount + " (sollte " + expectedTrueCount + " sein)");
			System.out.println("Fehler \u2717");
			return;
		}
		resultString = resultTask4ToString(resultList, nameField, priceField, weightField);
		if (!checkTask4Result(resultString, expectedResult, theIntVal))
			return;

		potionsList.add(new HealthPotion("Iiiiih", 1, 1, 1, 1));
		theIntVal = 4;
		expectedResult = "[Aaaah], [Iiiiih]";
		callCount = 0;
		trueCount = 0;
		expectedCallCount = 13;
		expectedTrueCount = 2;
		resultList = Main.selectPotions(potionsList).stream().toList();
		if (callCount != expectedCallCount || trueCount != expectedTrueCount) {
			System.out.println("Anzahl der Aufrufe von Checks_Do_Not_Change.doSelect: " + callCount + " (sollte " + expectedCallCount + " sein)"
					+ " Anzahl der true Ergebnisse: " + trueCount + " (sollte " + expectedTrueCount + " sein)");
			System.out.println("Fehler \u2717");
			return;
		}
		resultString = resultTask4ToString(resultList, nameField, priceField, weightField);
		if (!checkTask4Result(resultString, expectedResult, theIntVal))
			return;

		System.out.println("OK \u2713");
	} catch (Throwable t) {
		System.out.println("Unerwartete Exception "+t.getMessage());
		System.out.println("Fehler \u2717");
	}
	}
	
	private static String resultTask4ToString(List<Potion> l, Field nameField, Field priceField,
			Field weightField) {
		return l.stream()
				.map(o->objFieldsToString(o, nameField))
				.collect(Collectors.joining(", "));
	}

	private static boolean checkTask4Result(String result, String expectedResult, int intVal) {
		if (!expectedResult.equals(result)) {
			System.out.println("Gesucht wurden Potions mit minimaler Zeichenhäufigkeit = "+ intVal
					+ ".\n"
					+ "Die erwarteten Objekte sind (in dieser Reihenfolge,"
					+ " nur der relevante Wert name wird angezeigt):\n"
					+ expectedResult
					+ "\nErhalten wurde aber:\n"
					+ result);
			System.out.println("Fehler \u2717");
			return false;
		}
		else
			return true;
	}

	static Field getFieldForClass(Class<?> c, String fieldName) {
		Field f = null;
		Class<?> curClass = c;
		for (curClass = c; f == null && curClass!=Object.class; 
				curClass = curClass.getSuperclass()) {
			try {
				f = curClass.getDeclaredField(fieldName);
			} catch (NoSuchFieldException | SecurityException e) {
			}
		}
		if (f==null) {
			System.out.println("Überprüfung nicht möglich.");
			System.out.println("Instanzvariable '"+fieldName+"' in Klasse '"+c.getName()+"' fehlt");
			System.out.println("Implementierung nicht spezifikationskonform. ");
			System.out.println("Fehler \u2717");
		}
		return f;
	}
	
	private static String objFieldsToString(Object obj, Field... fields) {
		StringBuilder b = new StringBuilder("[");
		for (int i=0; i<fields.length; ++i) {
			try {
				b.append(fields[i].get(obj));
			} catch (IllegalArgumentException | IllegalAccessException e) {
			}
			if (i!=fields.length-1) b.append("; ");
		}
		b.append("]");
		return b.toString();
	}
	
	/*
	private static String objFieldsToStringAddition(Object obj, Function<String,String> transform, Field... fields) {
		StringBuilder b = new StringBuilder("[");
		for (int i=0; i<fields.length; ++i) {
			try {
				b.append(fields[i].get(obj));
				if (!fields[i].get(obj).toString().isEmpty()) {
					b.append(" (");
					b.append(transform.apply(fields[i].get(obj).toString()));
					b.append(")");
				}
			} catch (IllegalArgumentException | IllegalAccessException e) {
			}
			if (i!=fields.length-1) b.append("; ");
		}
		b.append("]");
		return b.toString();
	}
	*/
	
	/*
	private static String getMyFieldValue(Field f, Object obj) {
		String s = null;
		try {
			s = f.get(obj).toString();
		} catch (IllegalArgumentException | IllegalAccessException e) {
		}
		return s;
	}
	*/
}