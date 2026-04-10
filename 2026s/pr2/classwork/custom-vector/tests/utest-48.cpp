// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Reverse Iterator Arithmetics ---
TEST_CASE("VectorTest, ReverseArithmetics") {
    Vector<int> v({1, 2, 3, 4, 5});
    std::reverse_iterator<Vector<int>::iterator> rit(v.end());
    
    auto rit2 = rit + 2;
    CHECK(*rit2 == 3);
    CHECK(rit2 - rit == 2);
}
