// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Multiple Iterators Co-existing ---
TEST_CASE("VectorTest, CoexistingIterators") {
    Vector<int> v = {1, 2, 3, 4, 5};
    auto it1 = v.begin();
    auto it2 = v.begin() + 2;
    auto it3 = v.end();
    
    CHECK(*it1 == 1);
    CHECK(*it2 == 3);
    CHECK(it1 < it2);
    CHECK(it2 < it3);
    
    // ! Modify via one, check via other
    *it1 = 10;
    CHECK(v[0] == 10);
}
