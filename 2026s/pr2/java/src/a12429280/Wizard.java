package a12429280;

import java.util.Set;

/**
 * Wizard class objects are the primary actors in the game. They can use and trade items, provide
 * magic energy, cast spells and also are affected be various magical effects.
 */
public class Wizard implements MagicSource, Trader, MagicEffectRealization {
	private String      name;
	private MagicLevel  level;
	private VitalStats  vitals;
	private Inventory   inventory;
	private SpellBook   spellBook;

	/**
	 * @param name name
	 * @param level the magic level (proficiency needed to cast spells)
	 * @param vitals the health and mana manager
	 * @param inventory the items, money, and capacity manager
	 * @param spellBook the known spells and protections manager
	 */
	/*
	 * REFACTORING TASK 2.1:
	 * I chose the "Extract Class" method to refactor the Wizard constructor.
	 * The Wizard was violating the Single Responsibility Principle by trying 
	 * to manage trading, energy, and spell logic all at once. By extracting 
	 * these into Inventory, VitalStats, and SpellBook classes, the constructor 
	 * drops from 11 parameters to 5, and the Wizard cleanly delegates tasks.
	 */
	public Wizard(String name, MagicLevel level, VitalStats vitals, Inventory inventory, SpellBook spellBook) {
		AssertValue.isNotNull(name); AssertValue.isNotEmpty(name); AssertValue.isNotNull(level);
		AssertValue.isNotNull(vitals); AssertValue.isNotNull(inventory); AssertValue.isNotNull(spellBook);
		if (vitals.getDefaultManaPoints() < level.toMana()) throw new IllegalArgumentException("basic mana to low");

		this.name      = name;
		this.level     = level;
		this.vitals    = vitals;
		this.inventory = inventory;
		this.spellBook = spellBook;
	}

	/**
	 * Compatibility Constructor for Checks_Do_Not_Change.java.
	 * @param name name
	 * @param level the magic level (proficiency needed to cast spells)
	 * @param defaultHealthPoints base for percentage health calculations
	 * @param healthPoints current health 
	 * @param defaultManaPoints base for percentage mana calculations
	 * @param manaPoints current mana
	 * @param money current money
	 * @param knownSpells set of known spells
	 * @param protectedFrom set of spells the object is protected against
	 * @param carryingCapacity maximum carrying capacity
	 * @param items set of items the object is currently carrying
	 */
	public Wizard(String name, MagicLevel level, int defaultHealthPoints, int healthPoints, int defaultManaPoints, int manaPoints, int money, 
			      Set<Spell> knownSpells, Set<AttackingSpell> protectedFrom, int carryingCapacity, Set<Tradeable> items) {
		this(name, level, 
			 new VitalStats(defaultHealthPoints, healthPoints, defaultManaPoints, manaPoints), 
			 new Inventory(money, carryingCapacity, items), 
			 new SpellBook(knownSpells, protectedFrom));
	}

	/**
	 * Return true, if HP is 0, false otherwise
	 * @return true, if HP is 0, false otherwise
	 */
	public boolean isDead() {
		return vitals.isDead();
	}  

	/**
	 * If spell is null, IllegalArgumentException has to be thrown;
	 * if wizard is dead (isDead) no action can be taken and false is returned;
	 * add spell to the set of knownSpells;
	 * returns true, if insertion was successful, false otherwise.
	 * @param s spell to be learned
	 * @return true, if insertion was successful, false otherwise.
	 */
	public boolean learn(Spell s) {
		AssertValue.isNotNull(s); if (isDead()) return false;
		return spellBook.addSpell(s);
	}

	/**
	 * If spell is null, IllegalArgumentException has to be thrown;
	 * if wizard is dead (isDead) no action can be taken and false is returned;
	 * remove spell from the set of knownSpells;
	 * returns true if removal was successful, false otherwise.
	 * @param s spell that the object is about to learn
	 * @return true, if removal was successful, false otherwise.
	 */
	public boolean forget(Spell s) {
		AssertValue.isNotNull(s); if (isDead()) return false;
		return spellBook.removeSpell(s);
	}

	/**
	 * If s or target is null, IllegalArgumentException has to be thrown;
	 * if wizard is dead (isDead) no action can be taken and false is returned;
	 * if wizard does not know the spell, false is returned;
	 * call cast on s with this as source and parameter target as target
	 * return true, if cast was called;
	 * @param s spell to be cast
	 * @param target target of the spell to cast
	 * @return true, if cast was called, false otherwise;
	 */
	public boolean castSpell(Spell s, MagicEffectRealization target) {
		AssertValue.isNotNull(s); AssertValue.isNotNull(target);  if (isDead() || !spellBook.containsSpell(s)) return false;
		s.cast(this, target); return true;
	}

