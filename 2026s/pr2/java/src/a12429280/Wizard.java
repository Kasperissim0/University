package a12429280;

import java.util.HashSet;
import java.util.Set;
import java.util.ArrayList;
import java.util.List;

/**
 * Wizard class objects are the primary actors in the game.
 * They can use and trade items, provide magic energy,
 * cast spells and are affected by magical effects.
 */
public class Wizard implements MagicSource, Trader, MagicEffectRealization {

    private String name;
    private MagicLevel level;

    /*
    // REFACTORING TASK 2.1 (commented out for basic implementation)
    private VitalStats vitals;
    private Inventory inventory;
    private SpellBook spellBook;
    */

    // Original specification fields
    private int basicHP;
    private int HP; public int getHealth() {return HP;}
    private int basicMP;
    private int MP;
    private int money;
    private Set<Spell> knownSpells;
    private Set<AttackingSpell> protectedFrom;
    private int carryingCapacity;
    private Set<Tradeable> inventory;

    /*
    // Refactored constructor (bonus task) commented out
    public Wizard(String name, MagicLevel level,
                  VitalStats vitals,
                  Inventory inventory,
                  SpellBook spellBook) {

        AssertValue.isNotNull(name);
        AssertValue.isNotEmpty(name);
        AssertValue.isNotNull(level);
        AssertValue.isNotNull(vitals);
        AssertValue.isNotNull(inventory);
        AssertValue.isNotNull(spellBook);

        if(vitals.getDefaultManaPoints() < level.toMana())
            throw new IllegalArgumentException("basic mana too low");

        this.name = name;
        this.level = level;
        this.vitals = vitals;
        this.inventory = inventory;
        this.spellBook = spellBook;
    }
    */

    /**
     * Constructor required by the specification.
     */
    public Wizard(
            String name,
            MagicLevel level,
            int basicHP,
            int HP,
            int basicMP,
            int MP,
            int money,
            Set<Spell> knownSpells,
            Set<AttackingSpell> protectedFrom,
            int carryingCapacity,
            Set<Tradeable> inventory) {

        AssertValue.isNotNull(name);
        AssertValue.isNotEmpty(name);
        AssertValue.isNotNull(level);

        AssertValue.isPositive(basicHP);
        AssertValue.isPositive(HP);
        AssertValue.isPositive(basicMP);
        AssertValue.isPositive(MP);
        AssertValue.isPositive(money);
        AssertValue.isPositive(carryingCapacity);

        AssertValue.isNotNull(knownSpells);
        AssertValue.isNotNull(protectedFrom);
        AssertValue.isNotNull(inventory);

        if (basicMP < level.toMana()) {
            throw new IllegalArgumentException(
                "basic mana too low"
            );
        }

        if (HP > basicHP || MP > basicMP) {
            throw new IllegalArgumentException(
                "current values cannot exceed defaults"
            );
        }

        int weight = 0;
        for (Tradeable item : inventory) {
            weight += item.getWeight();
        }

        if (weight > carryingCapacity) {
            throw new IllegalArgumentException(
                "inventory too heavy"
            );
        }

        this.name = name;
        this.level = level;
        this.basicHP = basicHP;
        this.HP = HP;
        this.basicMP = basicMP;
        this.MP = MP;
        this.money = money;

        // specification requires HashSet as concrete type
        this.knownSpells = new HashSet<>(knownSpells);
        this.protectedFrom = new HashSet<>(protectedFrom);
        this.inventory = new HashSet<>(inventory);

        this.carryingCapacity = carryingCapacity;
    }


    /**
     * Return true if HP is 0.
     */
    public boolean isDead() {
        return HP == 0;
    }


    /**
     * Calculates total inventory weight.
     */
    private int inventoryTotalWeight() {

        int total = 0;

        for (Tradeable item : inventory) {
            total += item.getWeight();
        }

        return total;
    }


    /**
     * Learn a spell.
     */
    public boolean learn(Spell s) {

        AssertValue.isNotNull(s);

        if (isDead()) {
            return false;
        }

        return knownSpells.add(s);
    }


    /**
     * Forget a spell.
     */
    public boolean forget(Spell s) {

        AssertValue.isNotNull(s);

        if (isDead()) {
            return false;
        }

        return knownSpells.remove(s);
    }
    /**
     * Cast a known spell on a target.
     */
    public boolean castSpell(Spell s, MagicEffectRealization target) {

        AssertValue.isNotNull(s);
        AssertValue.isNotNull(target);

        if (isDead()) {
            return false;
        }

        if (!knownSpells.contains(s)) {
            return false;
        }

        s.cast(this, target);

        return true;
    }


