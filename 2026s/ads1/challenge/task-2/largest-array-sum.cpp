//§ Requisities
  //§ Includes
    #include <algorithm>
    #include <cstddef>
    #include <iostream>
    #include <fstream>
    #include <filesystem>
    #include <string>
    #include <limits>
    #if __has_include("random.hpp")
      #include "random.hpp"
    #else
      #include <random>
      #include <type_traits>

    class StandardRandomFallback {
    private:
        std::mt19937 engine;

    public:
        StandardRandomFallback() {
            std::random_device rd;
            engine.seed(rd());
        }
        template <typename T>
        T generate(T min, T max) {
            if constexpr (std::is_integral_v<T>) {
                std::uniform_int_distribution<T> dist(min, max);
                return dist(engine);
            } else if constexpr (std::is_floating_point_v<T>) {
                std::uniform_real_distribution<T> dist(min, max);
                return dist(engine);
            } else {
                static_assert(std::is_arithmetic_v<T>, "Type must be numeric");
                return 0;
            }
        }
    };
    StandardRandomFallback gen;
    #endif
    // //! Checking
    // #include <sstream>
    // #include <chrono>
    // #include <tuple>
    // #include <vector>
    // #include <functional>
    using ll = long long;
    inline ll timePassedSince(const auto startTime) {
      return (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startTime).count());
    }
  //.
  //§ Aliases
    using namespace std;
    namespace fs = filesystem;
    using st = size_t;
  //.
  //§ Functions
    int solve(const int* start, const int* end) { if (end - start == 1) return *start;
      const int *mid = start + (end - start) / 2, 
                leftMax = solve(start, mid), 
                rightMax = solve(mid, end);
      int       leftCross = numeric_limits<int>::min(), 
                rightCross = numeric_limits<int>::min(),
                current = 0;

      for (const int *p = (mid - 1); p >= start; --p) {
        current += *p;
        leftCross = max(leftCross, current);
      }
      current = 0;
      for (const int *p = mid; p < end; ++p) {
        current += *p;
        rightCross = max(rightCross, current);
      }

      return max({leftMax, rightMax, (leftCross + rightCross)});
    }
    tuple<int, int> solve(const int arr[], const st index) { if (index == 0) return {arr[0], arr[0]};
      const auto [previousEnd, globalEnd] = solve(arr, (index - 1));
      const int currentEnd = max(previousEnd + arr[index], arr[index]),
                globalBest = max(globalEnd, currentEnd);

      return {currentEnd, globalBest};
    }

    tuple<int, ll> naive(const int arr[], const st amountOfElements) { // Θ(n^2) naive implementation
      auto startTime = chrono::high_resolution_clock::now();
      int currentSum = 0, bestSum = 0;

      for (st start = 0; start < amountOfElements; ++start) {
        for (st end = start; end < amountOfElements; ++end) {
          currentSum += arr[end];
          bestSum = std::max(currentSum, bestSum);
        }
        currentSum = 0;
      }
      return {bestSum, timePassedSince(startTime)};
    }
    tuple<int, ll> divideAndConquer(const int arr[], const st amountOfElements) { // Θ(n log n) divide and conquer
      auto startTime = chrono::high_resolution_clock::now();
      const int *start = arr, *end = arr + amountOfElements;
      int bestSum = 0;

      if (start < end) bestSum = solve(start, end);

      return {bestSum, timePassedSince(startTime)};
    }
    tuple<int, ll> recursive(const int arr[], const st amountOfElements) { // Θ(n) recursive (top-down style)
      auto startTime = chrono::high_resolution_clock::now();
      int bestSum = 0;

      if (amountOfElements) bestSum = get<1>(solve(arr, (amountOfElements - 1)));

      return {bestSum, timePassedSince(startTime)};
    }
    tuple<int, ll> iterative(const int arr[], const st amountOfElements) { // Θ(n) memoized / bottom-up (a.k.a Kadane’s Algorithm)
      auto startTime = chrono::high_resolution_clock::now();
      int currentSum = 0, bestSum = 0;
      if (amountOfElements) {
       currentSum = bestSum = arr[0];

        for (st i = 1; i < amountOfElements; ++i) {
          currentSum = max(currentSum + arr[i], arr[i]);
          bestSum    = max(bestSum, currentSum); 
        }
      }
      return {bestSum, timePassedSince(startTime)};
    }
  //.
//.
// constexpr bool ADD_SPACE = true; //! Checking

auto sumOfElementsOfLargestSubarray(const int arr[], const st amountOfElements) {
    const st n = gen.generate<st>(0, 3);
    switch (n) {
      case 0: return naive(arr, amountOfElements);
      case 1: return divideAndConquer(arr, amountOfElements);
      case 2: return recursive(arr, amountOfElements);
      case 3: return iterative(arr, amountOfElements);
      default: throw runtime_error(("Invalid Random Number Generated: " + to_string(n)));
    }
  }
int main() { // output: 18934115471464326577337363707926913547101583119871
  // //! Checking
  // stringstream a1, a2, a3, a4; ll d1 = 0, d2 = 0, d3 = 0, d4 = 0;

  ifstream dataSource(fs::path("/Users/kasperissim0/Code/Archive/University/2026s/ads1/challenge/task-2/input.txt")); 
  st amountOfArrays; dataSource >> amountOfArrays; // if this is meant to be tested, then the path for the input file (obviously) needs to be changed 
                                                   // i couldn't get it to work with relative paths for some reason
  for (st currentArrayIndex = 0; currentArrayIndex < amountOfArrays; ++currentArrayIndex) {
    st size; dataSource >> size; int *currentArray = new int[size];

    for (st i = 0; i < size; ++i) 
      dataSource >> currentArray[i];

    // //! Checking
    // // auto [result, time] = naive(currentArray, size);
    // auto result = naive(currentArray, size);
    // d1 += get<1>(result);
    // a1 << get<0>(result) << (ADD_SPACE ? " " : "");
    // result = divideAndConquer(currentArray, size);
    // d2 += get<1>(result);
    // a2 << get<0>(result) << (ADD_SPACE ? " " : "");
    // result = recursive(currentArray, size);
    // d3 += get<1>(result);
    // a3 << get<0>(result) << (ADD_SPACE ? " " : "");
    // result = iterative(currentArray, size);
    // d4 += get<1>(result);
    // a4 << get<0>(result) << (ADD_SPACE ? " " : "");

    cout << get<0>(sumOfElementsOfLargestSubarray(currentArray, size));
    delete[] currentArray;
  } cout << endl;
  dataSource.close();

  // //! Checking
  // cout << "Naive Output:              " << a1.str() << " Average Speed Of Completion: " << (static_cast<long double>(d1) / 4) << " microseconds" << endl
  //      << "Divide And Conquer Output: " << a2.str() << " Average Speed Of Completion: " << (static_cast<long double>(d2) / 4) << " microseconds" << endl
  //      << "Top-Down Output:           " << a3.str() << " Average Speed Of Completion: " << (static_cast<long double>(d3) / 4) << " microseconds" << endl
  //      << "Bottom-Up Output:          " << a4.str() << " Average Speed Of Completion: " << (static_cast<long double>(d4) / 4) << " microseconds" << endl;
  return 0;
}