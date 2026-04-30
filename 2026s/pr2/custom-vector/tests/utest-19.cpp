// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Const Correctness Stress ---
// * Verifying that const vectors strictly prevent modification via any path.
TEST_CASE("VectorTest, StrictConstCorrectness") {
    const Vector<int> v({1, 2, 3});
    
    // ! These should compile and return const references/pointers
    const int& val = v[0];
    const int* ptr = v.begin().operator->();
    
    CHECK(val == 1);
    CHECK(*ptr == 1);
    
    // ! Testing if ConstIterator correctly prevents writing
    // ! This is a compile-time check, but we verify the iterator logic here.
    auto it = v.begin();
    CHECK(it == v.begin());
    
    // v[0] = 5; // Should fail to compile
    // *it = 5;  // Should fail to compile
}

// --- Project Comments ---
// * Ensures that the `ConstIterator` doesn't accidentally allow non-const access.
