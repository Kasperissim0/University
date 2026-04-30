// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <string>

// --- Test Case: Self Assignment Complex ---
TEST_CASE("VectorTest, SelfAssignmentComplex") {
    Vector<std::string> v({"Hello", "World", "Test"});
    v = v;
    
    CHECK(v.size() == 3);
    CHECK(v[0] == "Hello");
    CHECK(v[2] == "Test");
}
