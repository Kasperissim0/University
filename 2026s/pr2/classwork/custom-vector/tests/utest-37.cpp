// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Large Reallocations with Strings ---
TEST_CASE("VectorTest, StringReallocStress") {
    Vector<std::string> v;
    // ! Forcing many reallocations
    for(int i=0; i<500; ++i) {
        v.push_back("A very long string that definitely allocates on the heap to test memory management during resize " + std::to_string(i));
    }
    
    CHECK(v.size() == 500);
    CHECK(v[499].find("499") != std::string::npos);
}
