#include "answer.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string rtrim(const string &s) {
    size_t end = s.find_last_not_of(" \t\r");
    if (end == string::npos)
        return "";
    return s.substr(0, end + 1);
}

string stripTrailingSpaces(const string &text) {
    istringstream in(text);
    ostringstream out;
    string line;
    bool first = true;
    while (getline(in, line)) {
        if (!first)
            out << '\n';
        out << rtrim(line);
        first = false;
    }
    return out.str();
}

vector<string> splitExpectedTests(const string &content) {
    vector<string> tests;
    istringstream in(content);
    string line, block;
    while (getline(in, line)) {
        if (line.empty()) {
            if (!block.empty()) {
                tests.push_back(stripTrailingSpaces(block));
                block.clear();
            }
        } else {
            block += line + "\n";
        }
    }
    if (!block.empty())
        tests.push_back(stripTrailingSpaces(block));
    return tests;
}

int main() {

    ifstream testsFile("tests.txt");
    ifstream expectedFile("expected_output.txt");
    if (!testsFile.is_open() || !expectedFile.is_open()) {
        cerr << "Error: Could not open tests.txt or expected_output.txt\n";
        return 1;
    }

    size_t T;
    if (!(testsFile >> T)) {
        cerr << "Error: Invalid tests.txt format.\n";
        return 1;
    }

    string dummy;
    getline(testsFile, dummy);

    stringstream buffer;
    buffer << expectedFile.rdbuf();
    vector<string> expected_tests = splitExpectedTests(buffer.str());

    if (expected_tests.size() != T) {
        cerr << "Warning: expected_output.txt has " << expected_tests.size()
             << " blocks, but tests.txt says " << T << " tests.\n";
    }

    auto start_time = chrono::high_resolution_clock::now();

    for (size_t t = 1; t <= T; ++t) {
        size_t n;
        if (!(testsFile >> n)) {
            cerr << "Error: Missing test case size for test " << t << "\n";
            return 1;
        }

        vector<int> arr(n);
        for (size_t i = 0; i < n; ++i)
            testsFile >> arr[i];

        ostringstream student_out;
        streambuf *old_buf = cout.rdbuf(student_out.rdbuf());
        radixSort(arr);
        cout.rdbuf(old_buf);

        string student_output = stripTrailingSpaces(student_out.str());
        string expected_output = (t - 1 < expected_tests.size()) ? expected_tests[t - 1] : "";

        if (student_output != expected_output) {
            cout << "❌ Test " << t << " failed.\n";
            cout << "Expected output:\n" << expected_output << "\n";
            cout << "Got output:\n" << student_output << "\n";
            cout << "Stopping further checks.\n";
            return 0;
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    double elapsed = chrono::duration<double>(end_time - start_time).count();

    cout << "✅ All " << T << " tests passed successfully!\n";
    cout << "⏱ Total execution time: " << elapsed << " seconds.\n";

    return 0;
}
