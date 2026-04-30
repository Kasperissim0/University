// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Insert After Clear ---
// * Verifies if inserting into a cleared vector works correctly.
// * This tests if the internal state (savedElements, currentCapacity, data) 
// * remains consistent after a clear operation.
TEST_CASE("VectorTest, InsertAfterClear") {
    Vector<int> v({1, 2, 3});
    v.clear();
    
    // ! Inserting at the new begin() (which should be index 0)
    v.insert(v.begin(), 100);
    
    CHECK(v.size() == 1);
    CHECK(v[0] == 100);
}

// --- Test Case: Multiple Clears and Resizes ---
TEST_CASE("VectorTest, MultipleClearResizeCycle") {
    Vector<int> v;
    for(int i=0; i<10; ++i) v.push_back(i);
    v.clear();
    for(int i=0; i<10; ++i) v.push_back(i + 10);
    v.shrink_to_fit();
    
    CHECK(v.size() == 10);
    CHECK(v[0] == 10);
    CHECK(v.capacity() == 10);
}

// --- Test Case: Iterator Value Persistence ---
// * Verifies that the value pointed to by an iterator 
// * can be modified and correctly reflected in the vector.
TEST_CASE("VectorTest, IteratorValueModification") {
    Vector<int> v({10, 20, 30});
    auto it = v.begin() + 1;
    *it = 99;
    CHECK(v[1] == 99);
}

// --- Project Comments ---
// ? Socratic Question:
// ? In `insert`, you call `testValidity((position - this->begin()), (savedElements + 1))`.
// ? If the vector was just `clear()`-ed, `this->begin()` returns `data`. 
// ? If `data` is NOT nullptr after clear, `position - begin()` is 0.
// ? If `data` WAS nullptr after clear, `v.begin()` returns `nullptr`.
// ? Passing a default-constructed iterator (value=nullptr) to `insert` would result in `nullptr - nullptr = 0`.
// ? Does your implementation correctly handle the case where `data` is null?
