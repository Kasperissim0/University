package a12429280;

import java.util.Set;

/**
 * Magic spells that do some sort of damage to a target
 */
public class AttackingSpell extends ApplicationSpell {
	public AttackingSpell(String name, int manaCost, MagicLevel levelNeeded, boolean type, boolean percentage, int amount) {
		super(name, manaCost, levelNeeded, type, percentage, amount);
	}
	/**
	 * If the target is protected against this spell (isProtected), then protection against
	 * exactly this spell is removed (removeProtection).
	 * Otherwise use one of the functions takeDamage, takeDamagePercent, weakenMagic or
	 * weakenMagicPercent on target according to the flags type and percentage.
	 * @param target target that takes the damage
	*/
	@Override public void doEffect(MagicEffectRealization target) {
		if (target.isProtected(this)) target.removeProtection(Set.of(this));
		else
			if (type)
				this.applyEffect(MagicEffectRealization::takeDamage, MagicEffectRealization::takeDamagePercent, target);
			else
				this.applyEffect(MagicEffectRealization::weakenMagic, MagicEffectRealization::weakenMagicPercent, target);
	}
	/**
	 * Returns "; -'amount' 'percentage' 'HP or MP'".
	 * where 'percentage' is a '%'-sign if percentage is true,
	 * empty otherwise and HPorMP is HP if type is true, MP otherwise.
	 * E. g. "; -10 MP" or "; -50 % HP"
	 * @return "; -'amount' 'percentage' 'HP or MP'".
	 */
	@Override public char getOperationSign() { return '-'; }
}