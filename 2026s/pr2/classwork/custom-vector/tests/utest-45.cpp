// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <string>

// --- Test Case: Large String Vector Stability ---
TEST_CASE("VectorTest, StringVectorStress") {
    Vector<std::string> v;
    for(int i=0; i<1000; ++i) {
        v.push_back("String_" + std::to_string(i));
    }
    
    v.erase(v.begin() + 500);
    CHECK(v[500] == "String_501");
    CHECK(v.size() == 999);
}
