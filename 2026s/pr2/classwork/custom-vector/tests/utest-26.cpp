// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <algorithm>

// --- Test Case: Iterator Swap Compatibility ---
// * Verifies if the Iterator works with std::iter_swap.
// * This is a requirement for many sorting and partitioning algorithms.
TEST_CASE("VectorTest, IteratorSwap") {
    Vector<int> v({1, 2, 3});
    auto it1 = v.begin();
    auto it2 = v.begin() + 2;
    
    std::iter_swap(it1, it2);
    
    CHECK(v[0] == 3);
    CHECK(v[2] == 1);
}

// --- Project Comments ---
// * If this fails to compile, it's because Iterator::reference is not 
// * a true reference or the iterator doesn't satisfy the Swappable requirement.
