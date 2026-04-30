// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <algorithm>

// --- Test Case: std::nth_element Compatibility ---
// * Requires random access iterators and correct swapping.
TEST_CASE("VectorTest, NthElement") {
    Vector<int> v({5, 2, 1, 4, 3});
    auto mid = v.begin() + 2;
    std::nth_element(v.begin(), mid, v.end());
    CHECK(*mid == 3);
}

// --- Test Case: std::partial_sort Compatibility ---
TEST_CASE("VectorTest, PartialSort") {
    Vector<int> v({5, 4, 3, 2, 1});
    std::partial_sort(v.begin(), v.begin() + 2, v.end());
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
}
