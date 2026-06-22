package a12429280;

/**
 * HealthPotions increase the consumer's mana
 */
public class HealthPotion extends Potion {
	private int health ; // must not be negative
	/**
	 * @param name name
	 * @param usages number of usages still left
	 * @param price price
	 * @param weight weight
	 * @param health change of health on consumer
	 */
	public HealthPotion(String name, int usages, int price, int weight, int health) {
		super(name, usages, price, weight); AssertValue.isPositive(health);
		this.health = health;
	}
	/**
	 * returns "; +'health' HP".
	 * e.g. (total result of toString) "[Health Potion; 1 g; 1 Knut; 5 gulps; +10 HP]"
	 * @return "; +'health' HP"
	 */
	@Override public String additionalOutputString() {
		return String.format("; +%d HP", health);
	}
	public int getHealth() { return health; }
	@Override public void applyEffectsDefinedBy(ItemApplication visitor) {
		if (this.ableToApplyEffect()) visitor.applyEffectFrom(this);
	}
}