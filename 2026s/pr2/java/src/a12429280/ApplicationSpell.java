package a12429280;

import java.util.function.ObjIntConsumer;

public abstract class ApplicationSpell extends Spell {
	protected boolean type;       // true -> affects HP, false -> affects MP
	protected boolean percentage; // true -> use amonut as a %, false -> use amount as a number
	protected int     amount;     // has to be non negative ; if percentage == true , amount must be in the interval [0 ,100]
	/**
	 * @param name name
	 * @param manaCost manaCost
	 * @param levelNeeded levelNeeded
	 * @param type defines if health or mana is affected
	 * @param percentage defines if amount is an absolute or a percentage value
	 * @param amount amount
	 */
	public ApplicationSpell(String name, int manaCost, MagicLevel levelNeeded, boolean type, boolean percentage, int amount) {
		super(name, manaCost, levelNeeded); AssertValue.isPositive(amount); if (percentage) AssertValue.isAValidPercentage(amount);
		this.type       = type;
		this.percentage = percentage;
		this.amount     = amount;
	}
	@Override final public String additionalOutputString() {
		var sign = getOperationSign(); if (sign != '+' && sign != '-') throw new IllegalArgumentException("only 2 signs supported");
		return String.format("; %c%d %s%cP",
				sign,
				this.amount,
				percentage ? "% " : "",
				type ? 'H' : 'M');
	}
	protected void applyEffect (ObjIntConsumer<MagicEffectRealization> absoluteMethod, ObjIntConsumer<MagicEffectRealization> percentMethod,
								MagicEffectRealization target) {
		if (percentage) percentMethod.accept(target, amount);
		else            absoluteMethod.accept(target, amount);
	}
	abstract protected char getOperationSign();
}
