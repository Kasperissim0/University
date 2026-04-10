// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Iterator Relational Operators ---
// * Deeply testing <, >, <=, >= between iterators.
TEST_CASE("VectorTest, IteratorComparisonDeep") {
    Vector<int> v({1, 2, 3, 4, 5});
    auto it1 = v.begin();
    auto it3 = v.begin() + 2;
    auto it5 = v.end();
    
    CHECK(it1 < it3);
    CHECK(it3 < it5);
    CHECK(it5 > it1);
    CHECK(it3 <= it3);
    CHECK(it3 >= it3);
    
    // ! Boundary checks
    CHECK(!(it5 < it1));
    CHECK(!(it1 > it5));
}
