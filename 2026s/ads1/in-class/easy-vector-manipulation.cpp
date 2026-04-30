#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using st = size_t;

/* Implement the following function by filling in the missing parts. */
std::vector<int> vector_filter(const int arr[], const st n, const int k){
  std::vector<int> vec = {};

  for (st i = 0; i < n; ++i)
    if (arr[i] <= k) vec.push_back(arr[i]);

  return vec;
}

/* Implement the following function by filling in the missing parts. */
std::vector<int> vector_backwards_forwards(const int arr[], const st n){
  std::vector<int> vec = {};

  for (st i = 0; i < n; ++i)
    vec.insert(vec.begin(), arr[i]), vec.push_back(arr[i]);
  return vec;
}

void test_vec() {
  std::srand(static_cast<unsigned>(std::time(0)));
  st num_elements = static_cast<unsigned>(std::rand() % 100000 + 1);
  int k = std::rand();
  int arr[100001];
  // st count = 0;

  // Fill array with random elements
  for (st i = 0; i < num_elements; ++i) {
    arr[i] = std::rand();
  }
  std::cout << "Testing function vector_filter..." << std::endl;  
  std::vector<int> filtered_vector = vector_filter(arr, num_elements, k);
  st j = 0;
  for (st i = 0; i < num_elements; ++i){
    if (arr[i] <= k){
      assert(arr[i] == filtered_vector[j++]);
    }
  }
  assert(filtered_vector.size() == j);
  std::cout << "Test of vector_filter passed!" << std::endl; 
  
  std::cout << "Testing function vector_backwards_forwards..." << std::endl; 
  std::vector<int> vector_from_function = vector_backwards_forwards(arr,num_elements);
  // Verify
  assert(vector_from_function.size() == 2*num_elements);
  for (st i = 0; i < num_elements; ++i) {
    assert(vector_from_function[i] == arr[num_elements-1-i]);
    assert(vector_from_function[num_elements+i] == arr[i]);
  }
  std::cout << "Test of function vector_backwards_forwards passed!" << std::endl; 
}

int main() {
  test_vec();
  std::cout << "All tests passed!" << std::endl;
  return 0;
}