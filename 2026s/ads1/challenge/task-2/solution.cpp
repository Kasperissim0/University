//§ Requisities
  //§ Includes
    #include <cstddef>
    #include <iostream>
    #include <fstream>
    #include <filesystem>
    #include <string>
    #include "random.hpp"
  //.
  //§ Aliases
    using namespace std;
    namespace fs = filesystem;
    using st = size_t;
  //.
  //§ Functions
    // Θ(n^2) naive implementation
    int maxSubarray_Naive(const int arr[], const st amountOfElements) {
      
    }
    // Θ(n log n) divide and conquer
    int maxSubarray_DNC(const int arr[], const int *start, const int *end) {
      
    }
    // Θ(n) recursive (top-down style)
    int maxSubarray_Recursive(const int arr[], const st amountOfElements) {
      
    }
    // Θ(n) memoized / bottom-up
    int maxSubarray_DP(const int arr[], const st amountOfElements) {
    
  }
  //.
//.
int sumOfElementsOfLargestSubarray(const int arr[], const st amountOfElements) {
    const st n = gen.generate<st>(0, 3);
    switch (n) {
      case 0:
        return maxSubarray_Naive(arr, amountOfElements);
      case 1:
        return maxSubarray_DNC(arr, arr, (arr + amountOfElements));
      case 2:
        return maxSubarray_Recursive(arr, amountOfElements);
      case 3:
        return maxSubarray_DP(arr, amountOfElements);
      default:
        throw runtime_error(("Invalid Random Number Generated: " + to_string(n)));
    }
  }
int main() { // output: 
  ifstream dataSource(fs::path("/Users/kasperissim0/Code/Archive/University/2026s/ads1/challenge/task-2/input.txt")); 
  st amountOfArrays; dataSource >> amountOfArrays; // if this is meant to be tested, then the path for the input file (obviously) needs to be changed 
                                                   // i couldn't get it to work with relative paths for some reason
  for (st currentArrayIndex = 0; currentArrayIndex < amountOfArrays; ++currentArrayIndex) {
    st size; dataSource >> size; int *currentArray = new int[size];

    for (st i = 0; i < size; ++i) 
      dataSource >> currentArray[i];

    cout << sumOfElementsOfLargestSubarray(currentArray, size);
    delete[] currentArray;
  } cout << endl;
  dataSource.close();
  return 0;
}