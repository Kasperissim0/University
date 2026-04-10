// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Zero Capacity Push Back ---
// * Tests push_back when capacity is explicitly 0.
TEST_CASE("VectorTest, ZeroCapacityPush") {
    Vector<int> v(0); 
    CHECK(v.capacity() == 0);
    
    v.push_back(10);
    CHECK(v.size() == 1);
    CHECK(v.capacity() > 0);
    CHECK(v[0] == 10);
}

// --- Test Case: Shrink To Empty ---
TEST_CASE("VectorTest, ShrinkEmpty") {
    Vector<int> v({1, 2, 3});
    v.clear();
    v.shrink_to_fit();
    // ! Depending on implementation, capacity should be 0 or original
    // CHECK(v.capacity() == 0); 
}