	/**
	 * If this object's knownSpells is empty, return false
	 * otherwise choose a random spell from knownSpells and delegate to
	 * castSpell(Spell, MagicEffectRealization)
	 * @param target target of the spell to cast
	 * @return false, if the object does not know a spell, otherwise the
	 * result of the delegation to castSpell
	 */
	public boolean castRandomSpell(MagicEffectRealization target) {
		Spell randomSpell = spellBook.getRandomSpell(); if (randomSpell == null) return false;
		return castSpell(randomSpell, target);
	}

	/**
	 * If item or target is null, IllegalArgumentException has to be thrown;
	 * if wizard is dead (isDead) no action can be taken and false is returned;
	 * if wizard does not possess the item, false is returned;
	 * call useOn on the item with parameter target as target;
	 * return true, if useOn was called.
	 * @param item item to be used
	 * @param target target on which item is to be used on
	 * @return true, if useOn was called, false otherwise
	 */
	public boolean useItem(Tradeable item, MagicEffectRealization target) {
		AssertValue.isNotNull(item); AssertValue.isNotNull(target); if (isDead() || !inventory.containsItem(item)) return false;
		item.useOn(target); return true;
	}

	/**
	 * If this object's inventory is empty, return false;
	 * otherwise choose a random item from inventory and delegate to
	 * useItem(Tradeable, MagicEffectRealization).
	 * @param target target on which item is to be used on
	 * @return false, if the object does not possess any item, otherwise the
	 * result of the delegation to useItem
	 */
	public boolean useRandomItem(MagicEffectRealization target) {
		Tradeable randomItem = inventory.getRandomItem(); if (randomItem == null) return false;
		return useItem(randomItem, target);
	}

	/**
	 * If item or target is null, IllegalArgumentException has to be thrown;
	 * if wizard is dead (isDead), no action can be taken and false is returned;
	 * call purchase on the item with this as seller and target as buyer;
	 * return true, if purchase was called successfully (returned true), false
	 * otherwise.
	 * @param item item to be sold
	 * @param target object the item is sold to (buyer)
	 * @return true, if purchase was called successfully (returned true), false
	 * otherwise.
	 */ 
	public boolean sellItem(Tradeable item, Trader target) {
		AssertValue.isNotNull(item); AssertValue.isNotNull(target); if (isDead()) return false;
		return item.purchase(this, target);
	}

	/**
	 * If this object's inventory is empty, return false,
	 * otherwise choose a random item from inventory and delegate to
	 * sellItem(Tradeable, MagicEffectRealization).
	 * @param target object the item is sold to (buyer)
	 * @return false, if the object does not possess any item, otherwise the
	 * result of the delegation to sellItem
	 */
	public boolean sellRandomItem(Trader target) {
		Tradeable randomItem = inventory.getRandomItem(); if (randomItem == null) return false;
		return sellItem(randomItem, target);
	}

	/**
	 * Returns a string in the format
	 * "['name'('level'): 'HP'/'basicHP' 'MP'/'basicMP'; 'money' 'KnutOrKnuts'; knows 'knownSpells'; carries 'inventory']";
	 * where 'level' is the asterisks representation of the level
	 * (see MagicLevel.toString) and 'knownSpells' and 'inventory' use
	 * the default toString method of Java Set; 'KnutOrKnuts' is Knut
	 * if 'money' is 1, Knuts otherwise.
	 * E.g. [Ignatius(**): 70/100 100/150; 72 Knuts; knows [[Episkey(*): 5 mana; +20 HP], [Confringo(*): 10 mana; -20 HP]]; carries []]
	 * @return "['name'('level'): 'HP'/'basicHP' 'MP'/'basicMP'; 'money' 'KnutOrKnuts'; knows 'knownSpells'; carries 'inventory']"
	 */ 
	@Override public String toString() {
		return String.format("[%s(%s): %d/%d %d/%d; %d Knut%s; knows %s; carries %s]", 
				name, level, vitals.getHealthPoints(), vitals.getDefaultHealthPoints(), 
				vitals.getManaPoints(), vitals.getDefaultManaPoints(), inventory.getMoney(), 
				((inventory.getMoney() == 1) ? "" : "s"), spellBook.getKnownSpells(), 
				inventory.getItems());
	}

