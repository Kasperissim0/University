package a12429280;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class A_Main {

    private static int passed = 0;
    private static int failed = 0;
    private static String currentGroup = "";
    private static boolean groupPrinted = false;
    private static String currentAction = "";
    private static boolean actionPrinted = false;

    @FunctionalInterface private interface ThrowingRunnable {
        void run() throws Exception;
    }

    // ---------------------------------------------------------------
    // Helper: create a standard wizard
    // ---------------------------------------------------------------
    private static Wizard makeWizard(String name, MagicLevel level, int hp, int mp, int money, int capacity) {
        return new Wizard(
                name, level, hp, hp, mp, mp, money,
                new HashSet<>(), new HashSet<>(), capacity, new HashSet<>()
        );
    }

    private static void runGroup(String title, ThrowingRunnable test) {
        currentGroup = title;
        groupPrinted = false;
        try {
            test.run();
        } catch (Throwable t) {
            failed++;
            printHeaders();
            System.out.println("  [CRASH] " + title);
            System.out.println("          " + t.getClass().getSimpleName() + ": " + t.getMessage());
        }
    }

    private static void action(String description) {
        currentAction = description;
        actionPrinted = false;
    }

    private static void printHeaders() {
        if (!groupPrinted) {
            System.out.println("\n=== " + currentGroup + " ===");
            groupPrinted = true;
        }
        if (!actionPrinted && currentAction != null && !currentAction.isEmpty()) {
            System.out.println("  [ACTION] " + currentAction);
            actionPrinted = true;
        }
    }

    private static void check(String testName, boolean condition) {
        if (condition) {
            passed++;
        } else {
            printHeaders();
            System.out.println("  [FAIL]  " + testName);
            failed++;
        }
    }

    private static void checkEquals(String testName, Object actual, Object expected) {
        boolean ok = (expected == null) ? actual == null : expected.equals(actual);
        if (!ok) {
            printHeaders();
            System.out.println("          expected: " + expected);
            System.out.println("          actual:   " + actual);
        }
        check(testName, ok);
    }

    private static void checkContains(String testName, String text, String expectedPart) {
        boolean ok = text != null && text.contains(expectedPart);
        if (!ok) {
            printHeaders();
            System.out.println("          expected text to contain: " + expectedPart);
            System.out.println("          actual text:              " + text);
        }
        check(testName, ok);
    }

    private static void expectIllegalArgument(String testName, ThrowingRunnable action) {
        try {
            action.run();
            printHeaders();
            System.out.println("          expected IllegalArgumentException, but nothing was thrown");
            check(testName, false);
        } catch (IllegalArgumentException e) {
            check(testName, true);
        } catch (Throwable t) {
            printHeaders();
            System.out.println("          expected IllegalArgumentException, but got: " + t.getClass().getSimpleName());
            check(testName, false);
        }
    }

    // ================================================================
    public static void main(String[] args) {

        runGroup("MagicLevel", A_Main::testMagicLevel);
        runGroup("Spell output and constructors", A_Main::testSpells);
        runGroup("Potions and MagicItem behavior", A_Main::testPotions);
        runGroup("Scroll Edge Cases", A_Main::testScroll);
        runGroup("Wizard basics", A_Main::testWizardBasics);
        runGroup("Wizard HP/MP effects", A_Main::testWizardHPMP);
        runGroup("Spell casting and mana", A_Main::testSpellCastingAndMana);
        runGroup("Protection", A_Main::testProtection);
        runGroup("Trading & Transactions", A_Main::testTrading);
        runGroup("Random methods", A_Main::testRandomMethods);
        runGroup("Steal and loot", A_Main::testStealLoot);
        runGroup("Capacity edge cases", A_Main::testCapacityEdgeCases);
        runGroup("Null and negative argument checks", A_Main::testNullAndNegativeChecks);
        runGroup("Zero Boundaries (No Throw checks)", A_Main::testZeroBoundariesNoThrow);
        runGroup("Constructor integrity checks", A_Main::testConstructorIntegrityChecks);

        System.out.println("\n----------------------------------------");
        System.out.println("Results: " + passed + " passed, " + failed + " failed.");
    }

    // ================================================================
    private static void testMagicLevel() {
        action("Testing MagicLevel enum toMana() limits");
        checkEquals("NOOB.toMana()", MagicLevel.NOOB.toMana(), 50);
        checkEquals("ADEPT.toMana()", MagicLevel.ADEPT.toMana(), 100);
        checkEquals("STUDENT.toMana()", MagicLevel.STUDENT.toMana(), 200);
        checkEquals("EXPERT.toMana()", MagicLevel.EXPERT.toMana(), 500);
        checkEquals("MASTER.toMana()", MagicLevel.MASTER.toMana(), 1000);

        action("Testing MagicLevel enum toString() asterisks");
        checkEquals("NOOB.toString()", MagicLevel.NOOB.toString(), "*");
        checkEquals("ADEPT.toString()", MagicLevel.ADEPT.toString(), "**");
        checkEquals("STUDENT.toString()", MagicLevel.STUDENT.toString(), "***");
        checkEquals("EXPERT.toString()", MagicLevel.EXPERT.toString(), "****");
        checkEquals("MASTER.toString()", MagicLevel.MASTER.toString(), "*****");
    }

    // ================================================================
    private static void testSpells() {
        action("Creating AttackingSpell(Confringo, Absolute HP)");
        AttackingSpell hpAbs = new AttackingSpell("Confringo", 10, MagicLevel.NOOB, true, false, 20);
        checkEquals("AttackingSpell absolute HP toString", hpAbs.toString(), "[Confringo(*): 10 mana; -20 HP]");

        action("Creating AttackingSpell(Diffindo, Percentage MP)");
        AttackingSpell mpPercent = new AttackingSpell("Diffindo", 5, MagicLevel.NOOB, false, true, 50);
        checkEquals("AttackingSpell percentage MP toString", mpPercent.toString(), "[Diffindo(*): 5 mana; -50 % MP]");

        action("Creating HealingSpell(Episkey, Absolute HP)");
        HealingSpell hpHeal = new HealingSpell("Episkey", 5, MagicLevel.NOOB, true, false, 20);
        checkEquals("HealingSpell absolute HP toString", hpHeal.toString(), "[Episkey(*): 5 mana; +20 HP]");

        action("Creating HealingSpell(MpHeal, Percentage MP)");
        HealingSpell mpHeal = new HealingSpell("MpHeal", 8, MagicLevel.ADEPT, false, true, 50);
        checkEquals("HealingSpell percentage MP toString", mpHeal.toString(), "[MpHeal(**): 8 mana; +50 % MP]");

        action("Edge Case: Exhaustively testing remaining 4 Spell Flag permutations");
        AttackingSpell hpPercent = new AttackingSpell("HpPercent", 10, MagicLevel.NOOB, true, true, 50);
        checkContains("Attacking HP Percent", hpPercent.toString(), "-50 % HP");
        AttackingSpell mpAbs = new AttackingSpell("MpAbs", 10, MagicLevel.NOOB, false, false, 50);
        checkContains("Attacking MP Absolute", mpAbs.toString(), "-50 MP");
        HealingSpell hpPercentHeal = new HealingSpell("HpPercentHeal", 10, MagicLevel.NOOB, true, true, 50);
        checkContains("Healing HP Percent", hpPercentHeal.toString(), "+50 % HP");
        HealingSpell mpAbsHeal = new HealingSpell("MpAbsHeal", 10, MagicLevel.NOOB, false, false, 50);
        checkContains("Healing MP Absolute", mpAbsHeal.toString(), "+50 MP");

        action("Creating ProtectingSpell defending against multiple spells simultaneously");
        Set<AttackingSpell> multiDef = new HashSet<>(List.of(hpAbs, mpPercent));
        ProtectingSpell protegoMulti = new ProtectingSpell("ProtegoMulti", 15, MagicLevel.STUDENT, multiDef);
        checkContains("ProtectingSpell contains Confringo", protegoMulti.additionalOutputString(), "Confringo");
        checkContains("ProtectingSpell contains Diffindo", protegoMulti.additionalOutputString(), "Diffindo");
    }

    // ================================================================
    private static void testPotions() {
        action("Creating HealthPotion(5 gulps, 1 Knut)");
        HealthPotion hp = new HealthPotion("Health Potion", 5, 1, 1, 10);
        checkEquals("HealthPotion toString formatting", hp.toString(), "[Health Potion; 1 g; 1 Knut; 5 gulps; +10 HP]");

        action("Creating HealthPotion(1 gulp, 2 Knuts) -> Testing grammar rules");
        HealthPotion singularGulp = new HealthPotion("Small", 1, 2, 1, 5);
        checkEquals("HealthPotion singular gulp and plural Knuts", singularGulp.toString(), "[Small; 1 g; 2 Knuts; 1 gulp; +5 HP]");

        Wizard target = makeWizard("Target", MagicLevel.NOOB, 100, 50, 0, 10);
        action("Target.takeDamage(40)");
        target.takeDamage(40);
        
        action("hp.useOn(Target) -> Healing Target by 10 HP");
        hp.useOn(target);
        checkContains("HealthPotion useOn heals target", target.toString(), "70/100");
        checkContains("HealthPotion useOn reduces usages", hp.toString(), "4 gulps");

        action("Exhausting HealthPotion usages to 0");
        for (int i = 0; i < 4; i++) hp.useOn(target);
        checkContains("HealthPotion reaches 0 gulps", hp.toString(), "0 gulps");
        
        action("Using EMPTY HealthPotion on Target (Should fail silently)");
        hp.useOn(target); 
        checkContains("Empty potion does not heal", target.toString(), "110/100"); // HP is 110 due to overheal

        action("Using EMPTY ManaPotion on Target");
        ManaPotion emptyMana = new ManaPotion("Tiny", 1, 1, 1, 20);
        emptyMana.useOn(target); // Uses the 1 gulp
        emptyMana.useOn(target); // Should do nothing
        checkContains("Empty ManaPotion does not give mana", target.toString(), "70/50"); // MP is 70 due to overheal

        ManaPotion manaPotion = new ManaPotion("Small Mana", 2, 1, 1, 15);
        action("Target.weakenMagic(50)");
        target.weakenMagic(50);
        
        action("manaPotion.drink(Target)");
        manaPotion.drink(target);
        checkContains("Potion.drink delegates to useOn", target.toString(), "35/50"); // 70 - 50 + 15 = 35
        checkContains("Potion.drink reduces usages", manaPotion.toString(), "1 gulp");

        action("MagicItem takeDamagePercent boundary tests");
        HealthPotion boundPotion = new HealthPotion("Bounds", 10, 1, 1, 10);
        boundPotion.takeDamagePercent(0);
        checkContains("0% damage leaves usages unchanged", boundPotion.toString(), "10 gulps");
        boundPotion.takeDamagePercent(33); // 10 * (1 - 0.33) = 6.7 -> 6
        checkContains("33% damage truncates usages correctly to 6", boundPotion.toString(), "6 gulps");
        boundPotion.takeDamagePercent(100);
        checkContains("100% damage drops usages to 0", boundPotion.toString(), "0 gulps");

        AttackingSpell spell = new AttackingSpell("Confringo", 10, MagicLevel.NOOB, true, false, 20);
        action("new Concoction(\"My Brew\", usages:4, HP:-5, MP:+10, List(Confringo))");
        Concoction brew = new Concoction("My Brew", 4, 2, 2, -5, 10, List.of(spell));

        String brewText = brew.toString();
        checkContains("Concoction output contains negative HP", brewText, "-5 HP");
        checkContains("Concoction output contains positive MP", brewText, "+10 MP");
        checkContains("Concoction output contains cast", brewText, "cast");
        checkContains("Concoction output contains spell name", brewText, "Confringo");

        Wizard target2 = makeWizard("Target2", MagicLevel.NOOB, 100, 50, 0, 10);
        action("brew.useOn(Target2) -> Should apply HP, MP, and cast Spell");
        brew.useOn(target2);

        checkContains("Concoction useOn reduces usages", brew.toString(), "3 gulps");
        check("Concoction useOn applies at least HP change", !target2.toString().contains("100/100"));

        action("Testing Concoction omission formatting");
        Concoction partialBrew = new Concoction("Weird Brew", 1, 1, 1, 0, 15, new ArrayList<>());
        checkEquals("Concoction suppresses 0 health and empty spells", partialBrew.toString(), "[Weird Brew; 1 g; 1 Knut; 1 gulp; +15 MP]");

        Concoction singleHPBrew = new Concoction("HPBrew", 1, 1, 1, 10, 0, new ArrayList<>());
        checkEquals("Concoction suppresses 0 MP and empty spells", singleHPBrew.toString(), "[HPBrew; 1 g; 1 Knut; 1 gulp; +10 HP]");
    }

    // ================================================================
    private static void testScroll() {
        AttackingSpell bombarda = new AttackingSpell("Bombarda", 20, MagicLevel.ADEPT, true, true, 50);
        action("Creating Scroll(casts Bombarda)");
        Scroll scroll = new Scroll("Scroll of doom", 5, 100, 1, bombarda);

        checkContains("Scroll output contains casts", scroll.toString(), "casts");
        checkEquals("Scroll toString", scroll.toString(), "[Scroll of doom; 1 g; 100 Knuts; 5 uses; casts [Bombarda(**): 20 mana; -50 % HP]]");

        Wizard target = makeWizard("Target", MagicLevel.NOOB, 100, 50, 0, 10);
        action("Scroll.useOn(Target)");
        scroll.useOn(target);
        checkContains("Scroll can cast higher-level spell", target.toString(), "50/100");
        checkContains("Scroll usage decreases to 4", scroll.toString(), "4 uses");

        action("Using EMPTY Scroll (0 usages left)");
        Scroll emptyScroll = new Scroll("Empty", 0, 1, 1, bombarda);
        emptyScroll.useOn(target);
        checkContains("Empty scroll does not cast spell", target.toString(), "50/100"); // Remains at 50

        action("Scroll casting MASTER spell by NOOB wizard");
        AttackingSpell masterSpell = new AttackingSpell("Avada", 500, MagicLevel.MASTER, true, true, 100);
        Scroll masterScroll = new Scroll("Doom", 5, 100, 1, masterSpell);
        Wizard noob = makeWizard("NoobTarget", MagicLevel.NOOB, 100, 50, 0, 10);
        
        masterScroll.useOn(noob); 
        checkContains("Scroll bypasses target's low level and mana", noob.toString(), "0/100");
    }

    // ================================================================
    private static void testWizardBasics() {
        action("Creating basic Wizard (Ignatius)");
        Wizard w = makeWizard("Ignatius", MagicLevel.ADEPT, 100, 150, 72, 100);

        String text = w.toString();
        check("Wizard toString starts with name and level", text.startsWith("[Ignatius(**):"));
        checkContains("Wizard toString contains HP/basicHP", text, "100/100");
        checkContains("Wizard toString contains MP/basicMP", text, "150/150");
        checkContains("Wizard toString contains money", text, "72 Knuts");
        checkContains("Wizard toString contains known spells", text, "knows [");
        checkContains("Wizard toString contains inventory", text, "carries [");

        action("Wizard(money: 1) -> Checking grammar");
        Wizard oneKnut = makeWizard("Bob", MagicLevel.NOOB, 50, 50, 1, 10);
        checkContains("Wizard toString uses singular Knut", oneKnut.toString(), "1 Knut;");

        check("Alive wizard is not dead", !w.isDead());

        AttackingSpell spell = new AttackingSpell("Confringo", 10, MagicLevel.NOOB, true, false, 20);
        action("Ignatius.learn(Confringo)");
        check("learn returns true for new spell", w.learn(spell));
        check("learn returns false for duplicate spell", !w.learn(spell));
        
        action("Ignatius.forget(Confringo)");
        check("forget returns true for known spell", w.forget(spell));
        check("forget returns false for unknown spell", !w.forget(spell));

        Wizard dead = makeWizard("Dead", MagicLevel.NOOB, 0, 50, 10, 10);
        action("Dead wizard attempts to learn/forget/pay/earn");
        check("Dead wizard is dead", dead.isDead());
        check("Dead wizard cannot learn", !dead.learn(spell));
        check("Dead wizard cannot forget", !dead.forget(spell));
        check("Dead wizard cannot pay money", !dead.pay(5));
        check("Dead wizard cannot earn money", !dead.earn(5));

        action("Inventory: Add duplicate and Remove non-existent checks");
        HealthPotion invPot = new HealthPotion("InvPot", 1, 1, 1, 10);
        w.addToInventory(invPot);
        check("addToInventory returns false for duplicate items", !w.addToInventory(invPot));
        check("removeFromInventory returns false for unowned items", !w.removeFromInventory(new HealthPotion("X", 1, 1, 1, 10)));
    }

    // ================================================================
    private static void testWizardHPMP() {
        Wizard w = makeWizard("Harry", MagicLevel.NOOB, 100, 50, 0, 10);

        action("Harry takes 80 flat damage");
        w.takeDamage(80);
        checkContains("takeDamage reduces HP", w.toString(), "20/100");

        action("Harry takes 50 flat damage (overflow)");
        w.takeDamage(50);
        checkContains("takeDamage clamps HP to 0", w.toString(), "0/100");
        check("Wizard is dead after HP reaches 0", w.isDead());

        action("Harry heals flat 30");
        w.heal(30);
        checkContains("heal increases HP", w.toString(), "30/100");

        action("Harry heals 50% basic HP");
        w.healPercent(50);
        checkContains("healPercent adds percent of basicHP", w.toString(), "80/100");

        action("Harry takes 20% basic HP damage");
        w.takeDamagePercent(20);
        checkContains("takeDamagePercent subtracts percent of basicHP", w.toString(), "60/100");

        action("Harry weakens 30 flat MP");
        w.weakenMagic(30);
        checkContains("weakenMagic reduces MP", w.toString(), "20/50");

        action("Harry weakens 100 flat MP (overflow)");
        w.weakenMagic(100);
        checkContains("weakenMagic clamps MP to 0", w.toString(), "0/50");

        action("Harry enforces 25 flat MP");
        w.enforceMagic(25);
        checkContains("enforceMagic increases MP", w.toString(), "25/50");

        action("Harry enforces 100% basic MP");
        w.enforceMagicPercent(100);
        checkContains("enforceMagicPercent adds percent of basicMP", w.toString(), "75/50");

        action("Harry weakens 50% basic MP");
        w.weakenMagicPercent(50);
        checkContains("weakenMagicPercent subtracts percent of basicMP", w.toString(), "50/50");

        action("Testing Double Truncation logic (33% of 150 = 49.5 -> 49 damage)");
        Wizard mathWizard = makeWizard("Math", MagicLevel.NOOB, 150, 150, 0, 10);
        mathWizard.takeDamagePercent(33); 
        checkContains("takeDamagePercent truncates doubles correctly", mathWizard.toString(), "101/150");

        action("Testing Overheal (Allowing HP to exceed basicHP limits)");
        Wizard overhealWizard = makeWizard("Overhealer", MagicLevel.NOOB, 100, 50, 0, 10);
        overhealWizard.healPercent(100); // Should add 100 to the 100 they already have
        checkContains("healPercent successfully overheals past basic bounds", overhealWizard.toString(), "200/100");
    }

    // ================================================================
    private static void testSpellCastingAndMana() {
        Wizard noob = makeWizard("Noob", MagicLevel.NOOB, 100, 50, 0, 10);
        Wizard target = makeWizard("Target", MagicLevel.NOOB, 100, 50, 0, 10);
        AttackingSpell weakSpell = new AttackingSpell("SmallHit", 10, MagicLevel.NOOB, true, false, 20);
        AttackingSpell highSpell = new AttackingSpell("HighHit", 10, MagicLevel.ADEPT, true, false, 20);

        action("Noob.provideMana(NOOB, 10)");
        check("provideMana returns true if level and mana are enough", noob.provideMana(MagicLevel.NOOB, 10));
        checkContains("provideMana subtracts MP", noob.toString(), "40/50");

        action("Noob.provideMana(ADEPT, 10) -> Requires higher level");
        check("provideMana returns false if level is too low", !noob.provideMana(MagicLevel.ADEPT, 10));

        action("Noob.provideMana(NOOB, 999) -> Requires more MP than they have");
        check("provideMana returns false if MP < manaAmount", !noob.provideMana(MagicLevel.NOOB, 999));

        noob.learn(weakSpell);
        action("Noob.castSpell(weakSpell, Target)");
        check("castSpell returns true if spell is known", noob.castSpell(weakSpell, target));
        checkContains("castSpell applies effect", target.toString(), "80/100");

        noob.learn(highSpell);
        action("Noob.castSpell(highSpell, Target)");
        check("castSpell returns true if spell is known even when provideMana later fails", noob.castSpell(highSpell, target));
        checkContains("high-level spell does not apply effect if level too low", target.toString(), "80/100");

        action("EmptyMana wizard casts spell -> Should fail silently internally");
        Wizard emptyMana = makeWizard("EmptyMana", MagicLevel.NOOB, 100, 50, 0, 10);
        emptyMana.weakenMagic(50); // Set MP to 0
        emptyMana.learn(weakSpell);
        Wizard target2 = makeWizard("Target2", MagicLevel.NOOB, 100, 50, 0, 10);
        
        check("castSpell returns true because spell is known", emptyMana.castSpell(weakSpell, target2));
        checkContains("spell does not apply effect if mana is missing", target2.toString(), "100/100");

        Wizard dead = makeWizard("Dead", MagicLevel.NOOB, 0, 50, 0, 10);
        action("DeadWizard.provideMana / DeadWizard.castSpell");
        check("Dead wizard cannot provide mana", !dead.provideMana(MagicLevel.NOOB, 1));
        check("Dead wizard cannot cast known spell", !dead.castSpell(weakSpell, target));
    }

    // ================================================================
    private static void testProtection() {
        AttackingSpell confringo = new AttackingSpell("Confringo", 10, MagicLevel.NOOB, true, false, 20);
        AttackingSpell diffindo = new AttackingSpell("Diffindo", 5, MagicLevel.NOOB, true, false, 15);
        ProtectingSpell protego = new ProtectingSpell("Protego", 15, MagicLevel.STUDENT, Set.of(confringo));

        Wizard target = makeWizard("Target", MagicLevel.STUDENT, 100, 300, 0, 10);
        action("Protego.doEffect(Target) -> Target gains protection against Confringo");
        protego.doEffect(target);

        check("Target is protected against selected spell", target.isProtected(confringo));
        check("Target is not protected against other spell", !target.isProtected(diffindo));

        Wizard attacker = makeWizard("Attacker", MagicLevel.NOOB, 100, 50, 0, 10);
        attacker.learn(confringo);

        action("Attacker casts Confringo on Protected Target (First Hit)");
        attacker.castSpell(confringo, target);
        check("Protection is removed after blocked attack", !target.isProtected(confringo));
        checkContains("Protected target takes no damage", target.toString(), "100/100");

        action("Attacker casts Confringo on Target (Second Hit)");
        attacker.castSpell(confringo, target);
        checkContains("Second attack damages target", target.toString(), "80/100");

        Set<AttackingSpell> attacks2 = new HashSet<>();
        attacks2.add(diffindo);

        action("Target.setProtection(Diffindo)");
        target.setProtection(attacks2);
        check("setProtection adds spell", target.isProtected(diffindo));

        action("Target.removeProtection(Diffindo)");
        target.removeProtection(attacks2);
        check("removeProtection removes spell", !target.isProtected(diffindo));
    }

    // ================================================================
    private static void testTrading() {
        Wizard giver = makeWizard("Giver", MagicLevel.NOOB, 100, 50, 100, 100);
        Wizard taker = makeWizard("Taker", MagicLevel.NOOB, 100, 50, 100, 20);
        HealthPotion potion = new HealthPotion("Health Potion", 5, 10, 1, 20);

        action("Giver gives potion to Taker");
        giver.addToInventory(potion);
        check("possesses returns true after add", giver.possesses(potion));
        check("hasCapacity returns true if item fits", taker.hasCapacity(potion.getWeight()));
        check("give returns true", potion.give(giver, taker));
        check("giver no longer has item after give", !giver.possesses(potion));
        check("taker has item after give", taker.possesses(potion));

        action("Giver attempts to give item to Taker with full inventory");
        Wizard fullTaker = makeWizard("Full", MagicLevel.NOOB, 100, 50, 100, 1);
        ManaPotion fatItem = new ManaPotion("Fat", 1, 10, 50, 50); // Weight 50
        giver.addToInventory(fatItem);
        check("give fails if receiver has no capacity", !fatItem.give(giver, fullTaker));
        check("giver kept the item after failed give", giver.possesses(fatItem));

        Wizard seller = makeWizard("Seller", MagicLevel.NOOB, 100, 50, 0, 100);
        Wizard buyer = makeWizard("Buyer", MagicLevel.NOOB, 100, 50, 50, 20);
        ManaPotion manaPotion = new ManaPotion("Mana Potion", 3, 10, 1, 30);
        seller.addToInventory(manaPotion);

        action("Buyer purchases Mana Potion from Seller");
        check("purchase returns true", manaPotion.purchase(seller, buyer));
        check("seller lost item after purchase", !seller.possesses(manaPotion));
        check("buyer got item after purchase", buyer.possesses(manaPotion));
        checkContains("buyer paid price", buyer.toString(), "40 Knuts");
        checkContains("seller earned price", seller.toString(), "10 Knuts");

        Wizard brokeBuyer = makeWizard("Broke", MagicLevel.NOOB, 100, 50, 5, 20);
        ManaPotion expensive = new ManaPotion("Expensive", 1, 100, 1, 50);
        seller.addToInventory(expensive);

        action("expensiveItem.purchase(Seller, BrokeBuyer) -> Too expensive");
        check("purchase returns false if buyer cannot afford", !expensive.purchase(seller, brokeBuyer));
        check("seller still has item after failed purchase", seller.possesses(expensive));
        check("broke buyer did not get item", !brokeBuyer.possesses(expensive));

        Wizard deadSeller = makeWizard("DeadSeller", MagicLevel.NOOB, 0, 50, 0, 20);
        ManaPotion item = new ManaPotion("Item", 1, 5, 1, 5);
        deadSeller.addToInventory(item);

        action("deadSeller.sellItem(...)");
        check("Dead wizard cannot sell item", !deadSeller.sellItem(item, buyer));

        action("Transaction Integrity Test: Buyer has money, but NO capacity");
        Wizard buyerNoCapacity = makeWizard("BuyerNoCap", MagicLevel.NOOB, 100, 50, 100, 2); 
        ManaPotion heavyItem = new ManaPotion("Heavy", 10, 50, 50, 30); // Weight is 50!
        seller.addToInventory(heavyItem);

        check("purchase fails if capacity is exceeded", !heavyItem.purchase(seller, buyerNoCapacity));
        checkContains("buyer did NOT lose money on failed purchase", buyerNoCapacity.toString(), "100 Knuts");
        checkContains("seller did NOT gain money on failed purchase", seller.toString(), "10 Knuts"); // Stays at 10 from previous sale
        check("seller retains item after failed capacity purchase", seller.possesses(heavyItem));
    }

    // ================================================================
    private static void testRandomMethods() {
        Wizard caster = makeWizard("Caster", MagicLevel.NOOB, 100, 50, 0, 10);
        Wizard target = makeWizard("Target", MagicLevel.NOOB, 100, 50, 0, 10);
        
        action("castRandomSpell with 0 known spells");
        check("castRandomSpell returns false if no spells are known", !caster.castRandomSpell(target));

        AttackingSpell spell = new AttackingSpell("OnlySpell", 10, MagicLevel.NOOB, true, false, 20);
        caster.learn(spell);
        action("castRandomSpell with 1 known spell");
        check("castRandomSpell returns true if one spell is known", caster.castRandomSpell(target));
        checkContains("castRandomSpell applies effect", target.toString(), "80/100");

        Wizard user = makeWizard("User", MagicLevel.NOOB, 100, 50, 0, 10);
        HealthPotion potion = new HealthPotion("OnlyPotion", 1, 1, 1, 30);
        
        action("useRandomItem with 0 items");
        check("useRandomItem returns false if inventory is empty", !user.useRandomItem(user));

        user.addToInventory(potion);
        user.takeDamage(50);
        action("useRandomItem with 1 item");
        check("useRandomItem returns true if one item exists", user.useRandomItem(user));
        checkContains("useRandomItem applies item effect", user.toString(), "80/100");

        Wizard seller = makeWizard("Seller", MagicLevel.NOOB, 100, 50, 0, 10);
        Wizard buyer = makeWizard("Buyer", MagicLevel.NOOB, 100, 50, 20, 10);
        ManaPotion sellPotion = new ManaPotion("OnlySellPotion", 1, 5, 1, 5);

        action("sellRandomItem with 0 items");
        check("sellRandomItem returns false if inventory is empty", !seller.sellRandomItem(buyer));

        seller.addToInventory(sellPotion);
        action("sellRandomItem with 1 item");
        check("sellRandomItem returns true if one item exists", seller.sellRandomItem(buyer));
        checkContains("sellRandomItem gives money to seller", seller.toString(), "5 Knuts");
        check("sellRandomItem transfers item to buyer", buyer.possesses(sellPotion));
    }

    // ================================================================
    private static void testStealLoot() {
        Wizard victim = makeWizard("Victim", MagicLevel.NOOB, 100, 50, 0, 20);
        Wizard thief = makeWizard("Thief", MagicLevel.NOOB, 100, 50, 0, 20);
        ManaPotion item = new ManaPotion("Mana Potion", 1, 5, 1, 10);
        victim.addToInventory(item);

        action("Victim.steal(Thief) -> Valid Steal");
        check("Alive wizard canSteal", thief.canSteal());
        check("steal returns true if item fits", victim.steal(thief));
        check("victim lost stolen item", !victim.possesses(item));
        check("thief got stolen item", thief.possesses(item));

        Wizard deadThief = makeWizard("DeadThief", MagicLevel.NOOB, 0, 50, 0, 20);
        ManaPotion item2 = new ManaPotion("Item2", 1, 1, 1, 5);
        victim.addToInventory(item2);

        action("Victim.steal(DeadThief) -> Dead men can't steal");
        check("Dead wizard cannot steal", !deadThief.canSteal());
        check("steal returns false if thief cannot steal", !victim.steal(deadThief));
        check("item stays with victim after failed steal", victim.possesses(item2));

        Wizard corpse = makeWizard("Corpse", MagicLevel.NOOB, 0, 50, 0, 20);
        Wizard looter = makeWizard("Looter", MagicLevel.NOOB, 100, 50, 0, 20);
        ManaPotion lootItem = new ManaPotion("LootItem", 1, 1, 1, 5);
        corpse.addToInventory(lootItem);

        action("Corpse.loot(Looter) -> Valid Loot");
        check("Dead wizard isLootable", corpse.isLootable());
        check("Alive wizard canLoot", looter.canLoot());
        check("loot returns true if item transferred", corpse.loot(looter));
        check("corpse lost item after loot", !corpse.possesses(lootItem));
        check("looter got item after loot", looter.possesses(lootItem));

        Wizard alive = makeWizard("Alive", MagicLevel.NOOB, 100, 50, 0, 20);
        ManaPotion aliveItem = new ManaPotion("AliveItem", 1, 1, 1, 5);
        alive.addToInventory(aliveItem);

        action("Alive.loot(Looter) -> Cannot loot living wizard");
        check("Alive wizard is not lootable", !alive.isLootable());
        check("loot returns false if target is alive", !alive.loot(looter));
        check("alive target keeps item after failed loot", alive.possesses(aliveItem));

        Wizard deadLooter = makeWizard("DeadLooter", MagicLevel.NOOB, 0, 50, 0, 20);
        action("DeadLooter.canLoot()");
        check("Dead wizard cannot loot", !deadLooter.canLoot());
    }

    // ================================================================
    private static void testCapacityEdgeCases() {
        Wizard victim = makeWizard("Victim", MagicLevel.NOOB, 100, 50, 0, 20);
        Wizard thiefNoCapacity = makeWizard("ThiefNoCapacity", MagicLevel.NOOB, 100, 50, 0, 0);
        HealthPotion heavy = new HealthPotion("Heavy", 1, 1, 5, 10);
        victim.addToInventory(heavy);

        action("Victim.steal(ThiefNoCapacity)");
        check("steal returns false if stolen item does not fit", !victim.steal(thiefNoCapacity));
        check("stolen item vanishes from victim if thief has no capacity", !victim.possesses(heavy));
        check("stolen item is not added to thief if capacity is missing", !thiefNoCapacity.possesses(heavy));

        Wizard corpse = makeWizard("Corpse", MagicLevel.NOOB, 0, 50, 0, 50);
        Wizard looterSmallCapacity = makeWizard("LooterSmallCapacity", MagicLevel.NOOB, 100, 50, 0, 1);
        HealthPotion small = new HealthPotion("Small", 1, 1, 1, 5);
        ManaPotion tooHeavy = new ManaPotion("TooHeavy", 1, 1, 10, 5);
        corpse.addToInventory(small);
        corpse.addToInventory(tooHeavy);

        action("Corpse.loot(LooterSmallCapacity) -> Partial transfer, heavy items vanish");
        check("loot returns true if at least one item fits", corpse.loot(looterSmallCapacity));
        check("small item is transferred during loot", looterSmallCapacity.possesses(small));
        check("heavy item vanishes during loot", !corpse.possesses(tooHeavy) && !looterSmallCapacity.possesses(tooHeavy));
        check("corpse loses small item during loot", !corpse.possesses(small));

        Wizard lowCapacity = makeWizard("LowCapacity", MagicLevel.NOOB, 100, 50, 0, 1);
        HealthPotion weightTwo = new HealthPotion("WeightTwo", 1, 1, 2, 5);

        action("LowCapacity.addToInventory(HeavyItem)");
        check("addToInventory returns false if capacity would be exceeded", !lowCapacity.addToInventory(weightTwo));
        check("item is not added if capacity is exceeded", !lowCapacity.possesses(weightTwo));
        
        Wizard exactCapacity = makeWizard("ExactCapacity", MagicLevel.NOOB, 100, 50, 0, 10);
        HealthPotion weightTen = new HealthPotion("Ten", 10, 1, 10, 5); // Weight 10
        action("ExactCapacity.addToInventory(ItemWeighting10)");
        check("addToInventory accepts item exactly matching max capacity", exactCapacity.addToInventory(weightTen));
    }

    // ================================================================
    private static void testNullAndNegativeChecks() {
        action("Triggering dozens of Null/Negative Exception branches...");
        Wizard w = makeWizard("W", MagicLevel.NOOB, 100, 50, 100, 20);
        Wizard other = makeWizard("Other", MagicLevel.NOOB, 100, 50, 100, 20);
        AttackingSpell attack = new AttackingSpell("Attack", 5, MagicLevel.NOOB, true, false, 10);
        HealthPotion potion = new HealthPotion("Potion", 1, 1, 1, 10);

        expectIllegalArgument("provideMana null level throws", () -> w.provideMana(null, 1));
        expectIllegalArgument("provideMana negative mana throws", () -> w.provideMana(MagicLevel.NOOB, -1));
        expectIllegalArgument("learn null throws", () -> w.learn(null));
        expectIllegalArgument("forget null throws", () -> w.forget(null));
        expectIllegalArgument("castSpell null spell throws", () -> w.castSpell(null, other));
        expectIllegalArgument("castSpell null target throws", () -> w.castSpell(attack, null));
        expectIllegalArgument("useItem null item throws", () -> w.useItem(null, other));
        expectIllegalArgument("useItem null target throws", () -> w.useItem(potion, null));
        expectIllegalArgument("sellItem null item throws", () -> w.sellItem(null, other));
        expectIllegalArgument("sellItem null target throws", () -> w.sellItem(potion, null));
        expectIllegalArgument("possesses null throws", () -> w.possesses(null));
        expectIllegalArgument("canAfford negative throws", () -> w.canAfford(-1));
        expectIllegalArgument("hasCapacity negative throws", () -> w.hasCapacity(-1));
        expectIllegalArgument("pay negative throws", () -> w.pay(-1));
        expectIllegalArgument("earn negative throws", () -> w.earn(-1));
        expectIllegalArgument("addToInventory null throws", () -> w.addToInventory(null));
        expectIllegalArgument("removeFromInventory null throws", () -> w.removeFromInventory(null));
        expectIllegalArgument("steal null thief throws", () -> w.steal(null));
        expectIllegalArgument("loot null looter throws", () -> w.loot(null));
        expectIllegalArgument("takeDamage negative throws", () -> w.takeDamage(-1));
        expectIllegalArgument("takeDamagePercent negative throws", () -> w.takeDamagePercent(-1));
        expectIllegalArgument("takeDamagePercent > 100 throws", () -> w.takeDamagePercent(101));
        expectIllegalArgument("weakenMagic negative throws", () -> w.weakenMagic(-1));
        expectIllegalArgument("weakenMagicPercent negative throws", () -> w.weakenMagicPercent(-1));
        expectIllegalArgument("weakenMagicPercent > 100 throws", () -> w.weakenMagicPercent(101));
        expectIllegalArgument("heal negative throws", () -> w.heal(-1));
        expectIllegalArgument("healPercent negative throws", () -> w.healPercent(-1));
        expectIllegalArgument("healPercent > 100 throws", () -> w.healPercent(101));
        expectIllegalArgument("enforceMagic negative throws", () -> w.enforceMagic(-1));
        expectIllegalArgument("enforceMagicPercent negative throws", () -> w.enforceMagicPercent(-1));
        expectIllegalArgument("enforceMagicPercent > 100 throws", () -> w.enforceMagicPercent(101));
        expectIllegalArgument("isProtected null throws", () -> w.isProtected(null));
        expectIllegalArgument("setProtection null throws", () -> w.setProtection(null));
        expectIllegalArgument("removeProtection null throws", () -> w.removeProtection(null));
        expectIllegalArgument("Tradeable.give null giver throws", () -> potion.give(null, other));
        expectIllegalArgument("Tradeable.give null taker throws", () -> potion.give(w, null));
        expectIllegalArgument("Tradeable.give same giver/taker throws", () -> potion.give(w, w));
        expectIllegalArgument("Tradeable.purchase null seller throws", () -> potion.purchase(null, other));
        expectIllegalArgument("Tradeable.purchase null buyer throws", () -> potion.purchase(w, null));
        expectIllegalArgument("Tradeable.purchase same seller/buyer throws", () -> potion.purchase(w, w));
        expectIllegalArgument("HealthPotion.useOn null throws", () -> potion.useOn(null));
        expectIllegalArgument("ManaPotion.useOn null throws", () -> new ManaPotion("M", 1, 1, 1, 1).useOn(null));
        expectIllegalArgument("Scroll.useOn null throws", () -> new Scroll("S", 1, 1, 1, attack).useOn(null));
        expectIllegalArgument("Concoction.useOn null throws", () -> new Concoction("C", 1, 1, 1, 1, 0, List.of()).useOn(null));
        
        w.learn(attack);
        w.addToInventory(potion);
        expectIllegalArgument("castRandomSpell null target throws when spells exist", () -> w.castRandomSpell(null));
        expectIllegalArgument("useRandomItem null target throws when inventory exists", () -> w.useRandomItem(null));
        expectIllegalArgument("sellRandomItem null target throws when inventory exists", () -> w.sellRandomItem(null));
    }

    // ================================================================
    private static void testZeroBoundariesNoThrow() {
        action("Executing Boundary values (0 and 100) to ensure NO exceptions are thrown");
        Wizard w = makeWizard("Boundary", MagicLevel.NOOB, 100, 50, 100, 20);
        
        // None of these should throw IllegalArgumentException
        w.takeDamage(0);
        w.takeDamagePercent(0);
        w.takeDamagePercent(100);
        
        w.weakenMagic(0);
        w.weakenMagicPercent(0);
        w.weakenMagicPercent(100);
        
        w.heal(0);
        w.healPercent(0);
        w.healPercent(100);
        
        w.enforceMagic(0);
        w.enforceMagicPercent(0);
        w.enforceMagicPercent(100);
        
        w.pay(0);
        w.earn(0);
        w.hasCapacity(0);
        w.canAfford(0);

        check("All boundary zeroes successfully executed without throwing", true);
    }

    // ================================================================
    private static void testConstructorIntegrityChecks() {
        action("Triggering dozens of Constructor Integrity checks...");
        expectIllegalArgument("AttackingSpell negative amount throws", () -> new AttackingSpell("X", 5, MagicLevel.NOOB, true, false, -1));
        expectIllegalArgument("AttackingSpell percent > 100 throws", () -> new AttackingSpell("X", 5, MagicLevel.NOOB, true, true, 101));
        expectIllegalArgument("HealingSpell negative amount throws", () -> new HealingSpell("X", 5, MagicLevel.NOOB, true, false, -1));
        expectIllegalArgument("HealingSpell percent > 100 throws", () -> new HealingSpell("X", 5, MagicLevel.NOOB, true, true, 101));
        expectIllegalArgument("ProtectingSpell null attacks throws", () -> new ProtectingSpell("X", 5, MagicLevel.NOOB, null));
        expectIllegalArgument("ProtectingSpell empty attacks throws", () -> new ProtectingSpell("X", 5, MagicLevel.NOOB, new HashSet<>()));
        expectIllegalArgument("HealthPotion negative health throws", () -> new HealthPotion("X", 1, 1, 1, -1));
        expectIllegalArgument("ManaPotion negative mana throws", () -> new ManaPotion("X", 1, 1, 1, -1));
        expectIllegalArgument("Concoction null spells throws", () -> new Concoction("X", 1, 1, 1, 5, 0, null));
        expectIllegalArgument("Concoction with no effect throws", () -> new Concoction("X", 1, 1, 1, 0, 0, List.of()));
        expectIllegalArgument("Scroll null spell throws", () -> new Scroll("X", 1, 1, 1, null));
        expectIllegalArgument("MagicItem null name throws", () -> new HealthPotion(null, 1, 1, 1, 1));
        expectIllegalArgument("MagicItem empty name throws", () -> new HealthPotion("", 1, 1, 1, 1));
        expectIllegalArgument("MagicItem negative usages throws", () -> new HealthPotion("X", -1, 1, 1, 1));
        expectIllegalArgument("MagicItem negative price throws", () -> new HealthPotion("X", 1, -1, 1, 1));
        expectIllegalArgument("MagicItem negative weight throws", () -> new HealthPotion("X", 1, 1, -1, 1));
        expectIllegalArgument("Spell null name throws", () -> new AttackingSpell(null, 5, MagicLevel.NOOB, true, false, 1));
        expectIllegalArgument("Spell empty name throws", () -> new AttackingSpell("", 5, MagicLevel.NOOB, true, false, 1));
        expectIllegalArgument("Spell negative manaCost throws", () -> new AttackingSpell("X", -1, MagicLevel.NOOB, true, false, 1));
        expectIllegalArgument("Spell null levelNeeded throws", () -> new AttackingSpell("X", 5, null, true, false, 1));
        expectIllegalArgument("Wizard null name throws", () -> makeWizard(null, MagicLevel.NOOB, 100, 50, 0, 10));
        expectIllegalArgument("Wizard empty name throws", () -> makeWizard("", MagicLevel.NOOB, 100, 50, 0, 10));
        expectIllegalArgument("Wizard null level throws", () -> makeWizard("X", null, 100, 50, 0, 10));
        expectIllegalArgument("Wizard negative basicHP throws", () -> new Wizard("X", MagicLevel.NOOB, -1, 0, 50, 50, 0, new HashSet<>(), new HashSet<>(), 10, new HashSet<>()));
        expectIllegalArgument("Wizard negative HP throws", () -> new Wizard("X", MagicLevel.NOOB, 100, -1, 50, 50, 0, new HashSet<>(), new HashSet<>(), 10, new HashSet<>()));
        expectIllegalArgument("Wizard basicMP lower than level mana throws", () -> new Wizard("X", MagicLevel.ADEPT, 100, 100, 50, 50, 0, new HashSet<>(), new HashSet<>(), 10, new HashSet<>()));
        expectIllegalArgument("Wizard negative MP throws", () -> new Wizard("X", MagicLevel.NOOB, 100, 100, 50, -1, 0, new HashSet<>(), new HashSet<>(), 10, new HashSet<>()));
        expectIllegalArgument("Wizard negative money throws", () -> new Wizard("X", MagicLevel.NOOB, 100, 100, 50, 50, -1, new HashSet<>(), new HashSet<>(), 10, new HashSet<>()));
        expectIllegalArgument("Wizard null knownSpells throws", () -> new Wizard("X", MagicLevel.NOOB, 100, 100, 50, 50, 0, null, new HashSet<>(), 10, new HashSet<>()));
        expectIllegalArgument("Wizard null protectedFrom throws", () -> new Wizard("X", MagicLevel.NOOB, 100, 100, 50, 50, 0, new HashSet<>(), null, 10, new HashSet<>()));
        expectIllegalArgument("Wizard negative carryingCapacity throws", () -> new Wizard("X", MagicLevel.NOOB, 100, 100, 50, 50, 0, new HashSet<>(), new HashSet<>(), -1, new HashSet<>()));
        expectIllegalArgument("Wizard null inventory throws", () -> new Wizard("X", MagicLevel.NOOB, 100, 100, 50, 50, 0, new HashSet<>(), new HashSet<>(), 10, null));
        
        Set<Tradeable> tooHeavyInventory = new HashSet<>();
        tooHeavyInventory.add(new HealthPotion("Heavy", 1, 1, 10, 1)); // weight 10
        expectIllegalArgument("Wizard inventory heavier than capacity throws", () -> new Wizard("X", MagicLevel.NOOB, 100, 100, 50, 50, 0, new HashSet<>(), new HashSet<>(), 1, tooHeavyInventory)); // capacity 1
    }
}