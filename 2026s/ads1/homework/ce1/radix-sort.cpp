#include "answer.h"
#include <iostream>

using namespace std;
// using os = ostream&;

// os     operator<<(os o, const vector<int> &v) {
//     for (size_t i = 0, size = v.size(); i < size; ++i)
//         o << v.at(i) << " ";
//     return o;
// }
// size_t getAmountOfDigitsFromLargestNumber(const vector<int> &v) {
//     size_t digits = 0;
//     for (size_t i = 0, size = v.size(), place = 1; i < size; ++i)
//         if (v.at(i) / place) ++digits, --i, place *= 10;
//     return digits;
// }
// auto   flattenBuckets(vector<vector<int>> &buckets, vector<int> &target) { target.clear();
//     for (const auto &bucket : buckets)
//         for (const auto &element : bucket) 
//             target.push_back(element);
//     // clog << endl << "Array After Flattening: " << target<< endl;
//     return target;
// }

void radixSort(vector<int> &arr) {
    // const size_t         DIGITS_IN_NUMBER_BASE = 10;
    // vector<vector<int>>  buckets(DIGITS_IN_NUMBER_BASE, vector<int>());
    // vector<int>          sorted = {};

    // // clog << "Sorting Array: " << arr << endl;
    // for  (size_t digit = 10, currentLoop = 0, totalLoops = getAmountOfDigitsFromLargestNumber(arr); currentLoop < totalLoops; ++currentLoop, digit *= 10) {
    //     // clog << endl << "Started Iteration #" << (currentLoop + 1) << " of " << totalLoops << endl << endl;
    //     for (const auto &element : arr) { // clog << endl << "Inspecting: " << elem << endl;
    //         const size_t sortByDigit = (element % digit) / ((digit == 10) ? 1 : (digit / 10));

    //         // clog << "Adding To The " << sortByDigit << " Bucket" << endl; 
    //         buckets.at(sortByDigit).push_back(element);
    //         // clog << "Bucket After Insertion: " << buckets.at(sortByDigit) << endl;
    //     } cout << (arr = flattenBuckets(buckets, sorted)) << endl;

    //     for (auto &b : buckets)  b.clear();
    //                              sorted.clear(); 
    //     // clog << endl << "Finished Iteration #" << (currentLoop + 1) << " of " << totalLoops << endl;
    // }
    // const size_t DIGITS_IN_NUMBER_BASE = 10,
    //              totalLoops = [&] {
    //                 size_t digits = 0;
    //                 for (size_t i = 0, size = arr.size(), place = 1; i < size; ++i)
    //                     if (arr.at(i) / place) ++digits, --i, place *= 10;
    //                 return digits;
    //               }();
    // vector<vector<int>>  buckets(DIGITS_IN_NUMBER_BASE, vector<int>());
    // vector<int>          sorted = {};

    // for (size_t digit = 10, currentLoop = 0; currentLoop < totalLoops; ++currentLoop, digit *= 10) {
    //     for (const auto &element : arr)
    //         buckets.at(((element % digit) / ((digit == 10) ? 1 : (digit / 10)))).push_back(element);
    //     cout << (arr = [&] {
    //                 sorted.clear(); 
    //                 for (const auto &b : buckets) 
    //                     for (const auto &e : b) 
    //                         sorted.push_back(e); 
    //                 return sorted;
    //                 }()) << endl;
    //     sorted.clear();  for (auto &b : buckets)  b.clear();
    // }

    const size_t DIGITS_IN_NUMBER_BASE = 10,
                 totalLoops = [&] {
                    size_t digits = 0;
                    for (size_t i = 0, size = arr.size(), place = 1; i < size; ++i)
                        if (arr.at(i) / place) ++digits, --i, place *= 10;
                    return digits;
                  }();
    vector<vector<int>>  buckets(DIGITS_IN_NUMBER_BASE, vector<int>());
    vector<int>          sorted = {};

    for (size_t digit = 10, currentLoop = 0; currentLoop < totalLoops; ++currentLoop, digit *= 10) {
        for (const auto &element : arr)
            buckets.at(((element % digit) / ((digit == 10) ? 1 : (digit / 10)))).push_back(element);
    arr = [&] {
        sorted.clear(); 
        for (const auto &b : buckets) 
            for (const auto &e : b) 
                sorted.push_back(e); 
        return sorted;
    }();
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i) cout << ' ';
        cout << arr[i];
    } cout << '\n';
        sorted.clear();  for (auto &b : buckets)  b.clear();
}

// i had a few helper functions in my file, but since i must paste only the contents of the function i had to turn them into lambdas here
// nevertheless, i apologize for the lack of readability

// that being said doing this compression did improve the execution time (from 1.09955 to 1.04849 seconds)


    // i had a few helper functions in my file, but since i must paste only the contents of the function i had to turn them into lambdas here
    // nevertheless, i apologize for the lack of readability

    // that being said doing this compression did improve the execution time (from 1.09955 to 1.04849 seconds)
}