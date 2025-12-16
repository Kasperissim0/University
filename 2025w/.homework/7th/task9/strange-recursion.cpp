#include <iostream>

// Primary recursive function
template<unsigned n>
struct Factorial {
    static const unsigned value = n * Factorial<n - 1>::value; // Recursive case
};

// Base case specialization for Factorial<0>
template<>
struct Factorial<0> {
    static const unsigned value = 1; // Base case
};

int main() {
    constexpr unsigned number = 13; // Example input
    constexpr unsigned result = Factorial<number>::value; // Calculate factorial at compile-time
    std::cout << number << "! == " << result << std::endl;
    return 0;
}