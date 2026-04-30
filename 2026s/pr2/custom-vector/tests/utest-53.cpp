// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Declarations ---
struct Counter {
    static int instances;
    Counter() { instances++; }
    Counter(const Counter&) { instances++; }
    Counter& operator=(const Counter&) { return *this; }
    ~Counter() { instances--; }
};
int Counter::instances = 0;

// --- Test Case: Reserve and Shrink Destruction ---
// * Verifies if objects are destroyed when the vector resizes to a smaller size
// * or is completely destroyed.
TEST_CASE("VectorTest, ReserveAndShrinkDestruction") {
    {
        Vector<Counter> v;
        v.reserve(10);
        CHECK(Counter::instances == 10);
        
        // ! Resizing smaller should destroy the extra objects
        // ! but currently resize() uses new T[newSize] and delete[] oldData
        v.reserve(5); 
        // ? If resize works, old 10 were deleted, new 5 were created.
        // ? So count should be 5.
    }
    CHECK(Counter::instances == 0);
}

// --- Test Case: Self Assignment Destruction ---
TEST_CASE("VectorTest, SelfAssignmentDestruction") {
    Counter::instances = 0;
    {
        Vector<Counter> v;
        v.reserve(5);
        v = v; // Should not destroy and recreate objects
        CHECK(Counter::instances == 5);
    }
    CHECK(Counter::instances == 0);
}

// --- Project Comments ---
// * This test demonstrates that your Vector relies on the runtime's 
// * array-delete (delete[]) to manage lifetimes, rather than manual 
// * destruction of individual elements.
