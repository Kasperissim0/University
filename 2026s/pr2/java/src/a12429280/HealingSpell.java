package a12429280;

/**
 * Healing spells increase the targets health or mana
 */
public class HealingSpell extends ApplicationSpell {
	/**
	 * @param name name
	 * @param manaCost manaCost
	 * @param levelNeeded levelNeeded
	 * @param type defines if health or mana is affected
	 * @param percentage defines if amount is an absolute or a percentage value
	 * @param amount amount
	 */
	public HealingSpell(String name, int manaCost, MagicLevel levelNeeded, boolean type, boolean percentage, int amount) {
		super(name, manaCost, levelNeeded, type, percentage, amount);
	}
	/**
	 * Use one of the functions heal, healPercent, enforceMagic or enforceMagicPercent according
	 * to the flags type and percentage
	 * @param target target that receives healing
	 */
	@Override public void doEffect(MagicEffectRealization target) {
		if (affectsHealth())
			this.applyEffect(MagicEffectRealization::heal, MagicEffectRealization::healPercent, target);
		else
			this.applyEffect(MagicEffectRealization::enforceMagic, MagicEffectRealization::enforceMagicPercent, target);
	}
	/**
	 * Returns "; +'amount' 'percentage' 'HPorMP'", where 'percentage' is a '%'-sign if percentage
	 * is true, empty otherwise and HPorMP is HP if type is true, MP otherwise
	 * e. g. "; +10 HP" or "; +50 % MP"
	 * @return "; +'amount' 'percentage' 'HPorMP'"
	 */
	@Override public char getOperationSign() { return '+'; }
}