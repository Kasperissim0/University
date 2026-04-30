// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Capacity Geometric Growth Check ---
TEST_CASE("VectorTest, GeometricGrowth") {
    Vector<int> v;
    st growthCount = 0;
    st lastCap = 0;
    for(int i=0; i<1000; ++i) {
        v.push_back(i);
        if(v.capacity() > lastCap) {
            growthCount++;
            lastCap = v.capacity();
        }
    }
    // Doubling growth for 1000 elements should be ~10 steps
    CHECK(growthCount <= 15);
}
