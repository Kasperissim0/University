// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <numeric>
#include <vector>

// --- Test Case: std::iota Initialization ---
TEST_CASE("VectorTest, IotaFill") {
    Vector<int> v(10);
    // ! Since resize is private and reserve doesn't zero-init, 
    // ! we must push_back or use the constructor that allocates.
    // ! Assuming the Vector(st, st) constructor zero-initializes or we push.
    for(int i=0; i<10; ++i) v.push_back(0);
    
    std::iota(v.begin(), v.end(), 1);
    CHECK(v[0] == 1);
    CHECK(v[9] == 10);
}
