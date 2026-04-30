// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Growth Amortization ---
// * Verifies that the vector doesn't reallocate on every single push_back.
TEST_CASE("VectorTest, GrowthAmortization") {
    Vector<int> v;
    v.push_back(1);
    st initialCap = v.capacity();
    
    int reallocs = 0;
    for(int i = 0; i < 100; ++i) {
        st oldCap = v.capacity();
        v.push_back(i);
        if (v.capacity() > oldCap) reallocs++;
    }
    
    // ! For 100 elements, doubling growth should happen ~7 times.
    CHECK(reallocs < 10);
}