    /**
     * Cast a random spell.
     */
    public boolean castRandomSpell(MagicEffectRealization target) {

        AssertValue.isNotNull(target);

        if (knownSpells.isEmpty()) {
            return false;
        }

        int index = (int)(Math.random() * knownSpells.size());

        int counter = 0;

        for (Spell spell : knownSpells) {

            if (counter == index) {
                return castSpell(spell, target);
            }

            counter++;
        }

        return false;
    }


    /**
     * Use an item on a target.
     */
    public boolean useItem(Tradeable item, MagicEffectRealization target) {

        AssertValue.isNotNull(item);
        AssertValue.isNotNull(target);

        if (isDead()) {
            return false;
        }

        if (!inventory.contains(item)) {
            return false;
        }

        item.useOn(target);

        return true;
    }


    /**
     * Use a random item.
     */
    public boolean useRandomItem(MagicEffectRealization target) {

        AssertValue.isNotNull(target);

        if (inventory.isEmpty()) {
            return false;
        }

        int index = (int)(Math.random() * inventory.size());

        int counter = 0;

        for (Tradeable item : inventory) {

            if (counter == index) {
                return useItem(item, target);
            }

            counter++;
        }

        return false;
    }


    /**
     * Sell an item to another trader.
     */
    public boolean sellItem(Tradeable item, Trader target) {

        AssertValue.isNotNull(item);
        AssertValue.isNotNull(target);

        if (isDead()) {
            return false;
        }

        return item.purchase(this, target);
    }


    /**
     * Sell a random item.
     */
    public boolean sellRandomItem(Trader target) {

        AssertValue.isNotNull(target);

        if (inventory.isEmpty()) {
            return false;
        }

        int index = (int)(Math.random() * inventory.size());

        int counter = 0;

        for (Tradeable item : inventory) {

            if (counter == index) {
                return sellItem(item, target);
            }

            counter++;
        }

        return false;
    }


    /**
     * String representation of the wizard.
     */
    @Override
    public String toString() {

        String currency = (money == 1) ? "Knut" : "Knuts";

        return String.format(
            "[%s(%s): %d/%d %d/%d; %d %s; knows %s; carries %s]",
            name,
            level,
            HP,
            basicHP,
            MP,
            basicMP,
            money,
            currency,
            knownSpells,
            inventory
        );
    }


    // ---------------------------
    // MagicSource Interface
    // ---------------------------

    /**
     * Provide mana for a magical action.
     */
    @Override
    public boolean provideMana(MagicLevel levelNeeded, int manaAmount) {

        AssertValue.isNotNull(levelNeeded);
        AssertValue.isPositive(manaAmount);

        if (isDead()) {
            return false;
        }

        if (level.compareTo(levelNeeded) < 0) {
            return false;
        }

        if (MP < manaAmount) {
            return false;
        }

        MP -= manaAmount;

        return true;
    }
    // ---------------------------
    // Trader Interface
    // ---------------------------

    /**
     * Return true if the item is in the inventory.
     */
    @Override
    public boolean possesses(Tradeable item) {

        AssertValue.isNotNull(item);

        return inventory.contains(item);
    }


    /**
     * Return true if enough money is available.
     */
    @Override
    public boolean canAfford(int amount) {

        AssertValue.isPositive(amount);

        return money >= amount;
    }


    /**
     * Return true if enough carrying capacity exists.
     */
    @Override
    public boolean hasCapacity(int weight) {

        AssertValue.isPositive(weight);

        return inventoryTotalWeight() + weight <= carryingCapacity;
    }


    /**
     * Pay an amount of money.
     */
    @Override
    public boolean pay(int amount) {

        AssertValue.isPositive(amount);

        if (isDead()) {
            return false;
        }

        if (money < amount) {
            return false;
        }

        money -= amount;

        return true;
    }


    /**
     * Receive money.
     */
    @Override
    public boolean earn(int amount) {

        AssertValue.isPositive(amount);

        if (isDead()) {
            return false;
        }

        money += amount;

        return true;
    }


    /**
     * Add an item to the inventory.
     */
    @Override
    public boolean addToInventory(Tradeable item) {

        AssertValue.isNotNull(item);

        if (!hasCapacity(item.getWeight())) {
            return false;
        }

        return inventory.add(item);
    }