	// MagicSource Interface
	/**
	 * If wizard is dead (isDead) no action can be taken and false is returned:
	 * check if level is at least levelNeeded, return false otherwise;
	 * if MP is less than manaAmount return false;
	 * subtract manaAmount from MP and return true.
	 * @param levelNeeded minimum magic level needed for the action 
	 * @param manaAmount amount of mana needed for the action 
	 * @return true, if mana can be successfully provided, false otherwise
	 */
	@Override public boolean provideMana(MagicLevel levelNeeded, int manaAmount) {
		AssertValue.isNotNull(levelNeeded); AssertValue.isPositive(manaAmount); if (isDead() || (level.compareTo(levelNeeded) < 0)) return false;
		return vitals.provideMana(manaAmount);
	}

	//Trader Interface
	/**
	 * Return true, if the item is in the inventory, false otherwise
	 * @param item object is tested, if it possesses this item
	 * @return true, if the item is in the inventory, false otherwise
	 */
	@Override public boolean possesses(Tradeable item) {
		AssertValue.isNotNull(item);
		return inventory.containsItem(item);
	}

	/**
	 * Return true, if money is greater than or equal to amount, false otherwise
	 * @param amount object is tested, if it owns enough money to pay this amount
	 * @return true, if money is greater than or equal to amount, false otherwise
	 */
	@Override public boolean canAfford(int amount) {
		AssertValue.isPositive(amount);
		return inventory.hasEnoughMoney(amount);
	}

	/**
	 * Return true, if inventoryTotalWeight+weight is less than or equal to carryingCapacity, false otherwise
	 * @param weight test, if this weight can be added to object's inventory, without exceeding the
	 * carryingCapacity
	 * @return true, if inventoryTotalWeight+weight is less than or equal to carryingCapacity, false otherwise
	 */
	@Override public boolean hasCapacity(int weight) {
		AssertValue.isPositive(weight);
		return inventory.hasAvailableCapacity(weight);
	}

	/**
	 * If wizard is dead (isDead) no action can be taken and false is returned;
	 * if this owns enough money deduct amount from money and return true,
	 * return false otherwise
	 * @param amount to be payed
	 * @return true, if payment succeeds, false otherwise
	 */
	@Override public boolean pay(int amount) {
		if (isDead() || !inventory.hasEnoughMoney(amount)) return false;
		inventory.deductMoney(amount); return true;
	}   

	/**
	 * If wizard is dead (isDead), no action can be taken and false is returned;
	 * add amount to this object's money and return true.
	 * @param amount amount to be received
	 * @return true, if reception succeeds, false otherwise 
	 */
	@Override public boolean earn(int amount) {
		AssertValue.isPositive(amount); if (isDead()) return false;
		inventory.addMoney(amount); return true;
	}   

	/**
	 * Edd item to inventory if carryingCapacity is sufficient.
	 * returns true, if item is successfully added, false otherwise
	 * (carrying capacity exceeded or item is already in the inventory)
	 * @param item item to be added to object's inventory
	 * @return true. if item is successfully added, false otherwise
	 */
	@Override public boolean addToInventory(Tradeable item) {
		AssertValue.isNotNull(item);
		return inventory.addItem(item);
	}

	/**
	 * Remove item from inventory.
	 * returns true, if item is successfully removed, false otherwise
	 * (item not in the inventory).
	 * @param item item to be removed from object's inventory
	 * @return true, if item is successfully removed, false otherwise
	 */
	@Override public boolean removeFromInventory(Tradeable item) {
		AssertValue.isNotNull(item);
		return inventory.removeItem(item);
	}

	/**
	 * Returns true, if this object's HP are not 0 (alive wizard).
	 * @return true, if the object is alive
	 */
	@Override public boolean canSteal() {
		return !isDead();
	}

	/**
	 * If thief is null, IllegalArgumentException has to be thrown;
	 * if thief cannot steal (canSteal returns false) no action can be taken
	 * and false is returned;
	 * returns false if, the object's inventory is empty;
	 * otherwise transfers a random item from the this object's inventory into
	 * the thief's inventory;
	 * if the thief's inventory has not enough capacity, the object just vanishes
	 * and false is returned;
	 * returns true, if theft was successful.
	 * @param thief object that is stealing the item from the this-object.
	 * @return true, if theft was successful
	 */
	@Override public boolean steal(Trader thief) {
		AssertValue.isNotNull(thief); if (!thief.canSteal() || inventory.isEmpty()) return false;
		
		var item = inventory.getRandomItem(); inventory.removeItem(item);
		return thief.addToInventory(item);
	}

	/**
	 * Returns true if, this object's HP are 0 (dead wizard)
	 * @return true if the object is dead
	 */
	@Override public boolean isLootable() {
		return isDead();
	}

