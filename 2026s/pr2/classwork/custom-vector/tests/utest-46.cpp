// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Cross-Instance Iterator Comparison ---
TEST_CASE("VectorTest, CrossInstanceComparison") {
    Vector<int> v1({1, 2, 3});
    Vector<int> v2({1, 2, 3});
    
    // ! Comparing iterators from different containers
    // ! Standard says this is undefined, but your impl stores container pointer.
    CHECK(!(v1.begin() == v2.begin()));
    CHECK(v1.begin() != v2.begin());
}
