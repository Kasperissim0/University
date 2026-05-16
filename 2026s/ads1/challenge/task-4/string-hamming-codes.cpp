//§ Requisities
  //§ Includes
    #include <iostream>
    #include <filesystem>
    #include <fstream>
    #include <cstddef>
    #include <string>
    #include <vector>
    #include <algorithm>
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
    using ComputationTable = vector<vector<st>>;
    constexpr st START = 1;
  //.
  //§ Implementation
    auto edit_distance_dp(const string &s1, const string &s2) {
      const auto s1_size = s1.size(), s2_size = s2.size(),
                 rowAmount = (s1_size + 1), columnAmount = (s2_size + 1); 
      ComputationTable cache(rowAmount, vector<st>(columnAmount)); cache.at(START - 1).at(START - 1) = START - 1;
      for (st i = START; i < columnAmount; ++i) cache.at(0).at(i) = (cache.at(0).at(i - 1) + 1);
      for (st i = START; i < rowAmount; ++i)    cache.at(i).at(0) = (cache.at(i - 1).at(0) + 1);

      for (st substr_len_s1 = START; substr_len_s1 < rowAmount; ++substr_len_s1) {
        for (st substr_len_s2 = START; substr_len_s2 < columnAmount; ++substr_len_s2) {
          const auto replaceCost = cache.at(substr_len_s1 - 1).at(substr_len_s2 - 1) + ((s1.at(substr_len_s1 - 1) == s2.at(substr_len_s2 - 1)) ? 0 : 1),
                     deleteCost = cache.at(substr_len_s1 - 1).at(substr_len_s2) + 1,
                     insertCost = cache.at(substr_len_s1).at(substr_len_s2 - 1) + 1;
          cache.at(substr_len_s1).at(substr_len_s2) = min({insertCost, deleteCost, replaceCost});
        }
      } return cache.at(s1_size).at(s2_size);
    }
    auto memo_helper(const string &s1, const string &s2, const st &start, const st &end, ComputationTable &cache) {
      return 1;
    }
    auto edit_distance_memo(const string &s1, const string &s2) {
      return edit_distance_dp(s1, s2);
    }
  //.
//.

auto edit_distance(const string &s1, const string &s2) {
  return((s1 == s2) ? 0 : (gen.generate<int>(0, 1) ? edit_distance_dp(s1, s2) : edit_distance_memo(s1, s2)));
}
int main() { // output: 4444474646484748454742454445464644484548484847454446484444454447464546454848454641464547474543464746
  ifstream dataSource(fs::path("/Users/kasperissim0/Code/Archive/University/2026s/ads1/challenge/task-4/input.txt")); if (!dataSource.is_open()) return 1;
  st amountOfTests { 0 }; dataSource >> amountOfTests; // if this is meant to be tested, then the path for the input file (obviously) needs to be changed 
                                                       // i couldn't get it to work with relative paths for some reason
  for (st i = 0; i < amountOfTests; i += 2) {
    string a, b; dataSource >> a >> b;

    cout << edit_distance(a, b);
  } dataSource.close();
  return 0;
}