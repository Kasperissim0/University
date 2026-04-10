// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <numeric>

// --- Test Case: std::inner_product Compatibility ---
TEST_CASE("VectorTest, InnerProduct") {
    Vector<int> v1({1, 2, 3});
    Vector<int> v2({4, 5, 6});
    int result = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0);
    // (1*4) + (2*5) + (3*6) = 4 + 10 + 18 = 32
    CHECK(result == 32);
}

// --- Test Case: std::adjacent_difference ---
TEST_CASE("VectorTest, AdjacentDifference") {
    Vector<int> v({1, 3, 6, 10});
    // Vector<int> res(4); //! does not work, unitialized values begin() == end() + crash
    Vector<int> res({0, 0, 0, 0});
    // res needs to be pre-sized or use back_inserter. 
    // Since resize is private, we must push_back or use pre-allocated.
    std::adjacent_difference(v.begin(), v.end(), res.begin());
    CHECK(res[1] == 2);
    CHECK(res[3] == 4);
}
