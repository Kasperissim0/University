#include <iostream>
#include <fstream>
#include <chrono>
#include "LinkedList.h"
#include "answer.h"

bool test_list(LinkedList* adjList, int n, int m, int a[], int b[]) {
    bool ok = true;
    for (int i = 0; i < m; i++) {
        int u = a[i], v = b[i];
        if (!adjList[u].search(v)) {
            ok = false;
            std::cout << "List missing edge (" << u << "," << v << ")\n";
        }
        if (!adjList[v].search(u)) {
            ok = false;
            std::cout << "List missing edge (" << v << "," << u << ")\n";
        }
    }

    int total_length = 0;
    for (int i = 0; i < n; i++) {
        total_length += adjList[i].get_length();
    }
    if (total_length != 2 * m) {
        ok = false;
        std::cout << "Total adjacency list length mismatch: "
                  << "expected=" << 2 * m
                  << " got=" << total_length << std::endl;
    }

    return ok;
}

int main() {
    std::ifstream infile("tests.txt");

    if (!infile) {
        std::cerr << "Cannot open input files\n";
        return 1;
    }

    int tests_passed = 0;
    int list_tests_passed = 0;
    bool stop_counting = false;
    double total_path_time = 0.0;

    int T; infile >> T;

    for (int test_id = 1; test_id <= T; test_id++) {
        int n, m; infile >> n >> m;
        int* a = new int[m];
        int* b = new int[m];
        for (int i = 0; i < m; i++) infile >> a[i] >> b[i];

        LinkedList* adjList = buildAdjacencyList(n, m, a, b);

        bool list_ok = test_list(adjList, n, m, a, b);

        std::cout << "List Test " << test_id << ": "
                  << (list_ok ? "PASSED" : "FAILED")
                  << "\n";

        list_tests_passed += (int) list_ok;

        int pathStart; int pathEnd; int maxLen; std::string expected_path_str;
        infile >> pathStart >> pathEnd >> maxLen >> expected_path_str;
        bool expected_path = (expected_path_str == "true");

        auto start = std::chrono::high_resolution_clock::now();
        bool path_ok = pathExists(adjList, pathStart, pathEnd, maxLen);
        auto end = std::chrono::high_resolution_clock::now();

        

        std::chrono::duration<double> elapsed = end - start;
        double path_time = elapsed.count();
        total_path_time += path_time;

        bool passed = list_ok && (path_ok == expected_path);

        if (!stop_counting) {
            if (!passed) {
                stop_counting = true;
            } else if (path_time > 3.0) {
                stop_counting = true;
            } else {
                tests_passed++;
            }
        }

        std::cout << "Path Test " << test_id << ": "
                  << (passed ? "PASSED" : "FAILED")
                  << " | Path time: " << elapsed.count() << " sec.\n\n";

        delete[] a; delete[] b; delete[] adjList;
    }

    std::cout << "SUMMARY "
              << " list_tests_passed=" << tests_passed << "/" << T 
              << " path_tests_passed=" << tests_passed << "/" << T 
              << " total_path_time=" << total_path_time
              << std::endl;

    infile.close();
    // expected_file.close();
    return 0;
}
