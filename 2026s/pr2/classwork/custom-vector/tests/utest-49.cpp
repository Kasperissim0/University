// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <algorithm>

// --- Test Case: std::rotate Compatibility ---
TEST_CASE("VectorTest, RotateAlgorithm") {
    Vector<int> v({1, 2, 3, 4, 5});
    std::rotate(v.begin(), v.begin() + 2, v.end());
    // Should be: 3, 4, 5, 1, 2
    CHECK(v[0] == 3);
    CHECK(v[4] == 2);
}
