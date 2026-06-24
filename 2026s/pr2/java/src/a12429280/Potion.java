package a12429280;

import java.util.function.Function;
import java.util.stream.Collectors;

/**
 *  A potion has a specific magic effect on its consumer
 */
public abstract class Potion extends MagicItem {
	/**
	 * @param name name
	 * @param usages number of usages still left
	 * @param price price
	 * @param weight weight
	 */
	public Potion(String name, int usages, int price, int weight) {
		super(name, usages, price, weight);
	}
	/**
	 * Delegates to method call useOn(drinker)
	 * @param drinker the consumer of the potion
	 */
	public void drink(Wizard drinker) {
		AssertValue.isNotNull(drinker);
		if (getUsages() > 0)this.useOn(drinker);
	}
	/**
	 * returns "gulp" if usages is equal to 1, "gulps" otherwise
	 * @return "gulp" or "gulps" depending on number of usages left
	 */
	@Override public String usageString() {
		var msg = "gulp";
		return getUsages() == 1 ? msg : msg + "s";
	}
	/*
	public boolean checkName(int maxCount) {
		return getName().chars().mapToObj(token -> (char) token).collect(Collectors.groupingBy(Function.identity(), Collectors.counting())).values().stream()
			   .noneMatch(count -> count > maxCount);
	}
	*/
	public boolean checkName(int minCount) {
		return this.getName().toLowerCase().chars().mapToObj(c -> (char) c).collect(Collectors.groupingBy(Function.identity(), Collectors.counting()))
					.values().stream().anyMatch(count -> count >= minCount);
	}
	
}