package a12429280;

import java.util.HashSet;
import java.util.Random;
import java.util.Set;

/**
 * Manages financial transactions and carrying capacity for magical items.
 * Handles storing, retrieving, paying, and earning functionality for a Trader.
 */
public class Inventory {
    private int            money;
    private int            carryingCapacity;
    private Set<Tradeable> items;

    /**
     * @param money current money
     * @param carryingCapacity maximum carrying capacity
     * @param items set of items currently carried
     */
    public Inventory(int money, int carryingCapacity, Set<Tradeable> items) {
        AssertValue.isPositive(money); AssertValue.isPositive(carryingCapacity);
        AssertValue.isNotNull(items);
        
        this.money = money;
        this.carryingCapacity = carryingCapacity;
        this.items = new HashSet<>(items);
        
        if (inventoryTotalWeight() > carryingCapacity) {
            throw new IllegalArgumentException("inventory is too heavy");
        }
    }

    /**
     * @return the current money
     */
    public int getMoney() { 
        return money; 
    }

    /**
     * @return the set of items in the inventory
     */
    public Set<Tradeable> getItems() { 
        return items; 
    }

    /**
     * Calculates and returns the total weight of all the items in the inventory.
     * @return total weight of all items
     */
    public int inventoryTotalWeight() {
        return items.stream().mapToInt(Tradeable::getWeight).sum();
    }

    /**
     * Return true, if the item is present in the inventory, false otherwise.
     * @param item object is tested if it is in inventory
     * @return true if the item is in the inventory, false otherwise
     */
    public boolean containsItem(Tradeable item) {
        AssertValue.isNotNull(item);
        return items.contains(item);
    }

    /**
     * Return true, if money is greater than or equal to the amount, false otherwise.
     * @param amount amount to test
     * @return true if affordable, false otherwise
     */
    public boolean hasEnoughMoney(int amount) {
        AssertValue.isPositive(amount);
        return money >= amount;
    }

    /**
     * Return true, if current total weight plus the new weight is less than or equal to carryingCapacity.
     * @param weight weight to test
     * @return true if capacity is sufficient, false otherwise
     */
    public boolean hasAvailableCapacity(int weight) {
        AssertValue.isPositive(weight);
        return (inventoryTotalWeight() + weight) <= carryingCapacity;
    }

    /**
     * Deducts amount from money.
     * @param amount amount to be payed
     */
    public void deductMoney(int amount) {
        AssertValue.isPositive(amount);
        money -= amount;
    }

    /**
     * Adds amount to money.
     * @param amount amount to be received
     */
    public void addMoney(int amount) {
        AssertValue.isPositive(amount);
        money += amount;
    }

    /**
     * Adds item to inventory if carryingCapacity is sufficient.
     * @param item item to be added
     * @return true if item is successfully added, false otherwise
     */
    public boolean addItem(Tradeable item) {
        AssertValue.isNotNull(item);
        if (!hasAvailableCapacity(item.getWeight())) return false;
        return items.add(item);
    }

    /**
     * Removes item from inventory.
     * @param item item to be removed
     * @return true if item is successfully removed, false otherwise
     */
    public boolean removeItem(Tradeable item) {
        AssertValue.isNotNull(item);
        return items.remove(item);
    }

    /**
     * Returns whether the inventory has no items.
     * @return true if empty, false otherwise
     */
    public boolean isEmpty() {
        return items.isEmpty();
    }

    /**
     * Selects and returns a random item from the inventory.
     * @return a random Tradeable item or null if empty
     */
    public Tradeable getRandomItem() {
        if (items.isEmpty()) return null;
        return items.toArray(new Tradeable[0])[new Random().nextInt(items.size())];
    }

    /**
     * Empties the inventory of all items.
     */
    public void clear() {
        items.clear();
    }
}