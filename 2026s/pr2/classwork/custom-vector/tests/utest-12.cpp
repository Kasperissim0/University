// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <string>

// --- Declarations ---
// * A helper struct to track construction and destruction.
struct LifeCycleTracker {
    static int activeInstances;
    LifeCycleTracker() { activeInstances++; }
    LifeCycleTracker(const LifeCycleTracker&) { activeInstances++; }
    ~LifeCycleTracker() { activeInstances--; }
};

int LifeCycleTracker::activeInstances = 0;

// --- Test Case: Custom Object Lifecycle ---
// * Verifies that the Vector correctly manages the lifecycle of its elements.
// * Since Vector uses `new T[]`, it relies on default constructors.
TEST_CASE("VectorTest, ObjectLifecycle") {
    {
        Vector<LifeCycleTracker> v;
        v.reserve(10);
        // ! Note: new T[10] immediately creates 10 instances.
        CHECK(LifeCycleTracker::activeInstances == 10);
        
        v.push_back(LifeCycleTracker());
        // * One more created as temporary, then copied into the array.
    }
    // ! After vector destruction, all instances should be cleared.
    CHECK(LifeCycleTracker::activeInstances == 0);
}

// --- Test Case: String Vector Stress ---
// * Ensuring that complex types with heap allocation (like std::string) 
// * are handled correctly during Vector reallocations.
TEST_CASE("VectorTest, StringVectorStress") {
    Vector<std::string> v;
    for(int i = 0; i < 100; ++i) {
        v.push_back("String number " + std::to_string(i));
    }
    
    CHECK(v.size() == 100);
    CHECK(v[50] == "String number 50");
    
    v.clear();
    CHECK(v.size() == 0);
}

// --- Project Comments ---
// ! Warning: The current Vector implementation uses `new T[size]`.
// ? This means that even if a vector is "empty" but has capacity, 
// ? all `capacity()` elements are default-constructed.
// ? This is different from `std::vector` which uses placement new and raw memory.
