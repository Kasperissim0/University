// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Iterator Invalidation ---
// * This test documents behavior that would normally cause crashes.
// * It verifies that we can "detect" (mentally) where iterators become invalid.
TEST_CASE("VectorTest, IteratorInvalidationScenarios") {
    Vector<int> v({1, 2, 3});
    auto it = v.begin();
    int* originalAddr = &(*it);
    
    // ! This should trigger a resize
    v.reserve(100); 
    
    // ! The iterator 'it' is now technically invalid because 'data' was deleted.
    // ! However, your Iterator class stores a Pointer 'element'.
    // ? Does your Iterator check if the 'container->data' has changed since it was created?
    
    // This check is to see if the address actually changed
    CHECK(&(*v.begin()) != originalAddr);
}

// --- Test Case: Self-Erase Loop ---
TEST_CASE("VectorTest, EraseLoop") {
    Vector<int> v({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    
    // ! Erase all even numbers
    for (auto it = v.begin(); it != v.end(); ) {
        if (*it % 2 == 0) {
            it = v.erase(it); // erase returns next valid iterator
        } else {
            ++it;
        }
    }
    
    CHECK(v.size() == 5);
    CHECK(v[0] == 1);
    CHECK(v[4] == 9);
}
