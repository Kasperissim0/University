#include "answer.h"
#include <iostream>

using namespace std;
using os = ostream&;

os     operator<<(os o, const vector<int> &v) {
    for (size_t i = 0, size = v.size(); i < size; ++i)
        o << v.at(i) << " ";
    return o;
}
size_t getAmountOfDigitsFromLargestNumber(const vector<int> &v) {
    size_t digits = 0;
    for (size_t i = 0, size = v.size(), place = 1; i < size; ++i)
        if (v.at(i) / place) ++digits, --i, place *= 10;
    return digits;
}
auto   flattenBuckets(vector<vector<int>> &buckets, vector<int> &target) { target.clear();
    for (const auto &bucket : buckets)
        for (const auto &element : bucket) 
            target.push_back(element);
    // clog << endl << "Array After Flattening: " << target<< endl;
    return target;
}

void radixSort(vector<int> &arr) {
    const size_t         DIGITS_IN_NUMBER_BASE = 10;
    vector<vector<int>>  buckets(DIGITS_IN_NUMBER_BASE, vector<int>());
    vector<int>          sorted = {};

    // clog << "Sorting Array: " << arr << endl;
    for  (size_t digit = 10, currentLoop = 0, totalLoops = getAmountOfDigitsFromLargestNumber(arr); currentLoop < totalLoops; ++currentLoop, digit *= 10) {
        // clog << endl << "Started Iteration #" << (currentLoop + 1) << " of " << totalLoops << endl << endl;
        for (const auto &element : arr) { // clog << endl << "Inspecting: " << elem << endl;
            const size_t sortByDigit = (element % digit) / ((digit == 10) ? 1 : (digit / 10));

            // clog << "Adding To The " << sortByDigit << " Bucket" << endl; 
            buckets.at(sortByDigit).push_back(element);
            // clog << "Bucket After Insertion: " << buckets.at(sortByDigit) << endl;
        } cout << (arr = flattenBuckets(buckets, sorted)) << endl;

        for (auto &b : buckets)  b.clear();
                                 sorted.clear(); 
        // clog << endl << "Finished Iteration #" << (currentLoop + 1) << " of " << totalLoops << endl;
    }
}