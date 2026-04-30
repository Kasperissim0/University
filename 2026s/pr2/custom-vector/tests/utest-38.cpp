// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Insert/Erase Boundary Mix ---
TEST_CASE("VectorTest, InsertEraseMix") {
    Vector<int> v = {1, 2, 3, 4, 5};
    
    // Insert at begin, then erase at end
    v.insert(v.begin(), 0);
    v.pop_back();
    CHECK(v.size() == 5);
    CHECK(v[0] == 0);
    CHECK(v[4] == 4);
    
    // Erase from middle, insert at middle
    v.erase(v.begin() + 2); // Erases '2'
    v.insert(v.begin() + 2, 99);
    CHECK(v[2] == 99);
    CHECK(v[3] == 3);
}
