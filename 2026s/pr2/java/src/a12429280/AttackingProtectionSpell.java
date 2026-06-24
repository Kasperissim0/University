package a12429280;

import java.util.Set;

public class AttackingProtectionSpell extends AttackingSpell {

	public AttackingProtectionSpell(String name, int manaCost, MagicLevel levelNeeded, 
									boolean type, boolean percentage, int amount) {
		super(name, manaCost, levelNeeded, type, percentage, amount);
	}

	@Override public void cast(MagicSource source, MagicEffectRealization target) {
		super.cast(source, target); ((MagicEffectRealization) source).setProtection(Set.of(this));
	}
	
}
