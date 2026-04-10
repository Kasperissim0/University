// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Declarations ---
struct LargeObject {
    int data[1000];
    int id;
    LargeObject() : id(0) {}
    LargeObject(int i) : id(i) {}
};

// --- Test Case: Memory Fragmentation / Large Objects ---
// * Verifies that the Vector handles large types correctly during reallocations.
TEST_CASE("VectorTest, LargeObjectReallocation") {
    Vector<LargeObject> v;
    for(int i = 0; i < 50; ++i) {
        v.push_back(LargeObject(i));
    }
    
    CHECK(v.size() == 50);
    for(int i = 0; i < 50; ++i) {
        CHECK(v[i].id == i);
    }
}
