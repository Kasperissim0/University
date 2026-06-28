#include <cstdlib>
#include <print>
#include <format>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_set>
using namespace std; using tracker = unordered_set<int>;

constexpr auto SHOW_INVALID_ENTRIES = false;

auto insertionSort (vector<int> &list) { 
  if (!list.empty()) {
    using counter = decltype(list.size()); tracker entries = {list.front()};
    const auto previousEntryOf = [&](const counter &index) { return list.at(index - 1); };

    for (counter current = 1; current < list.size(); ++current) {
      auto indexOfUnsortedEntry = current; const auto unsortedEntry = list.at(indexOfUnsortedEntry); 
      const auto &[_, newEntry] = entries.insert(unsortedEntry);

      if (!newEntry) { list.erase(list.begin() + current--); continue; }
      while (indexOfUnsortedEntry > 0 and previousEntryOf(indexOfUnsortedEntry) > unsortedEntry)
        list.at(indexOfUnsortedEntry--) = previousEntryOf(indexOfUnsortedEntry);

      list.at(indexOfUnsortedEntry) = unsortedEntry;
    }
  } return list;
}
int main(int n, char** args) { if (n != 2) { println(R"(Usage: {} "n_1 n_2 ... n_k")", args[0]); return EXIT_FAILURE; }
  const string input = args[1]; string buffer; vector<int> list; const auto addEntry = [&]() {
    if (!buffer.empty()) {
      try         { list.push_back(stoi(buffer)); } 
      catch (...) { if (SHOW_INVALID_ENTRIES) println(R"(Skipping Invalid Entry "{}")", buffer); }
    } buffer.clear();
  };
  for (const auto &token : input) {
    if (isspace(token)) addEntry();
    else                   buffer += token;
  } addEntry();

  println("Input:  {}", list);
  println("Output: {}", insertionSort(list));
  return EXIT_SUCCESS;
}