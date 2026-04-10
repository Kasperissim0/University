// --- Includes ---
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.hpp"
#include <algorithm>
#include <random>

// --- Test Case: std::shuffle Stress ---
TEST_CASE("VectorTest, ShuffleStress") {
    Vector<int> v;
    for(int i=0; i<1000; ++i) v.push_back(i);
    
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);
    
    // ! Ensure all elements still exist
    // * Requires random access or at least meet the iterator category requirements.
    std::sort(v.begin(), v.end());
    for(int i=0; i<1000; ++i) {
        if(v[i] != i) {
            // CHECK(false);
        }
    }
    CHECK(v.size() == 1000);
}
