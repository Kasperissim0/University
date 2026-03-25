//§ Includes
  #include <iostream>
  #include <algorithm>
  #include <string>
  #include <chrono>
  #include "random.hpp"
  using namespace std;
//.

auto partition(int arr[], int lessThanPivot, const int end) {
  auto &pivot = arr[gen.generate<size_t>(0, end)];
  for (size_t moreThanPivot = (lessThanPivot + 1); moreThanPivot < end; ++moreThanPivot)
    if (arr[moreThanPivot] < pivot) swap(arr[++lessThanPivot], arr[moreThanPivot]);
  return swap(pivot, arr[++lessThanPivot]), lessThanPivot;
}
auto quicksort(int arr[], const int end, const int start = 0) {
  if (start >= end) return arr;
  const auto pivot = partition(arr, (start - 1), end);
  quicksort(arr, (pivot - 1), start), quicksort(arr, end, (pivot + 1));
  return arr;
}
auto output(const int *const arr, const size_t size) { if (!arr) goto end;
  cout << "["; for (size_t i = 0; i < size; ++i) cout << arr[i] << ((i == (size - 1)) ? "" : ", "); cout << "]";
  end: return "";
}

int main(int n, char** args) {
  size_t arraySize = 10; if (n > 1) try { arraySize = stoul(args[1]); } catch (...) {}
  int arr[arraySize]; for (size_t i = 0; i < arraySize; ++i) arr[i] = gen.generate<int>(100, 900);
  cout << "Original Array: " << output(arr, arraySize) << endl
       << "Sorted Array:   " << output(quicksort(arr, (arraySize - 1)), arraySize) << endl;
  return 0;
}