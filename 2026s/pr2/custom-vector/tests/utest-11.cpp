// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <algorithm>
#include <numeric>
#include <vector.hpp>

// --- Test Case: STL Algorithm Compatibility ---
// * Verifies that the custom Iterator and ConstIterator satisfy 
// * the requirements for standard library algorithms.
TEST_CASE("VectorTest, STLAlgorithmIntegration") {
    Vector<int> v({5, 3, 1, 4, 2});

    // ! Testing std::sort
    // * Requires random access or at least meet the iterator category requirements.
    std::sort(v.begin(), v.end());
    for(st i = 0; i < v.size(); ++i) {
        CHECK(v[i] == static_cast<int>(i + 1));
    }

    // ! Testing std::reverse
    std::reverse(v.begin(), v.end());
    CHECK(v[0] == 5);
    CHECK(v[4] == 1);

    // ! Testing std::accumulate
    int totalSum = std::accumulate(v.begin(), v.end(), 0);
    CHECK(totalSum == 15);

    // ! Testing std::find
    auto itFound = std::find(v.begin(), v.end(), 3);
    CHECK(itFound != v.end());
    CHECK(*itFound == 3);
}

// --- Project Comments ---
// * This test confirms that the `Iterator` class correctly provides the 
// * `iterator_category`, `value_type`, and other necessary traits for STL compatibility.
