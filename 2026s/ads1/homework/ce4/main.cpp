#include "LinkedList.h"
#include "answer.h"
#include <chrono>
#include <fstream>
#include <iostream>

LinkedList* buildAdjacencyList(int n, int m, int a[], int b[]) {
  LinkedList* adjList = new LinkedList[n];
  
  for (int i = 0; i < m; i++) {
      int u = a[i];
      int v = b[i];
      adjList[u].insert(v);
      adjList[v].insert(u);
  }
  
  return adjList;
}

int main() {
  std::ifstream infile("tests.txt");

  if (!infile) {
    std::cerr << "Cannot open input files\n";
    return 1;
  }

  int path_tests_passed = 0;
  int components_tests_passed = 0;
  bool stop_counting = false;
  double total_path_time = 0.0;
  double total_comp_time = 0.0;

  int T;
  infile >> T;

  for (int test_id = 1; test_id <= T; test_id++) {
    int n, m;
    infile >> n >> m;
    int *a = new int[m];
    int *b = new int[m];
    for (int i = 0; i < m; i++)
      infile >> a[i] >> b[i];

    LinkedList *adjList = buildAdjacencyList(n, m, a, b);

    int pathStart;
    int pathEnd;
    int expected_components;
    std::string expected_path_str;
    infile >> pathStart >> pathEnd >> expected_path_str >> expected_components;
    bool expected_path = (expected_path_str == "true");

    // Path Test
    auto start = std::chrono::high_resolution_clock::now();
    bool path_exists = pathExists(adjList,n, pathStart, pathEnd);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    double path_time = elapsed.count();
    total_path_time += path_time;
    
    bool path_passed = (path_exists == expected_path);

    path_tests_passed+= (int) (path_passed && (path_time < 3.0));

    std::cout << "Path Test " << test_id << ": "
              << (path_passed ? "PASSED" : "FAILED")
              << "       | Path time: " << elapsed.count() << " s\n";

    // Components test

    bool stop_counting = false;
    start = std::chrono::high_resolution_clock::now();
    int components = connectedComponents(adjList, n);
    end = std::chrono::high_resolution_clock::now();

    elapsed = end - start;
    double components_time = elapsed.count();
    total_comp_time += components_time;

    bool components_passed = (components == expected_components) && (components_time < 3.0);

    components_tests_passed+= (int) (components_passed);


    std::cout << "Components Test " << test_id << ": "
              << (components_passed ? "PASSED" : "FAILED")
              << " | Components time: " << elapsed.count() << " s\n\n";

    delete[] a;
    delete[] b;
    delete[] adjList;
  }

  std::cout << "\nSUMMARY\n"
            << " path_tests_passed=" << path_tests_passed << "/" << T
            << " total_path_time=" << total_path_time << std::endl;
  std::cout << " components_tests_passed=" << components_tests_passed << "/" << T
            << " total_comp_time=" << total_comp_time << std::endl;

  infile.close();
  // expected_file.close();
  return 0;
}
