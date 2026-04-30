// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <algorithm>

// --- Test Case: std::binary_search on Vector ---
TEST_CASE("VectorTest, BinarySearch") {
    Vector<int> v({10, 20, 30, 40, 50});
    CHECK(std::binary_search(v.begin(), v.end(), 30) == true);
    CHECK(std::binary_search(v.begin(), v.end(), 35) == false);
}

// --- Test Case: std::lower_bound / std::upper_bound ---
TEST_CASE("VectorTest, BoundsSearching") {
    Vector<int> v({10, 20, 30, 30, 40, 50});
    auto it = std::lower_bound(v.begin(), v.end(), 30);
    CHECK(std::distance(v.begin(), it) == 2);
    
    auto it2 = std::upper_bound(v.begin(), v.end(), 30);
    CHECK(std::distance(v.begin(), it2) == 4);
}
