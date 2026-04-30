// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Large static_castale Stress Test ---
// * Pushing 100,000 elements to test the geometric expansion (resize) logic.
// * Verifies that the capacity grows correctly and performance is reasonable.
TEST_CASE("VectorTest, Largestatic_castaleStress") {
    Vector<long> v;
    const st limit = 100000;
    
    for(st i = 0; i < limit; ++i) {
        v.push_back(static_cast<long>(i));
    }
    
    CHECK(v.size() == limit);
    CHECK(v[limit - 1] == 99999);
    
    // ! Checking if capacity is at least the size
    CHECK(v.capacity() >= limit);
    
    // ! Testing sequential access speed indirectly
    long sum = 0;
    for(auto it = v.begin(); it != v.end(); ++it) {
        sum += *it;
    }
    // Sum of first n numbers: n*(n-1)/2
    CHECK(sum == (static_cast<long>(limit) * (limit - 1) / 2));
}

// --- Project Comments ---
// * This test ensures that the `resize((savedElements + 1) * 2)` logic 
// * doesn't cause excessive reallocations or memory fragmentation.
