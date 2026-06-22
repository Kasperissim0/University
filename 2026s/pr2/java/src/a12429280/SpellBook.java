package a12429280;

import java.util.HashSet;
import java.util.Random;
import java.util.Set;

/**
 * Manages the magical knowledge and active protections of an entity.
 * Handles learning, forgetting, and checking known spells, as well as 
 * adding and removing magical protections.
 */
public class SpellBook {
    private Set<Spell>          knownSpells;
    private Set<AttackingSpell> protectedFrom;

    /**
     * @param knownSpells set of known spells
     * @param protectedFrom set of spells the object is protected against
     */
    public SpellBook(Set<Spell> knownSpells, Set<AttackingSpell> protectedFrom) {
        AssertValue.isNotNull(knownSpells); AssertValue.isNotNull(protectedFrom);
        
        this.knownSpells = new HashSet<>(knownSpells);
        this.protectedFrom = new HashSet<>(protectedFrom);
    }

    /**
     * @return the set of currently known spells
     */
    public Set<Spell> getKnownSpells() { 
        return knownSpells; 
    }

    /**
     * @return the set of attacking spells currently granting protection
     */
    public Set<AttackingSpell> getProtectedFrom() { 
        return protectedFrom; 
    }

    /**
     * Adds a spell to the set of known spells.
     * @param s spell to be added
     * @return true if insertion was successful, false otherwise
     */
    public boolean addSpell(Spell s) {
        AssertValue.isNotNull(s);
        return knownSpells.add(s);
    }

    /**
     * Removes a spell from the set of known spells.
     * @param s spell to remove
     * @return true if removal was successful, false otherwise
     */
    public boolean removeSpell(Spell s) {
        AssertValue.isNotNull(s);
        return knownSpells.remove(s);
    }

    /**
     * Tests if a specific spell is present in the spellbook.
     * @param s spell to test
     * @return true if the spell is present, false otherwise
     */
    public boolean containsSpell(Spell s) {
        AssertValue.isNotNull(s);
        return knownSpells.contains(s);
    }

    /**
     * Checks if there are any spells recorded in the spellbook.
     * @return true if no spells are present, false otherwise
     */
    public boolean isEmpty() {
        return knownSpells.isEmpty();
    }

    /**
     * Chooses a random spell from the set of known spells.
     * @return a random Spell or null if the set is empty
     */
    public Spell getRandomSpell() {
        if (knownSpells.isEmpty()) return null;
        return knownSpells.toArray(new Spell[0])[new Random().nextInt(knownSpells.size())];
    }

    /**
     * Returns true if there is active protection against the given spell.
     * @param s spell that is tested for
     * @return true if protected against spell s, false otherwise
     */
    public boolean containsProtectionAgainst(Spell s) {
        AssertValue.isNotNull(s);
        return protectedFrom.contains(s);
    }

    /**
     * Adds attacking spells to the active protections.
     * @param attacks spells against which protection is provided
     */
    public void addProtectionAgainst(Set<AttackingSpell> attacks) {
        AssertValue.isNotNull(attacks);
        protectedFrom.addAll(attacks);
    }

    /**
     * Removes specific attacking spells from the active protections.
     * @param attacks spells against which protection is removed 
     */
    public void removeProtectionAgainst(Set<AttackingSpell> attacks) {
        AssertValue.isNotNull(attacks);
        protectedFrom.removeAll(attacks);
    }
}