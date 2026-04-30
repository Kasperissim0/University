// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <initializer_list>

// --- Test Case: Initializer List and Capacity ---
// * Testing how the vector handles different sized initializer lists
// * and if it re-uses capacity correctly.
TEST_CASE("VectorTest, InitializerListStress") {
    Vector<int> v = {1, 2, 3};
    CHECK(v.size() == 3);
    
    // ! Assignment from larger list
    v = {10, 20, 30, 40, 50, 60};
    CHECK(v.size() == 6);
    CHECK(v[5] == 60);
    
    // ! Assignment from smaller list
    v = {99};
    CHECK(v.size() == 1);
    CHECK(v[0] == 99);
}

// --- Test Case: Boundary Bracket Access ---
TEST_CASE("VectorTest, BracketBoundary") {
    Vector<int> v(10);
    for(int i=0; i<10; ++i) v.push_back(i);
    
    CHECK_NOTHROW(v[0]);
    CHECK_NOTHROW(v[9]);
    
    // ! These should throw based on your implementation:
    // ! if (index >= savedElements) throw std::runtime_error(...)
    CHECK_THROWS_AS(v[10], std::runtime_error);
    
    const Vector<int> cv = {1, 2};
    CHECK_THROWS_AS(cv[2], std::runtime_error);
}

// --- Project Comments ---
// * Validates the `operator[]` bounds checking logic for both const and non-const vectors.
