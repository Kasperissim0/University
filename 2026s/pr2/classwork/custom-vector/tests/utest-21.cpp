// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Pop Back Empty Protection ---
TEST_CASE("VectorTest, PopBackEmpty") {
    Vector<int> v;
    // ! Should throw runtime_error as per your code
    CHECK_THROWS_AS(v.pop_back(), std::runtime_error);
    
    v.push_back(1);
    v.pop_back();
    CHECK_THROWS_AS(v.pop_back(), std::runtime_error);
}
