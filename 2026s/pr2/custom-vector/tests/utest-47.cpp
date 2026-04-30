// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Destructor Stress ---
TEST_CASE("VectorTest, DestructorLeakCheck") {
    for(int i=0; i<100; ++i) {
        Vector<int> temp;
        for(int j=0; j<100; ++j) temp.push_back(j);
        // temp goes out of scope here
    }
    // ! This test is for manual run with Valgrind/ASan
    CHECK(true);
}
