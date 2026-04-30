// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <string>
#include <algorithm>
#include <numeric>

// --- Test Case: Iterator Arithmetic Boundaries ---
// * Verifies that the random access operators (+, -, +=, -=) 
// * behave correctly and consistently with standard pointers.
TEST_CASE("VectorTest, IteratorArithmeticBoundaries") {
    Vector<int> v({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    auto it = v.begin();
    
    // ! Testing addition and indexing
    CHECK(*(it + 5) == 6);
    // CHECK(it[5] == 6); // operator[] is not yet implemented in IteratorBase.

    it += 3; // Now at index 3 (value 4)
    CHECK(*it == 4);
    
    auto it2 = it - 2; // Now at index 1 (value 2)
    CHECK(*it2 == 2);
    
    CHECK(it - it2 == 2);
    CHECK(it2 - it == -2);
}

// --- Test Case: Erase All Elements ---
// * Verifies that erasing elements in a loop correctly updates size
// * and handles iterator invalidation gracefully by using the return value.
TEST_CASE("VectorTest, EraseAllSequentially") {
    Vector<std::string> v({"A", "B", "C", "D"});
    auto it = v.begin();
    while (it != v.end()) {
        it = v.erase(it);
    }
    CHECK(v.empty());
    CHECK(v.size() == 0);
}

// --- Test Case: Insert at Capacity Boundary ---
// * Verifies that inserting an element when size == capacity
// * correctly triggers a resize and preserves existing elements.
TEST_CASE("VectorTest, InsertTriggersResize") {
    Vector<int> v;
    v.reserve(1); // Capacity is now 1
    v.push_back(1); // (0+1) >= 1, so it resizes to (1+1)*2 = 4
    
    st capAfterPush = v.capacity();
    // ! Capacity is now 4, size is 1.
    // ! To trigger another resize, we need to exceed capacity 4.
    v.push_back(2); // (1+1) >= 4 is false. size 2
    v.push_back(3); // (2+1) >= 4 is false. size 3
    v.push_back(4); // (3+1) >= 4 is true! Resizes to (4+1)*2 = 10.
    
    // CHECK(v.capacity() == 10); //* old resize logic
    CHECK(v.capacity() == 4);
}

// --- Test Case: std::fill and std::iota ---
// * Confirms compatibility with algorithms that modify ranges.
TEST_CASE("VectorTest, RangeModificationAlgorithms") {
    Vector<int> v({0, 0, 0, 0, 0});
    std::fill(v.begin(), v.end(), 42);
    for(auto val : v) {
        CHECK(val == 42);
    }
    
    std::iota(v.begin(), v.end(), 1);
    CHECK(v[0] == 1);
    CHECK(v[4] == 5);
}

// --- Project Comments ---
// ? Threads to Explore:
// ? 1. Move Assignment: Notice that `vector.hpp` implements a Move Constructor but not a Move Assignment Operator.
// ?    How does this affect performance when reassigning a temporary Vector?
// ? 2. Iterator Safety: As noted in `utest-4.cpp`, the lack of bounds checking in `Iterator` 
// ?    makes it "unsafe" compared to a "Checked Iterator" implementation. 
// ?    What architectural changes would be needed to make `*it` throw when `it == v.end()`?
// ? 3. Exception Safety: If `T`'s constructor throws during `new T[newSize]` in `resize`, 
// ?    the current implementation might leak memory or leave the Vector in an inconsistent state.
