// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <algorithm>

// --- Test Case: std::min_element / std::max_element ---
TEST_CASE("VectorTest, MinMaxElements") {
    Vector<int> v({40, 10, 50, 20, 30});
    auto minIt = std::min_element(v.begin(), v.end());
    auto maxIt = std::max_element(v.begin(), v.end());
    
    CHECK(*minIt == 10);
    CHECK(*maxIt == 50);
}

// --- Test Case: std::count / std::count_if ---
TEST_CASE("VectorTest, CountAlgorithms") {
    Vector<int> v({1, 2, 2, 3, 4, 2});
    auto count2 = std::count(v.begin(), v.end(), 2);
    auto countEven = std::count_if(v.begin(), v.end(), [](int i){ return i % 2 == 0; });
    
    CHECK(count2 == 3);
    CHECK(countEven == 4);
}
