/**
 * 
 */
package a12429280;

/**
 * 
 */
public class HazardousSpell extends AttackingSpell {
	private static int extraDamage = 10;
	public HazardousSpell(String name, int manaCost, MagicLevel levelNeeded, 
						  boolean type, boolean percentage, int amount) {
		super(name, manaCost, levelNeeded, type, percentage, amount);
	}

	@Override public void cast(MagicSource source, MagicEffectRealization target) {
		var caster = ((Wizard)source);
		
		if (caster.getHealth() > extraDamage) {
			super.cast(source, target);
			caster.takeDamage(extraDamage);
			extraDamage += 10;
		}
	}
	
}
