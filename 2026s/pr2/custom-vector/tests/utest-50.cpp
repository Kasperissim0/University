// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <algorithm>

// --- Test Case: std::is_sorted / std::is_partitioned ---
TEST_CASE("VectorTest, PredicateAlgorithms") {
    Vector<int> v({1, 2, 3, 4, 5});
    CHECK(std::is_sorted(v.begin(), v.end()) == true);
    
    v[0] = 10;
    CHECK(std::is_sorted(v.begin(), v.end()) == false);
    
    CHECK(std::is_partitioned(v.begin(), v.end(), [](int i){ return i > 5; }) == true);
}
