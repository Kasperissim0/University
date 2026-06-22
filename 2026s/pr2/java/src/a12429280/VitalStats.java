package a12429280;

/**
 * Manages the health and magic energy (mana) of a magical entity.
 * Handles the application of damage, healing, and magic consumption.
 */
public class VitalStats {
    private int defaultHealthPoints;
    private int healthPoints;
    private int defaultManaPoints;
    private int manaPoints;

    /**
     * @param defaultHealthPoints base for percentage health calculations
     * @param healthPoints current health
     * @param defaultManaPoints base for percentage mana calculations
     * @param manaPoints current mana
     */
    public VitalStats(int defaultHealthPoints, int healthPoints, int defaultManaPoints, int manaPoints) {
        AssertValue.isPositive(defaultHealthPoints); AssertValue.isPositive(healthPoints);
        AssertValue.isPositive(defaultManaPoints); AssertValue.isPositive(manaPoints);
        
        this.defaultHealthPoints = defaultHealthPoints;
        this.healthPoints = healthPoints;
        this.defaultManaPoints = defaultManaPoints;
        this.manaPoints = manaPoints;
    }

    /**
     * @return the default Health Points value
     */
    public int getDefaultHealthPoints() { 
        return defaultHealthPoints; 
    }

    /**
     * @return the current Health Points value
     */
    public int getHealthPoints() { 
        return healthPoints; 
    }

    /**
     * @return the default Mana Points value
     */
    public int getDefaultManaPoints() { 
        return defaultManaPoints; 
    }

    /**
     * @return the current Mana Points value
     */
    public int getManaPoints() { 
        return manaPoints; 
    }

    /**
     * Return true, if health is 0, false otherwise.
     * @return true, if health is 0, false otherwise
     */
    public boolean isDead() { 
        return healthPoints == 0; 
    }

    /**
     * Checks if there is enough mana and deducts it if possible.
     * @param amount amount of mana needed
     * @return true if mana is successfully provided, false otherwise
     */
    public boolean provideMana(int amount) {
        if (manaPoints < amount) return false;
        
        manaPoints -= amount; return true;
    }

    /**
     * Reduce the health by amount ensuring however that health does not become negative.
     * @param amount amount to be deducted from health 
     */
    public void takeDamage(int amount) {
        healthPoints -= amount; 
        if (healthPoints < 0) healthPoints = 0;
    }

    /**
     * Reduce the health by the percentage given of the default health value 
     * ensuring however that health does not become negative.
     * @param percentage percentage of damage done
     */
    public void takeDamagePercent(int percentage) {
        healthPoints -= (int)(defaultHealthPoints * (percentage / 100.0)); 
        if (healthPoints < 0) healthPoints = 0;
    }

    /**
     * Reduce the mana by amount ensuring however that mana does not become negative.
     * @param amount amount to be deducted from mana 
     */
    public void weakenMagic(int amount) {
        manaPoints -= amount; 
        if (manaPoints < 0) manaPoints = 0;
    }

    /**
     * Reduce the mana by the percentage given of the default mana value 
     * ensuring however that mana does not become negative.
     * @param percentage percentage of damage done
     */
    public void weakenMagicPercent(int percentage) {
        manaPoints -= (int)(defaultManaPoints * (percentage / 100.0)); 
        if (manaPoints < 0) manaPoints = 0;
    }

    /**
     * Increase the health by the amount given.
     * @param amount amount to increase health
     */
    public void heal(int amount) {
        healthPoints += amount;
    }

    /**
     * Increase the health by the percentage given of the default health.
     * @param percentage percentage of healing done
     */
    public void healPercent(int percentage) {
        healthPoints += (int)(defaultHealthPoints * (percentage / 100.0));
    }

    /**
     * Increase the mana by the amount given.
     * @param amount amount to increase mana
     */
    public void enforceMagic(int amount) {
        manaPoints += amount;
    }

    /**
     * Increase the mana by the percentage given of the default mana.
     * @param percentage percentage of mana increase
     */
    public void enforceMagicPercent(int percentage) {
        manaPoints += (int)(defaultManaPoints * (percentage / 100.0));
    }
}