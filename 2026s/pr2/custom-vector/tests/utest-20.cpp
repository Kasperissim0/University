// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Iterator Arithmetic Deep Dive ---
// * Tests (it + n), (n + it), (it - n), and (it1 - it2).
TEST_CASE("VectorTest, IteratorArithmetic") {
    Vector<int> v({10, 20, 30, 40, 50});
    auto it = v.begin();
    
    CHECK(*(it + 2) == 30);
    auto it2 = it + 4;
    CHECK(it2 - it == 4);
    CHECK(it - it2 == -4);
    
    it2 -= 2;
    CHECK(*it2 == 30);
}
