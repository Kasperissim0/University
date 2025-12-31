// Archive/University/2025w/.homework/8/task3/get-data.cpp
//
// This program fetches album data from a public API, parses the JSON response,
// and formats it into the 'collection.txt' file.
//
// Dependencies:
// - libcurl: For making HTTP requests.
// - nlohmann/json: For parsing JSON data. (https://github.com/nlohmann/json)

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <curl/curl.h>
#include "nlohmann/json.hpp" // Assumes 'nlohmann/json.hpp' is in an include path.

// Callback function for libcurl to write received data into a std::string.
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    try {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    } catch(const std::bad_alloc& e) {
        // Handle memory allocation errors.
        std::cerr << "Error: Not enough memory (bad_alloc)." << std::endl;
        return 0;
    }
}

void fetchDataAndWriteToFile(std::string SEARCH_TARGET = "music") {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Initialize libcurl.
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Using the iTunes Search API as a placeholder data source.
        for (auto& c : SEARCH_TARGET) if (isspace(c)) c = '+';
        const std::string url = "https://itunes.apple.com/search?term="+ SEARCH_TARGET +"&entity=album&limit=50";
        
        // Set curl options.
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects.

        std::cout << "Fetching data from: " << url << std::endl;
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Data fetched successfully. Parsing JSON..." << std::endl;
            try {
                // Parse the JSON response.
                nlohmann::json jsonData = nlohmann::json::parse(readBuffer);
                
                std::ofstream outFile("collection.txt", std::ios::trunc);
                if (!outFile.is_open()) {
                    std::cerr << "Error: Failed to open collection.txt for writing." << std::endl;
                    curl_easy_cleanup(curl);
                    curl_global_cleanup();
                    return;
                }

                outFile << "--START--" << std::endl;
                unsigned int currentId = 1;

                if (jsonData.contains("results") && jsonData["results"].is_array()) {
                    for (const auto& item : jsonData["results"]) {
                        // Safely extract data using .value(), providing a default if a key is missing.
                        std::string title = item.value("collectionName", "Unknown Title");
                        std::string artist = item.value("artistName", "Unknown Artist");
                        std::string style = item.value("primaryGenreName", "Unknown Genre");

                        // Write to file in the specified format.
                        outFile << currentId++ << " | "
                                << title << " | "
                                << artist << " | "
                                << style << " |" << std::endl;
                    }
                }
                outFile << "--END--" << std::endl;
                std::cout << "✅ Successfully wrote " << (currentId - 1) << " entries to collection.txt" << std::endl;

            } catch (nlohmann::json::parse_error& e) {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
            }
        }

        // Cleanup libcurl.
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main(int argc, char** argv) {
  if (argc > 2) return 1;
  else if (argc == 1) fetchDataAndWriteToFile();
  else {
    std::string searchTarget = argv[1];
    fetchDataAndWriteToFile(searchTarget);
  }
  return 0;
}

/*
 * ==========================
 * HOW TO COMPILE AND RUN
 * ==========================
 *
 * This code requires libcurl and the nlohmann/json library.
 *
 * 1. INSTALL LIBCURL:
 *    - On macOS (Homebrew): brew install curl
 *    - On Debian/Ubuntu: sudo apt-get install libcurl4-openssl-dev
 *
 * 2. GET NLOhmann/JSON:
 *    - Download the 'json.hpp' file from https://github.com/nlohmann/json/releases
 *    - Place it in your project's include directory. For this project, you can create
 *      a 'nlohmann' folder inside 'Includes' and place 'json.hpp' there.
 *      Path: Includes/nlohmann/json.hpp
 *
 * 3. COMPILE:
 *    Use the following command, adjusting paths if necessary. It includes the
 *    'Includes' directory for nlohmann/json and links against libcurl.
 *
 *    clang++ -std=c++20 -g Archive/University/2025w/.homework/8/task3/get-data.cpp -o Build/get-data -IIncludes -lcurl
 *
 * 4. RUN:
 *    ./Build/get-data
 *
 */
