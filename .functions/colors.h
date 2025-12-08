#ifndef COLORS_H
#define COLORS_H

#include <iostream>

// The core class for an ANSI escape code modifier.
// It's constexpr to allow for compile-time initialization of modifiers.
class AnsiModifier {
    int code;
public:
    constexpr AnsiModifier(int pCode) : code(pCode) {}

    // The friend function that sends the escape code to an output stream.
    friend std::ostream& operator<<(std::ostream& os, const AnsiModifier& mod) {
        return os << "\033[" << mod.code << "m";
    }
};

// The main namespace for all color and attribute modifiers.
namespace Color {

    // --- ATTRIBUTES ---
    struct ATTR {
        static inline constexpr AnsiModifier RESET{0};
        static inline constexpr AnsiModifier BOLD{1};
        static inline constexpr AnsiModifier DIM{2};
        static inline constexpr AnsiModifier ITALIC{3};
        static inline constexpr AnsiModifier UNDERLINE{4};
        static inline constexpr AnsiModifier BLINK{5};
        static inline constexpr AnsiModifier INVERSE{7};
        static inline constexpr AnsiModifier HIDDEN{8};
        static inline constexpr AnsiModifier STRIKETHROUGH{9};
    };
    
    // New alias for full word
    using Attribute = ATTR;

    // --- FOREGROUND COLORS ---
    struct FG {
        static inline constexpr AnsiModifier BLACK{30};
        static inline constexpr AnsiModifier RED{31};
        static inline constexpr AnsiModifier GREEN{32};
        static inline constexpr AnsiModifier YELLOW{33};
        static inline constexpr AnsiModifier BLUE{34};
        static inline constexpr AnsiModifier MAGENTA{35};
        static inline constexpr AnsiModifier CYAN{36};
        static inline constexpr AnsiModifier WHITE{37};
        struct Bright {
            static inline constexpr AnsiModifier BLACK{90};
            static inline constexpr AnsiModifier RED{91};
            static inline constexpr AnsiModifier GREEN{92};
            static inline constexpr AnsiModifier YELLOW{93};
            static inline constexpr AnsiModifier BLUE{94};
            static inline constexpr AnsiModifier MAGENTA{95};
            static inline constexpr AnsiModifier CYAN{96};
            static inline constexpr AnsiModifier WHITE{97};
        };
    };

    // --- BACKGROUND COLORS ---
    struct BG {
        static inline constexpr AnsiModifier BLACK{40};
        static inline constexpr AnsiModifier RED{41};
        static inline constexpr AnsiModifier GREEN{42};
        static inline constexpr AnsiModifier YELLOW{43};
        static inline constexpr AnsiModifier BLUE{44};
        static inline constexpr AnsiModifier MAGENTA{45};
        static inline constexpr AnsiModifier CYAN{46};
        static inline constexpr AnsiModifier WHITE{47};
        struct Bright {
            static inline constexpr AnsiModifier BLACK{100};
            static inline constexpr AnsiModifier RED{101};
            static inline constexpr AnsiModifier GREEN{102};
            static inline constexpr AnsiModifier YELLOW{103};
            static inline constexpr AnsiModifier BLUE{104};
            static inline constexpr AnsiModifier MAGENTA{105};
            static inline constexpr AnsiModifier CYAN{106};
            static inline constexpr AnsiModifier WHITE{107};
        };
    };

    // --- Default Aliases within the Color namespace ---
    // Provides direct access like `Color::RED`, `Color::BOLD`, etc.
    static constexpr auto& BLACK         = FG::BLACK;
    static constexpr auto& RED           = FG::RED;
    static constexpr auto& GREEN         = FG::GREEN;
    static constexpr auto& YELLOW        = FG::YELLOW;
    static constexpr auto& BLUE          = FG::BLUE;
    static constexpr auto& MAGENTA       = FG::MAGENTA;
    static constexpr auto& CYAN          = FG::CYAN;
    static constexpr auto& WHITE         = FG::WHITE;

    static constexpr auto& RESET         = ATTR::RESET;
    static constexpr auto& BOLD          = ATTR::BOLD;
    static constexpr auto& DIM           = ATTR::DIM;
    static constexpr auto& ITALIC        = ATTR::ITALIC;
    static constexpr auto& UNDERLINE     = ATTR::UNDERLINE;
    static constexpr auto& BLINK         = ATTR::BLINK;
    static constexpr auto& INVERSE       = ATTR::INVERSE;
    static constexpr auto& HIDDEN        = ATTR::HIDDEN;
    static constexpr auto& STRIKETHROUGH = ATTR::STRIKETHROUGH;