    /**
     * Remove an item from the inventory.
     */
    @Override
    public boolean removeFromInventory(Tradeable item) {

        AssertValue.isNotNull(item);

        return inventory.remove(item);
    }


    /**
     * Only living wizards can steal.
     */
    @Override
    public boolean canSteal() {

        return !isDead();
    }


    /**
     * Steal a random item from another object.
     */
    @Override
    public boolean steal(Trader thief) {

        AssertValue.isNotNull(thief);

        if (!thief.canSteal()) {
            return false;
        }

        if (inventory.isEmpty()) {
            return false;
        }

        int index = (int)(Math.random() * inventory.size());

        Tradeable stolenItem = null;

        int counter = 0;

        for (Tradeable item : inventory) {

            if (counter == index) {
                stolenItem = item;
                break;
            }

            counter++;
        }

        inventory.remove(stolenItem);

        return thief.addToInventory(stolenItem);
    }


    /**
     * Dead wizards can be looted.
     */
    @Override
    public boolean isLootable() {

        return isDead();
    }


    /**
     * Only living wizards can loot.
     */
    @Override
    public boolean canLoot() {

        return !isDead();
    }


    /**
     * Transfer all items into the looter inventory.
     */
    @Override
    public boolean loot(Trader looter) {

        AssertValue.isNotNull(looter);

        if (!looter.canLoot()) {
            return false;
        }

        if (!isLootable()) {
            return false;
        }

        boolean success = false;

        Set<Tradeable> itemsCopy = new HashSet<>(inventory);

        for (Tradeable item : itemsCopy) {

            if (looter.addToInventory(item)) {
                success = true;
            }

            inventory.remove(item);
        }

        return success;
    }
    
    // ---------------------------
    // MagicEffectRealization Interface
    // ---------------------------

    /**
     * Reduce HP by amount but never below 0.
     */
    @Override
    public void takeDamage(int amount) {

        MagicEffectRealization.super.takeDamage(amount);

        HP -= amount;

        if (HP < 0) {
            HP = 0;
        }
    }


    /**
     * Reduce HP by a percentage of basic HP.
     */
    @Override
    public void takeDamagePercent(int percentage) {

        MagicEffectRealization.super.takeDamagePercent(percentage);

        int damage = (int)(basicHP * (percentage / 100.0));

        takeDamage(damage);
    }


    /**
     * Reduce MP by amount but never below 0.
     */
    @Override
    public void weakenMagic(int amount) {

        MagicEffectRealization.super.weakenMagic(amount);

        MP -= amount;

        if (MP < 0) {
            MP = 0;
        }
    }


    /**
     * Reduce MP by a percentage of basic MP.
     */
    @Override
    public void weakenMagicPercent(int percentage) {

        MagicEffectRealization.super.weakenMagicPercent(percentage);

        int reduction = (int)(basicMP * (percentage / 100.0));

        weakenMagic(reduction);
    }


    /**
     * Increase HP by amount.
     */
    @Override
    public void heal(int amount) {

        MagicEffectRealization.super.heal(amount);

        HP += amount;
    }


    /**
     * Increase HP by a percentage of basic HP.
     */
    @Override
    public void healPercent(int percentage) {

        MagicEffectRealization.super.healPercent(percentage);

        int healing = (int)(basicHP * (percentage / 100.0));

        heal(healing);
    }


    /**
     * Increase MP by amount.
     */
    @Override
    public void enforceMagic(int amount) {

        MagicEffectRealization.super.enforceMagic(amount);

        MP += amount;
    }


    /**
     * Increase MP by a percentage of basic MP.
     */
    @Override
    public void enforceMagicPercent(int percentage) {

        MagicEffectRealization.super.enforceMagicPercent(percentage);

        int mana = (int)(basicMP * (percentage / 100.0));

        enforceMagic(mana);
    }


    /**
     * Check if this wizard is protected against a spell.
     */
    @Override
    public boolean isProtected(Spell s) {

        MagicEffectRealization.super.isProtected(s);

        return protectedFrom.contains(s);
    }


    /**
     * Add protection against attacking spells.
     */
    @Override
    public void setProtection(Set<AttackingSpell> attacks) {

        MagicEffectRealization.super.setProtection(attacks);

        protectedFrom.addAll(attacks);
    }


    /**
     * Remove protection against attacking spells.
     */
    @Override
    public void removeProtection(Set<AttackingSpell> attacks) {

        MagicEffectRealization.super.removeProtection(attacks);

        protectedFrom.removeAll(attacks);
    }

}