	/**
	 * Returns true if this object's HP are not 0 (alive wizard)
	 * @return true, if the object is alive
	 */
	@Override public boolean canLoot() {
		return !isDead();
	}

	/**
	 * Of looter is null, IllegalArgumentException has to be thrown;
	 * if looter cannot loot (canLoot returns false), no action can be taken
	 * and false is returned;
	 * if the this object can be looted (isLootable), transfer all the items
	 * in the object's inventory into the looter's inventory;
	 * items that don't fit in the looter's inventory because auf the weight
	 * limitation just vanish.
	 * returns true, if at least one item was successfully transferred, false
	 * otherwise.
	 * @param looter object that is looting this-object.
	 * @return true, if looting was successful, false otherwise
	 */
	@Override public boolean loot(Trader looter) {
		AssertValue.isNotNull(looter); if (!looter.canLoot() || !isLootable()) return false;
		var stole = inventory.getItems().stream().filter(looter::addToInventory).count() > 0;
		inventory.clear(); return stole;
	} 

	// MagicEffectRealization Interface
	/**
	 * Reduce the object's HP by amount ensuring however that HP does not
	 * become negative.
	 * @param amount amount to be deducted from health 
	 */
	@Override public void takeDamage(int amount) {
		MagicEffectRealization.super.takeDamage(amount);
		vitals.takeDamage(amount);
	}  

	/**
	 * Reduce the object's HP by the percentage given of the object's basic
	 * HP value ensuring however, that HP does not become negative.
	 * Do calculations in double truncating to int only for the assignment
	 * @param percentage percentage of damage done
	 */
	@Override public void takeDamagePercent(int percentage) {
		MagicEffectRealization.super.takeDamagePercent(percentage);
		vitals.takeDamagePercent(percentage);
	}

	/**
	 * Reduce the object's MP by amount ensuring however that MP does not
	 * become negative.
	 * @param amount amount to be deducted from mana 
	 */
	@Override public void weakenMagic(int amount) {
		MagicEffectRealization.super.weakenMagic(amount);
		vitals.weakenMagic(amount);
	}

	/**
	 * Reduce the object's MP by the percentage given of the object's basic
	 * MP value ensuring however, that MP does not become negative.
	 * Do calculations in double truncating to int only for the assignment
	 * @param percentage percentage of damage done
	 */
	@Override public void weakenMagicPercent(int percentage) {
		MagicEffectRealization.super.weakenMagicPercent(percentage);
		vitals.weakenMagicPercent(percentage);
	}

	/**
	 * Increase the object's HP by the amount given.
	 * @param amount amount to increase health
	 */
	@Override public void heal(int amount) {
		MagicEffectRealization.super.heal(amount);
		vitals.heal(amount);
	}

	/**
	 * Increase the object's HP by the percentage given of the object's
	 * basic HP. Do calculations in double truncating to int only for
	 * the assignment
	 * @param percentage percentage of healing done
	 */
	@Override public void healPercent(int percentage) {
		MagicEffectRealization.super.healPercent(percentage);
		vitals.healPercent(percentage);
	}

	/**
	 * Increase the object's MP by the amount given.
	 * @param amount amount to increase mana
	 */
	@Override public void enforceMagic(int amount) {
		MagicEffectRealization.super.enforceMagic(amount);
		vitals.enforceMagic(amount);
	}

	/**
	 * Increase the object's MP by the percentage given of the object's
	 * basic MP. Do calculations in double truncating to int only for
	 * the assignment
	 * @param percentage percentage of mana increase
	 */
	@Override public void enforceMagicPercent(int percentage) {
		MagicEffectRealization.super.enforceMagicPercent(percentage);
		vitals.enforceMagicPercent(percentage);
	}

	/**
	 * Return true, if s is contained in instance variable protectedFrom
	 * @param s spell that is tested for
	 * @return true, if object is protected against spell s, false otherwise
	 */
	@Override public boolean isProtected(Spell s) {
		MagicEffectRealization.super.isProtected(s);
		return spellBook.containsProtectionAgainst(s);
	}  

	/**
	 * Add all spells from attacks to instance variable protectedFrom
	 * @param attacks spells against which protection is provided
	 */
	@Override public void setProtection(Set<AttackingSpell> attacks) {
		MagicEffectRealization.super.setProtection(attacks);
		spellBook.addProtectionAgainst(attacks);
	}

	/**
	 * Remove all spells from attacks from instance variable protectedFrom
	 * @param attacks spells against which protection is removed 
	 */
	@Override public void removeProtection(Set<AttackingSpell> attacks) {
		MagicEffectRealization.super.removeProtection(attacks);
		spellBook.removeProtectionAgainst(attacks);
	}
}