    // New aliases for full words
    using Foreground = FG;
    using Background = BG;
    using Attribute = ATTR;

} // namespace Color


// --- Global Aliases for convenience and backward compatibility ---
// Provides direct access like `red`, `bold`, etc.
static constexpr auto& black         = Color::FG::BLACK;
static constexpr auto& red           = Color::FG::RED;
static constexpr auto& green         = Color::FG::GREEN;
static constexpr auto& yellow        = Color::FG::YELLOW;
static constexpr auto& blue          = Color::FG::BLUE;
static constexpr auto& magenta       = Color::FG::MAGENTA;
static constexpr auto& cyan          = Color::FG::CYAN;
static constexpr auto& white         = Color::FG::WHITE;

static constexpr auto& reset         = Color::ATTR::RESET;
static constexpr auto& bold          = Color::ATTR::BOLD;
static constexpr auto& dim           = Color::ATTR::DIM;
static constexpr auto& italic        = Color::ATTR::ITALIC;
static constexpr auto& underline     = Color::ATTR::UNDERLINE;
static constexpr auto& blink         = Color::ATTR::BLINK;
static constexpr auto& inverse       = Color::ATTR::INVERSE;
static constexpr auto& hidden        = Color::ATTR::HIDDEN;
static constexpr auto& strikethrough = Color::ATTR::STRIKETHROUGH;

// --- Compressed Global Aliases for convenience and efficiency ---
static constexpr auto& r             = reset;
static constexpr auto& b             = bold;
static constexpr auto& i             = italic;
static constexpr auto& u             = underline;
static constexpr auto& s             = strikethrough


#endif

/*
 * =====================================================================================
 *
 *                                     HOW TO USE
 *
 * =====================================================================================
 *
 * 1. INCLUDE THE HEADER
 *    Simply include this file in your C++ source:
 *    #include "colors.h"
 *
 * 2. USE MODIFIERS WITH std::cout
 *    You can stream the color/style modifiers directly to std::cout to change the
 *    appearance of the text that follows.
 *
 *    There are three main ways to access the modifiers, depending on your preference
 *    for verbosity and clarity.
 *
 *
 *    A) Fully-Qualified Access (most explicit)
 *       This is the most verbose method but also the clearest, as it leaves no doubt
 *       about what color or style you are using.
 *
 *       std::cout << Color::FG::Bright::RED << "This is Bright red text." << std::endl;
 *       std::cout << Color::BG::BLUE << "This text has a blue background." << std::endl;
 *       std::cout << Color::Attribute::UNDERLINE << "This is underlined." << std::endl;
 *
 *
 *    B) Namespace-Level Aliases (balanced)
 *       For convenience, common attributes and standard foreground colors are aliased
 *       directly inside the `Color` namespace.
 *
 *       std::cout << Color::RED << "This is standard red text." << std::endl;
 *       std::cout << Color::BOLD << "This text is bold." << std::endl;
 *
 *
 *    C) Global Aliases (most concise)
 *       For maximum convenience and backward compatibility, all common attributes and
 *       standard foreground colors are also aliased in the global scope. This is the
 *       shortest and quickest way to use them.
 *
 *       std::cout << red << "This is standard red text." << std::endl;
 *       std::cout << bold << "This text is bold." << std::endl;
 *
 *
 * 3. COMBINING MODIFIERS
 *    You can combine any number of modifiers. They are applied sequentially.
 *
 *    // Example: Bright yellow text on a blue background, both bold and underlined.
 *    std::cout << Color::FG::Bright::YELLOW << Color::BG::BLUE << bold << underline;
 *    std::cout << "This is a complex style!";
 *
 *
 * 4. IMPORTANT: RESETTING THE STYLE
 *    The terminal style will remain changed until you explicitly reset it. Always
 *    remember to send the `reset` modifier when you are done.
 *
 *    std::cout << red << "This is red." << r << " This is back to default." << std::endl;
 *
 *    You can access the reset modifier in any of the three ways:
 *    - Color::Attribute::RESET
 *    - Color::RESET
 *    - reset
 *    - r
 *
 */