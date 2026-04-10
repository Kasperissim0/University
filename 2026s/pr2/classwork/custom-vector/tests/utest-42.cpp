// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <algorithm>

// --- Test Case: std::unique Compatibility ---
TEST_CASE("VectorTest, UniqueAlgorithm") {
    Vector<int> v({1, 1, 2, 2, 2, 3, 3, 1});
    auto it = std::unique(v.begin(), v.end());
    // ! unique moves duplicates to the end but doesn't change size
    // ! v should now start with 1, 2, 3, 1
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
    CHECK(v[2] == 3);
    CHECK(v[3] == 1);
}
