// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"

// --- Test Case: Recursive Vector Consistency ---
TEST_CASE("VectorTest, DeeplyNestedOps") {
    Vector<Vector<Vector<int>>> tensor;
    tensor.push_back({{1, 2}, {3, 4}});
    tensor.push_back({{5, 6}});
    
    CHECK(tensor.size() == 2);
    CHECK(tensor[0][1][1] == 4);
    CHECK(tensor[1][0][1] == 6);
    
    tensor.clear();
    CHECK(tensor.empty());
}
