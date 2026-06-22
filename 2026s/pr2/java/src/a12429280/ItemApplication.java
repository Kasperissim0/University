package a12429280;

public interface ItemApplication {
	default boolean ableToApplyEffect() {
		return true;
	}
	void applyEffectFrom(HealthPotion item);
 	void applyEffectFrom(ManaPotion   item);
	void applyEffectFrom(Concoction   item);
	void applyEffectFrom(Scroll       item);
}