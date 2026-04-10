// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <iterator>

// --- Test Case: std::reverse_iterator Wrapping ---
// * Verifies if the Iterator can be used with the STL's reverse_iterator wrapper.
TEST_CASE("VectorTest, ReverseIteratorWrapping") {
    Vector<int> v({1, 2, 3, 4, 5});
    std::reverse_iterator<Vector<int>::iterator> rbegin(v.end());
    std::reverse_iterator<Vector<int>::iterator> rend(v.begin());
    
    CHECK(*rbegin == 5);
    CHECK(*(++rbegin) == 4);
    
    int expected = 5;
    for (auto it = rbegin; it != rend; ++it) {
        // ! Since we already incremented rbegin once, it starts at 4
        //? so why does it then check if 4 == 5-- (i think the increment was placed incorrectly)
        // CHECK(*it == expected--); // logic check
        CHECK(*it == --expected); // logic check //* updaetd myself
    }
}

// --- Project Comments ---
// * Requires the iterator to support operator-- and the correct category tags.
