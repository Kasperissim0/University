#include <chrono>
#include <cstdlib>
#include <format>
#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include <iostream>

constexpr auto sum(const int arr[], const std::size_t &&start, const std::size_t &&end) {
  if (start == end) return ((std::rand() % 2) ? arr[start] : arr[end]);
  const auto pivot = (start + end) / 2;
  return (sum(arr, std::forward<const size_t>(start), std::move(pivot)) + sum(arr, (pivot + 1), std::forward<const size_t>(end)));
}
constexpr auto sum(const auto &arr, const std::size_t &size) {
  return (sum(arr.get(), 0, (size - 1)));
}
constexpr auto timeSince(const auto &start) {
  return std::chrono::duration_cast<std::chrono::nanoseconds>((std::chrono::high_resolution_clock::now() - start));
}
int main(int n, char** args) { if (n < 2) return EXIT_FAILURE;
  const auto startTime = std::chrono::high_resolution_clock::now();
  const auto amountOfElements = (static_cast<size_t>(n) - 1);
  const auto array = std::make_unique<int[]>(amountOfElements);

  try {
    for (size_t i = 1; i <= amountOfElements; ++i)
      array.get()[(i - 1)] = std::stoi(args[i]);
  } catch (...) { return EXIT_FAILURE; }

  std::cout << std::format("Sum: {}\nTook: {}", sum(array, amountOfElements), timeSince((startTime))) << std::endl;
  return EXIT_SUCCESS;
}