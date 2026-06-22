package a12429280;

import java.util.Set;

/**
 * This interface contains all the methods to realize various magic effects on an object.
 * Most methods default to doing nothing and should be overriden for classes that can be
 * influenced by magic. The overrides define what exactly will happen given a specific
 * magic effect on the specific object.
 */
interface MagicEffectRealization extends ItemApplication {
    /**
     * Negative amount must throw IllegalArgumentException;
     * a typical implementation will reduce the object's HP by amount ensuring however
     * that HP does not become negative.
     * 
     * @param amount amount of damage done
     */
	default void takeDamage(int amount) {
		AssertValue.isPositive(amount);
	} 
	/**
     * Percentage must be between 0 and 100 (inclusive) otherwise an IllegalArgumentException
     * must be thrown;
     * a typical implementation will reduce the object's HP by the percentage given of the
     * object's basic HP value ensuring however, that HP does not become negative.
     * calculations must be done in double data type converting back to int only in the
     * last step
     * 
     * @param percentage percentage of damage relative to object's basic HP value
     */
	default void takeDamagePercent(int percentage) {
		AssertValue.isAValidPercentage(percentage);
	}
    /**
     * Negative amount must throw IllegalArgumentException;
     * a typical implementation will reduce the object's MP by amount ensuring however
     * that MP does not become negative.
     * 
     * @param amount amount of damage done
     */
	default void weakenMagic(int amount) {
		AssertValue.isPositive(amount);
	}
    /**
     * Percentage must be between 0 and 100 (inclusive) otherwise an IllegalArgumentException
     * must be thrown;
     * a typical implementation will reduce the object's MP by the percentage given of the
     * object's basic MP value value ensuring however, that MP does not become negative..
     * calculations must be done in double data type converting back to int only in the last step
     * 
     * @param percentage percentage of damage relative to object's basic MP value
     */
	default void weakenMagicPercent(int percentage) {
		AssertValue.isAValidPercentage(percentage);
	}
	/**
	 * Negative amount must throw IllegalArgumentException;
	 * a typical implementation will increase the object's HP by the amount given.
	 * 
     * @param amount amount of healing done
	 */
	default void heal(int amount) {
		AssertValue.isPositive(amount);
	}
    /**
     * Percentage must be between 0 and 100 (inclusive) otherwise an IllegalArgumentException
     * must be thrown;
     * a typical implementation will increase the object's HP by the percentage given of the
     * object's basic HP value.
     * calculations must be done in double data type converting back to int only in the last step
     * 
     * @param percentage percentage of healing relative to object's basic MP value
     */
	default void healPercent(int percentage) {
		AssertValue.isAValidPercentage(percentage);
	}
    /**
     * Negative amount must throw IllegalArgumentException;
     * a typical implementation will increase the object's MP by the amount given.
     * 
     * @param amount amount to increase mana
     */
	default void enforceMagic(int amount) {
		AssertValue.isPositive(amount);
	}
    /**
     * Percentage must be between 0 and 100 (inclusive) otherwise an IllegalArgumentException
     * must be thrown;
     * a typical implementation will increase the object's MP by the percentage given of the
     * object's basic MP value
     * calculations must be done in double data type converting back to int only in the last
     * step
     * 
     * @param percentage percentage of mana increase relative to object's basic MP value
     */
	default void enforceMagicPercent(int percentage) {
		AssertValue.isAValidPercentage(percentage);
	}
    /**
     * If s is null, an IllegalArgumentException must be thrown;
     * an implementation returns true if the object is protected against the spell s, false
     * otherwise.
     * 
     * @param s spell to test for 
     * @return true if object is protected against spell s
     */
	default boolean isProtected(Spell s) {
		AssertValue.isNotNull(s);
		return false;
	}
    /**
     * If attacks is null an IllegalArgumentException must be thrown;
     * a typical implementation will register the object as protected against all the spells
     * in attacks
     * 
     * @param attacks list of attacking spells that the object gets protected against
     */
	default void setProtection(Set<AttackingSpell> attacks) {
		AssertValue.isNotNull(attacks);
	}
    /**
     * If attacks is null an IllegalArgumentException must be thrown;
     * a typical implementation will register the object as not protected against all the spells
     * in attacks
     * 
     * @param attacks list of attacking spells that the object loses protection against
     */
	default void removeProtection(Set<AttackingSpell> attacks) {
		AssertValue.isNotNull(attacks);
	}
	/**
	 * Visits a HealthPotion to apply its effects to this object.
	 * If the potion has remaining usages, it increases the object's HP.
	 * @param potion the HealthPotion being consumed
	 */
	@Override default void applyEffectFrom(HealthPotion potion) {
		this.heal(potion.getHealth());
	}
	/**
	 * Visits a ManaPotion to apply its effects to this object.
	 * If the potion has remaining usages, it increases the object's MP.
	 * @param potion the ManaPotion being consumed
	 */
	@Override default void applyEffectFrom(ManaPotion potion) {
		this.enforceMagic(potion.getMana());
	}
	/**
	 * Visits a Concoction to apply its complex effects to this object.
	 * If the concoction has remaining usages, it alters health and mana based
	 * on its positive or negative values, and casts any spells it contains.
	 * @param concoction the Concoction being consumed
	 */
	@Override default void applyEffectFrom(Concoction concoction) {
		if (concoction.getHealth() >= 0) 
			this.heal(concoction.getHealth());
		else 
			this.takeDamage(-concoction.getHealth());

		if (concoction.getMana() >= 0) 
			this.enforceMagic(concoction.getMana());
		else 
			this.weakenMagic(-concoction.getMana());

		for (Spell s : concoction.getSpells()) 
			s.cast(concoction, this);
	}
	/**
	 * Visits a Scroll to apply its effects to this object.
	 * If the scroll has remaining usages, it casts the spell written on it.
	 * @param scroll the Scroll being read
	 */
	@Override default void applyEffectFrom(Scroll scroll) {
		scroll.getSpell().cast(scroll, this);
	}
}