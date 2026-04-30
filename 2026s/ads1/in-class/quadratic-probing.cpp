/* Part of ADS1
   University of Vienna
   Author: Sagar Kale.
   Test code generated with the help of ChatGPT 4o (OpenAI), 2025; minimal
   modifications were made to the test code. The following prompt was used.

   """
   There is still a HashTable class. But there is a hash_test.txt file with each
   line containing one of i, s, d, chars followed by a 32-bit integer. Just
   perform these operations on HashTable (i for insert, s for search, and d for
   delete) and make sure they match that of std::unordered_set. After every,
   say, 500, operations, go over whole unorderd_set and check if the int is
   present in the HashTable object.
   """

   NOTE: THE MAIN PURPOSE OF THIS CODE IS DEMONSTRATION OF
   DATA STRUCTURE CONCEPTS. THIS CODE MAY NOT NECESSARILY SHOW BEST SOFTWARE
   ENGINEERING PRACTICES!
*/

#include <chrono>
#include <fstream>
#include <iostream>
#include <cstddef>
#include <filesystem>
#include <ratio>
#include <unordered_set>

constexpr int EMPTY = -2, DELETED = -1;
constexpr size_t SIZE = 1U << 15U;

class HashTable {
private:
  size_t size = SIZE;
  int    *data = new int[size];

  [[nodiscard]] constexpr size_t hash(const size_t &value) const { // , const size_t &iteration = 0) const { 
    // return ((value % size) + ((iteration * (iteration + 1)) / 2));
    return value % size;
  }
public:
  HashTable() {
    for (size_t i = 0; i < size; ++i) {
      data[i] = EMPTY;
    }
  }
  ~HashTable() { delete[] data; }
  void insert(const int &value) {
    for (size_t iteration = 0, index = hash(value); iteration < size; ++iteration, index = ((iteration + index) % size)) {
      if (data[index] == EMPTY) {
        data[index] = value;
        break;
      }
    }
  }
  bool search(const int &value) {
    for (size_t iteration = 0, index = hash(value); iteration < size; ++iteration, index = ((iteration + index) % size)) {
      if (data[index] == value)
        return true;
      if (data[index] == EMPTY)
        return false;
    }
    return false;
  }
  void remove(const int &value) {
    for (size_t iteration = 0, index = hash(value); iteration < size; ++iteration, index = ((iteration + index) % size)) {
      if (data[index] == value)
        data[index] = DELETED;
      if (data[index] == EMPTY)
        return;
    }
  }
};

void check_consistency(HashTable &data,
                       std::unordered_set<int> &reference_set) {
  for (const int &val : reference_set) {
    if (!data.search(val)) {
      std::cerr << "Error: Value " << val
                << " not found in hash table but present in reference set."
                << std::endl;
    }
  }
}

//§ Tests
  void test_data(const std::filesystem::path &file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
      std::cerr << "Failed to open file: " << file_name << std::endl;
      return;
    }

    HashTable data;
    std::unordered_set<int> reference_set;
    std::string operation;
    int value;
    int operation_count = 0;

    while (file >> operation >> value) {
      if (operation == "i") {
        data.insert(value);
        reference_set.insert(value);
      } else if (operation == "s") {
        bool data_found = data.search(value);
        bool reference_set_found =
            reference_set.find(value) != reference_set.end();
        if (data_found != reference_set_found) {
          std::cerr << "Error: Mismatch in search for value " << value
                    << std::endl;
        }
      } else if (operation == "d") {
        data.remove(value);
        reference_set.erase(value);
        if (data.search(value)) {
          std::cerr << "Error: Value " << value
                    << " found in hash table but not present in reference set."
                    << std::endl;
        }
      } else {
        std::cerr << "Error: Unknown operation " << operation << std::endl;
      }

      operation_count++;
      if (operation_count % 500 == 0) {
        check_consistency(data, reference_set);
      }
    }

    // Final consistency check
    check_consistency(data, reference_set);

    file.close();
  }

  int main() {
    std::filesystem::path file_name = "/Users/kasperissim0/Code/Archive/University/2026s/ads1/hash_test.txt";
    const auto startTime = std::chrono::high_resolution_clock::now();

    // Test hash table
    test_data(file_name);
    std::cout << "Test finished; if no errors were reported, then all tests passed." << std::endl << "Total Time: " 
              << (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startTime)) 
              << std::endl;

    return 0;
  }
//.