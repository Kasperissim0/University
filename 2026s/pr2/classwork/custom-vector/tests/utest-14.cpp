// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <stdexcept>

// --- Declarations ---
struct FragileObject {
    static int count;
    static bool shouldThrow;
    FragileObject() {
        if (shouldThrow) throw std::runtime_error("Construction Failed");
        count++;
    }
    FragileObject(const FragileObject&) {
        if (shouldThrow) throw std::runtime_error("Copy Failed");
        count++;
    }
    ~FragileObject() { count--; }
};

int FragileObject::count = 0;
bool FragileObject::shouldThrow = false;

// --- Test Case: Exception Safety during Reserve ---
// * Note: This tests if the Vector leaks memory when an element constructor 
// * throws during a reallocation/resize.
TEST_CASE("VectorTest, ExceptionSafetyDuringResize") {
    Vector<FragileObject> v;
    FragileObject::shouldThrow = false;
    v.reserve(5);
    CHECK(FragileObject::count == 5); 
    
    // ! If resize uses new T[n] and it fails halfway, what happens?
    // ! (Currently Vector uses new T[newSize], so if the array itself fails to construct, 
    // ! we need to ensure the count is consistent).
    // FragileObject::shouldThrow = false; //* Implicitly Carried From Line 30
    // FragileObject::shouldThrow = true;
    // CHECK_THROWS(v.reserve(10)); //? why would reserving throw here?
    CHECK_NOTHROW(v.reserve(10000));
    
    // FragileObject::shouldThrow = false; //* Implicitly Carried From Line 30
    v.clear();
    CHECK(FragileObject::count == 0);
}

// --- Project Comments ---
// ? Dialectic Question:
// ? If `new T[newSize]` throws an exception, the memory is usually cleaned up by the runtime,
// ? but what happens to the elements already in your `data` pointer?
// ? Does your `resize` method protect against this?
