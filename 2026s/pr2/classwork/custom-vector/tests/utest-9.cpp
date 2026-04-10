// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <iostream>

// --- Test Case: Iterator Arithmetic and Comparisons ---
// * This test verifies the random-access-like capabilities of the Vector's iterators.
// * While Vector implements a forward_iterator_tag, its Iterator class provides 
// * relational operators and pointer arithmetic which should be verified.
TEST_CASE("VectorTest, IteratorArithmeticAndComparison") {
    Vector<int> v({10, 20, 30, 40, 50});
    auto itStart = v.begin();
    auto itEnd = v.end();

    // ! Checking relational operators
    CHECK(itStart < itEnd);
    CHECK(itEnd > itStart);
    CHECK(itStart <= itStart);
    CHECK(itEnd >= itEnd);

    // ! Checking arithmetic
    auto itMid = itStart + 2;
    CHECK(*itMid == 30);
    CHECK((itMid - 2) == itStart);
    CHECK((itEnd - itStart) == 5);

    // ? Should the iterator be able to decrement from begin()?
    // ? Current implementation check: if (isInRange((element - 1))) --element;
    auto itBegin = v.begin();
    --itBegin; 
    CHECK(itBegin == v.begin()); // Should not move out of range
}

// --- Test Case: Post-Clear and Shrink Stability ---
// ! Warning: Analysis of vector.hpp suggests clear() doesn't reset currentCapacity.
// ! This test case specifically probes for potential segmentation faults.
TEST_CASE("VectorTest, PostClearStability") {
    Vector<int> v({1, 2, 3});
    st originalCapacity = v.capacity();
    
    v.clear();
    CHECK(v.size() == 0);
    // ? Does clear() reset capacity? Implementation suggests it might not.
    // CHECK(v.capacity() == 0); 
    
    // ! Stress test: push_back after clear.
    // ! If currentCapacity remained > 0 but data is nullptr, this will crash.
    v.push_back(100);
    CHECK(v.size() == 1);
    CHECK(v[0] == 100);

    v.shrink_to_fit();
    // ? Does shrink_to_fit on empty vector reset capacity to 0?
    v.clear();
    v.shrink_to_fit();
    // CHECK(v.capacity() == 0);
}

// --- Test Case: Assignment Edge Cases ---
// * Verifying that self-assignment and assignment from empty/cleared vectors 
// * do not cause memory leaks or double-frees.
TEST_CASE("VectorTest, AssignmentRobustness") {
    Vector<int> v1({1, 2, 3, 4, 5});
    
    // ! Self-assignment
    v1 = v1; 
    CHECK(v1.size() == 5);
    CHECK(v1[0] == 1);
    CHECK(v1[4] == 5);

    // ! Assignment from cleared vector
    Vector<int> v2({10, 20});
    v1.clear();
    v2 = v1;
    CHECK(v2.size() == 0);
    CHECK(v2.empty() == true);
    
    // ! Re-filling after assignment
    v2.push_back(99);
    CHECK(v2.size() == 1);
    CHECK(v2[0] == 99);
}

// --- Project Comments ---
// ? Dialectic Question for the User:
// ? In `vector.hpp`, the `clear()` method is implemented as:
// ? `if (data) delete[] data, data = nullptr; return (savedElements = 0, *this);`
// ? However, `currentCapacity` is NOT reset. 
// ? In `push_back`, the check is `if ((savedElements + 1) >= currentCapacity)`.
// ? If I clear a vector of capacity 10, savedElements becomes 0, but currentCapacity remains 10.
// ? The next push_back will see 1 < 10, skip the resize, and try to write to `data[0]`.
// ? But `data` is `nullptr`. Should `clear()` or `push_back` be updated to handle this?
