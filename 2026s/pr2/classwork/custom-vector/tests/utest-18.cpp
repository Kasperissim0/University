// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <utility>

// --- Test Case: Move Semantics Verification ---
// * Even if not explicitly implemented, Vector should handle std::move 
// * by falling back to the copy constructor.
TEST_CASE("VectorTest, MoveFallback") {
    Vector<int> v1({1, 2, 3});
    Vector<int> v2 = std::move(v1);
    
    CHECK(v2.size() == 3);
    CHECK(v2[0] == 1);
    // ! Note: In a true move, v1 would be empty. 
    // ! Currently, v1 is still a full copy.
}
