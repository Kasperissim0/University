// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <vector>

// --- Test Case: Vector of Booleans ---
// * std::vector<bool> is a specialized container.
// * This test ensures our custom Vector behaves as a standard container of bools.
TEST_CASE("VectorTest, BoolSpecializationCheck") {
    Vector<bool> v({true, false, true});
    CHECK(v.size() == 3);
    
    v.push_back(false);
    CHECK(v[3] == false);
    
    bool* ptr = &v[0]; // std::vector<bool> wouldn't allow this!
    *ptr = false;
    CHECK(v[0] == false);
}

// --- Project Comments ---
// * Our Vector should NOT optimize bools like std::vector does, 
// * allowing direct pointer access to elements.
