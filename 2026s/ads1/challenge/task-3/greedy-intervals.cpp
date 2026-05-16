//§ Requisities
  //§ Includes
    #include <algorithm>
    #include <cstddef>
    #include <iostream>
    #include <fstream>
    #include <filesystem>
    #include <utility>
    #include <vector>
  //.
  //§ Aliases
    using namespace std;
    namespace fs = filesystem;
    using st = size_t;
    using interval = pair<st, st>;
    using it = vector<interval>::const_iterator;
  //.
//.
//* Proof: 
  /*
    Assumption:
      The following is under the assumption that all intervals are "valid", that is 'start ≤ end' for every interval.
    Lemma:
      Greedily choosing the compatible interval with the smallest end value always preserves the existence of an optimal solution.
    Proof:
      Let i be the interval chosen greedily (smallest end value among the remaining intervals) and let S be an optimal solution. 
      If S already contains i, done. Otherwise let f be the first interval in S. 
      Since i was chosen greedily among all compatible intervals: 'i.end ≤ f.end'.
      Every interval appearing after f in S must begin at or after f.end, since S is non-overlapping. 
      Since: 'i.end ≤ f.end' every interval appearing after f in S is also compatible with i. 
      Therefore replacing f with i preserves both: 
        1. compatibility 
        2. the number of selected intervals
      Thus there exists an optimal solution containing i. □

    Definition:
      P(n): when a valid vector of 'n' intervals (i.e. 'n == intervals.size()') is passed to 'max_non_overlapping_intervals', 
            it returns the maximum number of non-overlapping intervals in that vector.
    The proof is by induction on 'intervals.size()':
      Base Cases:
        P(0): 'intervals' is empty, early return fires, returns --amount = 0. 
          ❓ Correct: empty set has 0 non-overlapping intervals. ✅
        P(1): Loop range is [begin+1, end) = [end, end), so the loop body never executes. 'amount' = 1 is returned. 
          ❓ Correct: A single valid interval trivially forms a non-overlapping set of size 1. ✅

      Inductive Step: Does 'P(k) --> P(k + 1)'?
        Assume P(k) holds for some k ≥ 1, i.e. after processing: intervals[0], ..., intervals[k - 1]:
          (a) 'amount' is the maximum number of non-overlapping intervals selectable from intervals[0], ..., intervals[k-1].
          (b) 'currentEnd' equals the end value of the last selected interval.
          (c) every selected interval was chosen greedily (i.e. among all compatible remaining intervals, it had the smallest end value.)
        We now process intervals[k] with: start = intervals[k].first end = intervals[k].second.
          Two cases are possible:
            Overlapping (start < currentEnd):
              Since 'start < currentEnd', the body does not execute, 'amount' and 'currentEnd' remain unchanged.
              ❓ Correct: By (b), intervals[k] overlaps the last selected interval, so it cannot be appended to the current selection.
                 By (c) and the ordering by increasing end values, the previously selected interval finishes no later than intervals[k], 
                 so replacing it with intervals[k] cannot increase the number of future compatible intervals.
                 Hence, by (a), the current value of 'amount' already equals the maximum possible count for: intervals[0], ..., intervals[k - 1], 
                 and since including intervals[k] cannot yield a larger compatible set, 'amount' also remains optimal for: intervals[0], ..., intervals[k].
                 Thus: leaving 'amount' unchanged preserves correctness. ✅
            Non-Overlapping (start ≥ currentEnd):
              Since 'start >= currentEnd', the body executes: amount --> amount + 1, currentEnd --> end.
              ❓ Correct: By (b), intervals[k] is compatible with every previously selected interval, so it may be added to the current selection.
                 By (a), the current selection already has maximum size among: intervals[0], ..., intervals[k - 1], 
                 and adding intervals[k] increases that size by 1, since we want to return the maximum number of intervals this is optimal.
                 By (c) and the greedy-choice lemma, selecting the earliest-finishing compatible interval is always safe, 
                 so no larger solution can be obtained by postponing this choice. 
                 Therefore: amount --> amount + 1 remains the correct optimal count for: intervals[0], ..., intervals[k]. ✅
        In both cases, after processing intervals[k], 'amount' holds the correct count for intervals[0], ..., intervals[k], so P(k + 1) holds.
        Which means P(k) does imply P(k + 1) for all k ≥ 1.

      Conclusion:
        P(0) and P(1) hold as base cases. P(k) --> P(k + 1) for all k ≥ 1. By induction, P(n) holds for all n ≥ 0. □
  */
st max_non_overlapping_intervals(vector<interval> &intervals) {
  st amount { 1 };

  if (!intervals.empty()) {
    ranges::sort(intervals, [&](const interval &before, const interval &after){
      return (before.second < after.second);
    }); auto currentEnd = intervals.begin()->second;
    for_each((intervals.begin() + 1), intervals.end(), [&](const auto &elem){
      const auto &[start, end] = elem;
      if (start >= currentEnd) ++amount, currentEnd = end;
    }); return amount;
  } return --amount;
}
int main(int n, char** args) { // output: 775802780778801797805801800799
  if ((n - 1) % 2 == 0 and (n - 1) != 0) { // Testing out with manual interval inputs
    vector<interval> intervals;
    for (st i = 1; i < n; ++i)
      intervals.emplace_back(stoul(args[i]), stoul(args[++i])); // should probably wrap in try/catch blocks ...
    cout << "Amount: " << max_non_overlapping_intervals(intervals) << endl;
  }
  else {
    ifstream dataSource(fs::path("/Users/kasperissim0/Code/Archive/University/2026s/ads1/challenge/task-3/input.txt")); if (!dataSource.is_open()) return 1;
    st amountOfTests { 0 }; dataSource >> amountOfTests; // if this is meant to be tested, then the path for the input file (obviously) needs to be changed 
                                                        // i couldn't get it to work with relative paths for some reason
    while (amountOfTests--) {
      st amountOfIntervals { 0 }; dataSource >> amountOfIntervals;
      vector<interval> intervals(amountOfIntervals);
      
      for (auto &interval : intervals)
        dataSource >> interval.first >> interval.second;
      cout << max_non_overlapping_intervals(intervals);
    } dataSource.close();
  }
  return 0;
}
