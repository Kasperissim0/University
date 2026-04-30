// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Shrink To Fit Empty ---
TEST_CASE("VectorTest, ShrinkToFitEmpty") {
    Vector<int> v;
    v.reserve(100);
    v.shrink_to_fit();
    
    // CHECK(v.capacity() == 0);
    CHECK(v.size() == 0);
    CHECK(v.begin() == v.end());
}
