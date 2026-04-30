/**
 * [Learning]
 * 
 * --- Ultimate Vector Master Benchmark Suite (Audit Edition v7.0) ---
 * 
 * * This suite performs a deep architectural audit of:
 *   1. std::vector (Industry Standard)
 *   2. basic::Vector (Standard implementation)
 *   3. opt::Vector (Optimization attempt with state issues)
 * 
 * * Architectural Scrutiny:
 *   - Local Conventions: Integrated //§ and //. markers for hierarchical sectioning.
 *   - Ranked Summaries: Sorted leaderboards (🥇, 🥈, 🥉) after each table.
 *   - No Magic Numbers: Entire table layout is defined by row/column constants.
 *   - Crash Resilience: SIGSEGV + longjmp for surviving implementation bugs.
 */

//§ Requisites
  //§ Includes
    #include <iostream>
    #include <chrono>
    #include <vector>
    #include <string>
    #include <iomanip>
    #include <numeric>
    #include <algorithm>
    #include <random>
    #include <memory>
    #include <concepts>
    #include <stdexcept>
    #include <utility>
    #include <sstream>
    #include <csignal>
    #include <csetjmp>
    #include <map>
    #include <ostream>
    #include <iterator>
    #include <initializer_list>
    #include <cstddef>

    // Global Color Include
    #include "/Users/kasperissim0/Code/Includes/colors.hpp"
  //.
  //§ Aliases
    using st   = std::size_t;
    using diff = std::ptrdiff_t;
  //.
  //§ Custom Implementations
    namespace basic {
        #include "src/vector.hpp"
    }

    namespace opt {
        #include "src/optimized-vector.hpp"
    }
  //.
//.

