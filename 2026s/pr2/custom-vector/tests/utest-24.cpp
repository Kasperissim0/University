// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Clear Capacity Persistence ---
// * Verifies that clearing the vector doesn't lose the reserved capacity.
TEST_CASE("VectorTest, ClearCapacityPersistence") {
    Vector<int> v;
    v.reserve(50);
    v.push_back(1);
    v.clear();
    
    CHECK(v.size() == 0);
    // ! If clear() deletes memory, this might fail or be inefficient
    CHECK(v.capacity() == 50);
}
