// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <string>

// --- Test Case: Nested Vector Deep Copy ---
// * Verifies that the Vector handles recursive memory management correctly.
// * This tests if copying a Vector of Vectors properly clones all levels.
TEST_CASE("VectorTest, NestedVectorDeepCopy") {
    Vector<Vector<int>> matrix;
    matrix.push_back(Vector<int>({1, 2, 3}));
    matrix.push_back(Vector<int>({4, 5}));
    
    Vector<Vector<int>> copy = matrix;
    
    CHECK(copy.size() == 2);
    CHECK(copy[0].size() == 3);
    CHECK(copy[1][1] == 5);
    
    // ! Modify copy to ensure matrix is unchanged (Deep Copy check)
    copy[0].push_back(99);
    CHECK(copy[0].size() == 4);
    CHECK(matrix[0].size() == 3);
}

// --- Test Case: Triple Nested Vector ---
TEST_CASE("VectorTest, TripleNestedVector") {
    Vector<Vector<Vector<std::string>>> cube;
    Vector<Vector<std::string>> layer;
    layer.push_back(Vector<std::string>({"A", "B"}));
    cube.push_back(layer);
    
    CHECK(cube[0][0][1] == "B");
    cube.clear();
    CHECK(cube.size() == 0);
}

// --- Project Comments ---
// * Tests the depth of the destructor and assignment operator.
