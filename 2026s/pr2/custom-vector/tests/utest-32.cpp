// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Clear Capacity Persistence ---
// * Verifies that clear() DOES NOT change the capacity.
TEST_CASE("VectorTest, ClearCapacityPersistence") {
    Vector<int> v;
    v.reserve(100);
    st cap = v.capacity();
    
    v.push_back(1);
    v.push_back(2);
    v.clear();
    
    CHECK(v.size() == 0);
    CHECK(v.capacity() == cap);
    
    // ! Ensure we can still push back into that capacity
    v.push_back(99);
    CHECK(v[0] == 99);
}

// --- Project Comments ---
// * This test ensures that clear() doesn't accidentally release the reserved memory.
