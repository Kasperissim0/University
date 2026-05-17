//§ Requisities
  //§ Includes
    #include <iostream>
    #include <filesystem>
    #include <fstream>
    #include <cstddef>
    #include <string>
    #include <vector>
    #include <algorithm>
    #include <array>
    #include <chrono>
    #include <utility>
    #include <sstream>
    #include <print>
    #include <cassert>
    #if __has_include("random.hpp")
      #include "random.hpp"
    #else
      #include <random>
      #include <type_traits>

      class RandomNumberGenerator {
          std::mt19937 engine;
        public:
          RandomNumberGenerator() {
            std::random_device seed;
            engine.seed(seed());
          }
          template <typename T>
          T generate(T min, T max) {
            if constexpr (std::is_integral_v<T>) {
              std::uniform_int_distribution<T> distribution(min, max);
              return distribution(engine);
            } else if constexpr (std::is_floating_point_v<T>) {
              std::uniform_real_distribution<T> distribution(min, max);
              return distribution(engine);
            } else {
              static_assert(std::is_arithmetic_v<T>, "Type must be numeric");
              return 0;
            }
          }
      }; RandomNumberGenerator gen;
    #endif
  //.
  //§ Aliases
    using namespace std;
    using st = size_t;
    namespace fs = filesystem;
    using timetype = std::chrono::microseconds;
    using ComputationTable = vector<vector<int>>;
    #define VARIABLE_INIT(VALUE) \
      const auto s1_size = s1.size(), s2_size = s2.size(), rowAmount = s1_size + 1, columnAmount = s2_size + 1; \
        ComputationTable cache(rowAmount, vector<int>(columnAmount, VALUE)); cache.at(0).at(0) = 0; \
        for (st i = 1; i < columnAmount; ++i) cache.at(0).at(i) = cache.at(0).at(i - 1) + 1; \
        for (st i = 1; i < rowAmount; ++i)    cache.at(i).at(0) = cache.at(i - 1).at(0) + 1;
  //.
  //§ Implementation
    auto edit_distance_tab(const string &s1, const string &s2) {
      VARIABLE_INIT(0)

      for (st substr_len_s1 = 1; substr_len_s1 < rowAmount; ++substr_len_s1)
        for (st substr_len_s2 = 1; substr_len_s2 < columnAmount; ++substr_len_s2) {
          const auto replaceCost = cache.at(substr_len_s1 - 1).at(substr_len_s2 - 1) + ((s1.at(substr_len_s1 - 1) == s2.at(substr_len_s2 - 1)) ? 0 : 1),
                     deleteCost  = cache.at(substr_len_s1 - 1).at(substr_len_s2) + 1,
                     insertCost  = cache.at(substr_len_s1).at(substr_len_s2 - 1) + 1;
          cache.at(substr_len_s1).at(substr_len_s2) = min({insertCost, deleteCost, replaceCost});
        } return cache.at(s1_size).at(s2_size);
    }
    auto memo_helper(const string &s1, const string &s2, const int row, const int column, ComputationTable &cache) {
      auto &currentEntry = cache.at((row == -1 ? 0 : row)).at((column == -1 ? 0 : column));
      if (currentEntry != -1) return currentEntry;
      // assert(row >= 0 && column >= 0);
      return currentEntry = min({memo_helper(s1, s2, row - 1, column - 1, cache) + ((s1.at(row - 1) == s2.at(column - 1)) ? 0 : 1),
                                   memo_helper(s1, s2, row, column - 1, cache) + 1,
                                   memo_helper(s1, s2, row - 1, column, cache) + 1});
    }
    auto edit_distance_memo(const string &s1, const string &s2) {
      VARIABLE_INIT(-1)

      return memo_helper(s1, s2, s1_size, s2_size, cache);
    }
  //.
//.
auto edit_distance(const string &s1, const string &s2) {
  return((s1 == s2) ? 0 : (gen.generate<int>(0, 1) ? edit_distance_tab(s1, s2) : edit_distance_memo(s1, s2)));
}
int main() { // output: 4444474646484748454742454445464644484548484847454446484444454447464546454848454641464547474543464746
  array<pair<stringstream, timetype>, 2> outputs;
  ifstream dataSource(fs::path("/Users/kasperissim0/Code/Archive/University/2026s/ads1/challenge/task-4/input.txt")); if (!dataSource.is_open()) return 1;
  st amountOfTests { 0 }; dataSource >> amountOfTests; // if this is meant to be tested, then the path for the input file (obviously) needs to be changed 
                                                       // i couldn't get it to work with relative paths for some reason
  for (st i = 0; i < amountOfTests; i += 2) {
    string a, b; dataSource >> a >> b; // cout << edit_distance(a, b);
    const auto now = []() {
      return chrono::duration_cast<timetype>(
        chrono::high_resolution_clock::now().time_since_epoch()
      );
    };
    
    outputs.at(0).second = now();
    outputs.at(0).first << edit_distance_tab(a, b);
    outputs.at(0).second = now() - outputs.at(0).second;
    outputs.at(1).second = now();
    outputs.at(1).first << edit_distance_memo(a, b);
    outputs.at(1).second = now() - outputs.at(1).second;
  } dataSource.close();
  print("\nTabulation:  {} | Took: {}\nMemoization: {} | Took: {}\n", outputs.at(0).first.str(), outputs.at(0).second, 
                                                                          outputs.at(1).first.str(), outputs.at(1).second);
  return 0;
}