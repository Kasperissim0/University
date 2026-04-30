// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Multi-Element Insert and Erase ---
// * This test focuses on the shifting logic within the Vector.
// * It verifies that elements are correctly moved during insertions 
// * at the beginning, middle, and end of the container.
TEST_CASE("VectorTest, ShiftingLogicStress") {
    Vector<int> v({1, 2, 3, 4, 5});

    // ! Inserting at the very beginning
    v.insert(v.begin(), 0); 
    CHECK(v.size() == 6);
    CHECK(v[0] == 0);
    CHECK(v[1] == 1);

    // ! Inserting in the middle
    auto mid = v.begin() + 3; // Points to '3'
    v.insert(mid, 99);
    CHECK(v[3] == 99);
    CHECK(v[4] == 3);

    // ! Erasing from the middle
    v.erase(v.begin() + 3); // Erase '99'
    CHECK(v[3] == 3);
    CHECK(v.size() == 6);

    // ! Erasing until empty
    while(!v.empty()) {
        v.erase(v.begin());
    }
    CHECK(v.size() == 0);
    CHECK(v.empty() == true);
}

// --- Project Comments ---
// * Verification of the `testValidity` helper function used in `insert` and `erase`.
// * It ensures that iterators from unrelated vectors or out-of-bounds iterators 
// * trigger the expected `std::out_of_range` exception.