//§ Infrastructure
  //§ Layout Constants
    constexpr int OP_WIDTH      { 34 };
    constexpr int DATA_WIDTH    { 22 };
    constexpr int WINNER_WIDTH  { 20 };
    constexpr int TABLE_WIDTH   { (OP_WIDTH + 4 + (DATA_WIDTH * 3) + 7 + WINNER_WIDTH + 3) + 2 };
  //.
  //§ Scale Constants
    constexpr st SCALE_100K  { 100'000 };
    constexpr st SCALE_10K   {  10'000 };
    constexpr st SCALE_1K    {   1'000 };
  //.
  //§ Crash Recovery
    static std::jmp_buf jump_buffer;
    static void segfault_handler([[maybe_unused]] int sig) {
        std::longjmp(jump_buffer, 1);
    }
  //.
  //§ STL Parity Concepts
    template<typename V> concept HasAt      = requires(V v) { v.at(0); };
    template<typename V> concept HasFront   = requires(V v) { v.front(); };
    template<typename V> concept HasBack    = requires(V v) { v.back(); };
    template<typename V> concept HasData    = requires(V v) { v.data(); };
    template<typename V> concept HasResize  = requires(V v) { v.resize(10); };
    template<typename V> concept HasShrink  = requires(V v) { v.shrink_to_fit(); };
    template<typename V> concept HasAssign  = requires(V v) { v.assign(10, 1.0); };
    template<typename V> concept HasSwap    = requires(V v1, V v2) { v1.swap(v2); };
    template<typename V> concept HasEmplace = requires(V v) { v.emplace_back(1.0); };
    template<typename V> concept HasCustomBool = requires(V v) { { v.begin().operator bool() } -> std::same_as<bool>; };
    template<typename V> concept SafeInitAssign = !std::same_as<V, opt::Vector<double>> && requires(V v) { v = {1.0, 2.0}; };
  //.
//.

//§ Data Structures
  enum class Status { OK, MISSING, SEGFAULT, EXCEPTION, BROKEN };

  struct Result {
      long long timeResult { -1 };
      st        spaceResult { 0 };
      Status    status      { Status::OK };
  };

  struct BenchmarkResult {
      std::string testName;
      Result      stdRes;
      Result      basicRes;
      Result      optRes;
  };
//.

//§ Formatting Engine
  //§ Text Centering
    std::string centerText(const std::string& str, int width) {
        int len = static_cast<int>(str.length());
        if (len >= width) return str;
        int left = (width - len) / 2;
        int right = width - len - left;
        return std::string(static_cast<st>(left), ' ') + str + std::string(static_cast<st>(right), ' ');
    }
  //.
  //§ Result Formatters
    std::string formatTime(const Result& res) {
        if (res.status == Status::MISSING)   return "MISSING";
        if (res.status == Status::SEGFAULT)  return "SEGFAULT";
        if (res.status == Status::EXCEPTION) return "EXCEPTION";
        if (res.status == Status::BROKEN)    return "BROKEN";
        if (res.timeResult == -1)            return "FAIL";
        if (res.timeResult == 0)             return "<1us";
        return std::to_string(res.timeResult) + "us";
    }

    std::string formatSpace(const Result& res) {
        if (res.status == Status::MISSING)   return "N/A";
        if (res.status == Status::SEGFAULT)  return "SEGFAULT";
        if (res.status == Status::EXCEPTION) return "EXCEPTION";
        if (res.status == Status::BROKEN)    return "BROKEN";
        if (res.status != Status::OK)        return "-";
        if (res.spaceResult >= 1024 * 1024)  return std::to_string(res.spaceResult / (1024 * 1024)) + "MB";
        if (res.spaceResult >= 1024)         return std::to_string(res.spaceResult / 1024) + "KB";
        return std::to_string(res.spaceResult) + "B";
    }
  //.
  //§ Winners & Leaderboards
    std::vector<std::string> calculateWinners(const BenchmarkResult& r, bool isTime) {
        long long bestVal { -1 };
        std::vector<std::string> winners;

        auto compare = [&](const Result& res, std::string name) {
            if (res.status != Status::OK) return;
            long long val = isTime ? res.timeResult : static_cast<long long>(res.spaceResult);
            if (bestVal == -1 || val < bestVal) {
                bestVal = val;
                winners.clear();
                winners.push_back(name);
            } else if (val == bestVal) {
                winners.push_back(name);
            }
        };

        compare(r.stdRes, "std");
        compare(r.basicRes, "bas");
        compare(r.optRes, "opt");
        return winners;
    }

    std::string getWinnerString(const std::vector<std::string>& winners) {
        if (winners.empty()) return "NONE";
        std::string s = winners[0];
        for (st i { 1 }; i < winners.size(); ++i) s += "/" + winners[i];
        return s;
    }

    void printSummary(const std::string& title, const std::map<std::string, int>& wins) {
        std::vector<std::pair<std::string, int>> sortedWins(wins.begin(), wins.end());
        std::sort(sortedWins.begin(), sortedWins.end(), [](auto& a, auto& b) { return b.second < a.second; });

        std::cout << bold << "\n" << title << reset << std::endl;
        const char* medals[] = {"🥇 ", "🥈 ", "🥉 "};
        for (st i { 0 }; i < sortedWins.size(); ++i) {
            std::string rank = (i < 3) ? medals[i] : "   ";
            std::cout << rank << bold << cyan << std::right << std::setw(2) << sortedWins[i].second << reset 
                      << " wins - " << sortedWins[i].first << std::endl;
        }
    }
  //.
  //§ Table Construction
    void printMetric(const Result& res, bool isTime) {
        if (res.status == Status::OK)             std::cout << green;
        else if (res.status == Status::MISSING)   std::cout << yellow;
        else                                      std::cout << red;
        std::cout << centerText(isTime ? formatTime(res) : formatSpace(res), DATA_WIDTH) << reset;
    }

    void printDivider(int width) {
        std::cout << dim << std::string(static_cast<st>(width), '-') << reset << std::endl;
    }

    void printTableHead(std::string title) {
        std::cout << bold << blue << "\n" << title << reset << std::endl;
        std::cout << dim << std::string(static_cast<st>(TABLE_WIDTH), '=') << reset << std::endl;
        std::cout << "| " << std::left << std::setw(OP_WIDTH) << centerText("Benchmark Operation", OP_WIDTH) 
                  << " | " << centerText("std::vector", DATA_WIDTH) 
                  << " | " << centerText("basic::Vector", DATA_WIDTH) 
                  << " | " << centerText("opt::Vector", DATA_WIDTH) 
                  << " | " << centerText("Winner 🏆", WINNER_WIDTH) << " |" << std::endl;
        printDivider(TABLE_WIDTH);
    }
  //.
//.

//§ Execution Core
  template<typename V> bool isStateBroken(const V& v) {
      if constexpr (HasCustomBool<V>) {
          if (v.capacity() > 0 && !v.begin().operator bool()) return true;
      }
      return false;
  }

  template<typename Vec, typename T = double>
  Result runBenchmark(auto&& op) {
      Result res;
      void (*prev_handler)(int) = std::signal(SIGSEGV, segfault_handler);
      if (setjmp(jump_buffer) == 0) {
          try {
              Vec v;
              auto startTime = std::chrono::high_resolution_clock::now();
              op(v);
              auto endTime = std::chrono::high_resolution_clock::now();
              if (isStateBroken(v)) { res.status = Status::BROKEN; }
              else {
                  res.timeResult = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
                  res.spaceResult = v.capacity() * sizeof(T);
                  res.status = Status::OK;
              }
          } catch (...) { res.status = Status::EXCEPTION; }
      } else { res.status = Status::SEGFAULT; }
      std::signal(SIGSEGV, prev_handler);
      return res;
  }
//.

//§ Main Entry
  int main() {
      std::vector<BenchmarkResult> allResults;
      auto addTest = [&](std::string name, auto&& op) {
          BenchmarkResult br;
          br.testName = name;
          br.stdRes   = runBenchmark<std::vector<double>>(op);
          br.basicRes = runBenchmark<basic::Vector<double>>(op);
          try { br.optRes = runBenchmark<opt::Vector<double>>(op); } catch (...) { br.optRes.status = Status::EXCEPTION; }
          allResults.push_back(br);
      };

      //§ Test Suite Definition
        addTest("Growth: Push Back (10k)",      [](auto& v){ for(st i { 0 }; i < SCALE_10K; ++i) v.push_back(1.0); });
        addTest("Growth: Emplace Back (10k)",   [](auto& v){ if constexpr (HasEmplace<decltype(v)>) { for(st i { 0 }; i < SCALE_10K; ++i) v.emplace_back(1.0); } else throw Status::MISSING; });
        addTest("Capacity: Reserve (100k)",     [](auto& v){ v.reserve(SCALE_100K); });
        addTest("Capacity: shrink_to_fit()",    [](auto& v){ v.reserve(100); v.push_back(1.0); if constexpr (HasShrink<decltype(v)>) { v.shrink_to_fit(); } else throw Status::MISSING; });
        addTest("Access: front() / back()",     [](auto& v){ v.push_back(1.0); v.push_back(2.0); if constexpr (HasFront<decltype(v)> && HasBack<decltype(v)>) { (void)v.front(); (void)v.back(); } else throw Status::MISSING; });
        addTest("Access: [] (Standard)",        [](auto& v){ v.push_back(1.0); (void)v[0]; });
        addTest("Access: at() (Checked)",       [](auto& v){ v.push_back(1.0); if constexpr (HasAt<decltype(v)>) { (void)v.at(0); } else { (void)v[0]; } });
        addTest("Access: data() pointer",       [](auto& v){ v.push_back(1.0); if constexpr (HasData<decltype(v)>) { (void)v.data(); } else throw Status::MISSING; });
        addTest("Modifier: Erase Middle (1k)",  [](auto& v){ for(st i { 0 }; i < SCALE_10K; ++i) v.push_back(1.0); for(st i { 0 }; i < SCALE_1K; ++i) v.erase(v.begin() + static_cast<long>(v.size()/2)); });
        addTest("Modifier: Insert Start (1k)",  [](auto& v){ v.reserve(SCALE_1K + 1); for(st i { 0 }; i < SCALE_1K; ++i) v.insert(v.begin(), 1.0); });
        addTest("Modifier: Resize (1k)",        [](auto& v){ if constexpr (HasResize<decltype(v)>) { v.resize(SCALE_1K); } else throw Status::MISSING; });
        addTest("Modifier: Swap vectors",       [](auto& v1){ using V = std::decay_t<decltype(v1)>; if constexpr (HasSwap<V>) { V vT; vT.push_back(2.0); v1.push_back(1.0); v1.swap(vT); } else throw Status::MISSING; });
        addTest("Modifier: assign(n, val)",     [](auto& v){ if constexpr (HasAssign<decltype(v)>) { v.assign(SCALE_1K, 1.0); } else throw Status::MISSING; });
        addTest("Lifecycle: InitList Const.",   [](auto& v){ if constexpr (SafeInitAssign<std::decay_t<decltype(v)>>) { v = {1.0, 2.0, 3.0, 4.0, 5.0}; } else { v.push_back(1.0); v.push_back(2.0); v.push_back(3.0); v.push_back(4.0); v.push_back(5.0); } });
        addTest("Lifecycle: Copy Construction", [](auto& v1){ for(st i { 0 }; i < SCALE_1K; ++i) v1.push_back(1.0); using V = std::decay_t<decltype(v1)>; V vT(v1); (void)vT; });
        addTest("Algo: std::sort (10k)",         [](auto& v){ for(st i { 0 }; i < SCALE_10K; ++i) v.push_back(static_cast<double>(rand()%100)); std::sort(v.begin(), v.end()); });
      //.

      std::map<std::string, int> timeWins  = {{"std::vector", 0}, {"basic::Vector", 0}, {"opt::Vector", 0}};
      std::map<std::string, int> spaceWins = {{"std::vector", 0}, {"basic::Vector", 0}, {"opt::Vector", 0}};
      std::map<std::string, int> totalWins = {{"std::vector", 0}, {"basic::Vector", 0}, {"opt::Vector", 0}};

      auto recordWin = [&](const std::vector<std::string>& winners, std::map<std::string, int>& target) {
          for (const auto& w : winners) {
              if (w == "std") { target["std::vector"]++; totalWins["std::vector"]++; }
              if (w == "bas") { target["basic::Vector"]++; totalWins["basic::Vector"]++; }
              if (w == "opt") { target["opt::Vector"]++; totalWins["opt::Vector"]++; }
          }
      };

      //§ Results Table 1: Time
        printTableHead("⏱️  Time Audit (Latency in microseconds)");
        for (const auto& row : allResults) {
            auto winners = calculateWinners(row, true);
            recordWin(winners, timeWins);
            std::cout << "| " << std::left << std::setw(OP_WIDTH) << row.testName << " | ";
            printMetric(row.stdRes, true); std::cout << " | ";
            printMetric(row.basicRes, true); std::cout << " | ";
            printMetric(row.optRes, true); std::cout << " | ";
            std::cout << cyan << centerText(getWinnerString(winners), WINNER_WIDTH) << reset << " |" << std::endl;
        }
        printDivider(TABLE_WIDTH);
    //     printSummary("📊 Time Performance Ranking:", timeWins);
    //   //.

    //   //§ Results Table 2: Space
    //     printTableHead("💾  Space Audit (Memory usage in Bytes/KB/MB)");
    //     for (const auto& row : allResults) {
    //         auto winners = calculateWinners(row, false);
    //         recordWin(winners, spaceWins);
    //         std::cout << "| " << std::left << std::setw(OP_WIDTH) << row.testName << " | ";
    //         printMetric(row.stdRes, false); std::cout << " | ";
    //         printMetric(row.basicRes, false); std::cout << " | ";
    //         printMetric(row.optRes, false); std::cout << " | ";
    //         std::cout << cyan << centerText(getWinnerString(winners), WINNER_WIDTH) << reset << " |" << std::endl;
    //     }
    //     printDivider(TABLE_WIDTH);
    //     printSummary("📊 Space Efficiency Ranking:", spaceWins);
    //   //.

      //§ Final Architectural Victory
        std::cout << Color::MAGENTA << "\n" << std::string(TABLE_WIDTH, '*') << reset << std::endl;
        printSummary("🏆 OVERALL ARCHITECTURAL VICTORY:", totalWins);
        std::cout << Color::MAGENTA << std::string(TABLE_WIDTH, '*') << reset << std::endl;
      //.

      return 0;
  }
//.
