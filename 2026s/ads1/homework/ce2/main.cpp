#include "HashTable.h"
#include "LinkedList.h"
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    HashTable ht;

    std::ifstream ops("ops.txt");
    if (!ops.is_open()) {
        std::cout << "Error: Could not open ops.txt\n";
        return 1;
    }

    std::ifstream tests("tests.txt");
    if (!tests.is_open()) {
        std::cout << "Error: Could not open tests.txt\n";
        return 1;
    }

    std::string op;
    int x;

    int updateCount = 0;
    int snapshotCount = 0;

    std::string expectedLine;

    while (ops >> op >> x) {

        // Perform operation
        if (op == "insert") {
            ht.insert(x);
            updateCount++;
        } else if (op == "delete") {
            ht.remove(x);
            updateCount++;
        } else {
            std::cout << "Unknown operation: " << op << "\n";
            return 1;
        }

        if (updateCount % 1000 == 0) {
            snapshotCount++;

            if (!std::getline(tests, expectedLine)) {
                std::cout << "Error: tests.txt ended too early at snapshot " << snapshotCount
                          << "\n";
                return 1;
            }

            if (expectedLine.size() == 0)
                std::getline(tests, expectedLine);

            std::stringstream ss(expectedLine);
            std::vector<int> expectedKeys;
            int v;
            while (ss >> v)
                expectedKeys.push_back(v);

            std::vector<int> actualKeys = ht.get_all_keys();

            if (actualKeys.size() != expectedKeys.size()) {
                std::cout << "[FAIL] Snapshot " << snapshotCount << ": size mismatch (expected "
                          << expectedKeys.size() << ", got " << actualKeys.size() << ")\n";
                return 0;
            }

            for (size_t i = 0; i < actualKeys.size(); i++) {
                if (actualKeys[i] != expectedKeys[i]) {
                    std::cout << "[FAIL] Snapshot " << snapshotCount << ": mismatch at index " << i
                              << " expected " << expectedKeys[i] << " got " << actualKeys[i]
                              << "\n";
                    return 0;
                }
            }
        }
    }

    std::cout << "All tests passed!\n";

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "Runtime: " << duration << " ms\n";

    return 0;
}
