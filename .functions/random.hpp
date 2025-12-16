#ifndef RANDOM
#define RANDOM
#include <type_traits>
#include <filesystem>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <vector>
#include <string>
#include <any>
#include <iomanip>

namespace fs = std::filesystem;

class Generator {
    //!  Variables
    fs::path currentFile = "input.txt";
    size_t generatedAmount = 50;
    std::mt19937 generationEngine;
    std::type_index lastTypeWritten = typeid(std::nullptr_t);
    std::vector<fs::path> createdFiles = {};

    //!  Seed Engine In Constructor
    Generator() {
      std::random_device randomSeed;
      generationEngine.seed(randomSeed());
    }
    //!  Private Value Generators
    template <typename T> T generateNumericType(const T& minValue, const T& maxValue) {
      if      constexpr (std::is_same_v<T, bool>) {
        std::uniform_int_distribution<short> distributionRange(0, 1);
        return static_cast<T>(distributionRange(generationEngine));
      }
      else if constexpr (std::is_same<T, char>() || std::is_same<T, signed char>() || std::is_same<T, unsigned char>::value) {
        std::uniform_int_distribution<short> distributionRange(minValue, maxValue);
        return static_cast<T>(distributionRange(generationEngine));
      }
      else if constexpr (std::is_integral<T>()) {
        std::uniform_int_distribution distributionRange(minValue, maxValue);
        return distributionRange(generationEngine);
      }
      else if constexpr (std::is_floating_point<T>()) {
        std::uniform_real_distribution distributionRange(minValue, maxValue);
        return distributionRange(generationEngine);
      }
      else throw std::runtime_error("Passed Type '" + std::string(typeid(T).name()) + "' Is Not Currently Supported");
    }
    std::string generateString(const size_t& lengthToGenerate, const char& startingValue = ' ', 
                                                               const char& endingValue = '~') {
      std::string construct(lengthToGenerate, '\0');
      for (size_t i = 0; i < lengthToGenerate; ++i)
        construct.at(i) = generateNumericType<char>(startingValue, endingValue); // All Values Except \special
      return construct;
    }
  public:
    //!  Singleton Type Modifications
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    Generator(Generator&&) = delete;
    Generator& operator=(Generator&&) = delete;
    static Generator& getInstance() {
      static Generator instance;
      return instance;
    }
    //!  Get Variables
    size_t getAmount() const {
      return generatedAmount;
    }
    fs::path getFile() const {
      return currentFile;
    }
    //!  Edit Configuration(s)
    Generator& setAmount(const size_t& newValue) {
      if (newValue == 0) std::cerr << "❌ Cannot Set Amount Of Generated Numbers To 0, Old Value " 
                                   << generatedAmount << " Retained" << std::endl;
      else generatedAmount = newValue;
      return *this;
    }
    Generator& setFile(const std::string& fileTitle) {
      if (fileTitle.empty()) std::cerr << "❌ Cannot Set File Title To Empty, Old Value " 
                                       << currentFile << " Retained" << std::endl;
      
      else if (fileTitle.find(".txt") != std::string::npos) currentFile = fileTitle;
      else currentFile = fileTitle + ".txt";
      return *this;
    }
    Generator& deleteFile(std::optional<fs::path> fileToDelete = std::nullopt) {
      const auto& chosenFile = (fileToDelete ? *fileToDelete : currentFile);
      // if (!fs::exists(chosenFile))                               throw std::runtime_error("File: " + chosenFile.string() + " Does Not Exist");
      // else {
        try {
          fs::remove(chosenFile); // if (!fs::remove(chosenFile))   throw std::runtime_error("File: " + chosenFile.string() + " Does Not Exist");
        }
        catch (const std::bad_alloc& e)       {                     throw std::runtime_error(e.what()); }
        catch (const fs::filesystem_error& e) {                     throw std::runtime_error(e.what()); }
        catch (const std::error_code& e)      {                     throw std::runtime_error(e.message()); }
      // }
      return *this;
    }
    Generator& deleteFiles(std::optional<std::vector<fs::path>> filesToDelete = std::nullopt) {
      const auto& chosenFiles = (filesToDelete ? *filesToDelete : createdFiles);
      for (const auto& f : chosenFiles) deleteFile(f); // if (!fs::remove(f)) throw std::runtime_error("File: " + f.string() + " Does Not Exist");
      return *this;
    }
    //!  Generate Value(s)
    template<typename T>
    T generate(size_t minValue, std::optional<const char> startingValue = std::nullopt,
                                std::optional<const char> endingValue = std::nullopt)  {
     static_assert(std::is_same_v<T, std::string>, "❌ ERROR: This Overload Is For Strings (std::string) Only");
     return generate<T, size_t>(minValue, minValue, startingValue, endingValue);
    }
    template<typename T, typename ARG = T>
    T generate(ARG minValue = std::numeric_limits<ARG>::min(), 
               ARG maxValue = std::numeric_limits<ARG>::max(),
               std::optional<const char> startingValue = std::nullopt,
               std::optional<const char> endingValue = std::nullopt)  {
      if (minValue > maxValue) std::swap(minValue, maxValue);
      if      constexpr (std::is_arithmetic_v<T>) return generateNumericType<T>(minValue, maxValue);
      else if constexpr (std::is_same_v<T, std::string>) {
        if (minValue < 0 || maxValue < 0)    throw std::runtime_error("String Length Cannot Be Negative Or 0");
        if (maxValue == std::numeric_limits<ARG>::max()) maxValue = minValue;
        std::string construct = ""; const size_t length = generateNumericType(minValue, maxValue);
        if (startingValue && endingValue)        construct = generateString(length, *startingValue, *endingValue);
        else if (startingValue && !endingValue)  construct = generateString(length, *startingValue);
        else                                     construct = generateString(length);

        if (!construct.empty()) return construct;
        else throw std::runtime_error("String Somehow Empty After Generation");
      }
      else throw std::runtime_error("Passed Type '" + std::string(typeid(T).name()) + "' Is Not Currently Supported");
    }
    //! Input/Output
    template<typename T>
    Generator& writeValues(size_t minValue, std::optional<const char> startingValue = std::nullopt,
                                            std::optional<const char> endingValue = std::nullopt,
                                            std::optional<fs::path> fileToWriteTo = std::nullopt)  {
     static_assert(std::is_same_v<T, std::string>, "❌ ERROR: This Overload Is For Strings (std::string) Only");
     return writeValues<T, size_t>(minValue, minValue, startingValue, endingValue, fileToWriteTo);
    }
    template<typename T, typename ARG = T>
    Generator& writeValues(ARG minValue = std::numeric_limits<ARG>::min(), 
                           ARG maxValue = std::numeric_limits<ARG>::max(),
                           std::optional<const char> startingValue = std::nullopt,
                           std::optional<const char> endingValue = std::nullopt,
                           std::optional<fs::path> fileToWriteTo = std::nullopt) {
      const auto& chosenFile = (fileToWriteTo ? *fileToWriteTo : currentFile); 
      std::ofstream fileContent(chosenFile); if (!fileContent.is_open()) throw std::runtime_error("Could Not Open File To Write In");
      try {
        for (size_t i = 0; i < generatedAmount; ++i)
          fileContent << generate<T, ARG>(minValue, maxValue, startingValue, endingValue) 
                      << ((i == generatedAmount - 1) ? "" : "\n");
      } catch (const std::runtime_error& e) { fileContent.close(); throw e; }
      fileContent.close(); lastTypeWritten = typeid(T);
      if (!createdFiles.empty() && [&] {
        for (const auto& f : createdFiles) if (f == chosenFile) return false;
        return true;
      }())  createdFiles.push_back(chosenFile);
      else  createdFiles.push_back(chosenFile);
      return *this;
    }
    std::vector<std::any> readValues(std::optional<fs::path> fileToRead = std::nullopt) {
      const auto& chosenFile = (fileToRead ? *fileToRead : currentFile);
      if (lastTypeWritten == typeid(std::nullptr_t))                     throw std::runtime_error("Unable To Infer Type");
      if (!fs::exists(chosenFile))                                       throw std::runtime_error("File: " + chosenFile.string() + " Does Not Exist");
      std::ifstream fileContent(chosenFile); if (!fileContent.is_open()) throw std::runtime_error("Could Not Open File To Read From");
      std::vector<std::any> collected = {};

      if (lastTypeWritten == typeid(std::string))                     {
        std::string temp; 
        while (getline(fileContent, temp)) collected.push_back(temp);
      }
      else if (lastTypeWritten == typeid(bool))                       {
        bool temp; 
        while (fileContent >> temp) collected.push_back(temp);
      }
      else if (lastTypeWritten == typeid(char))                       {
        // int temp;
        char temp; 
        while (fileContent >> temp) collected.push_back(static_cast<char>(temp));
      }
      else if (lastTypeWritten == typeid(signed char))                {
        // int temp;
        signed char temp; 
        while (fileContent >> temp) collected.push_back(static_cast<signed char>(temp));
      }
      else if (lastTypeWritten == typeid(unsigned char))              {
        // int temp;
        unsigned char temp; 
        while (fileContent >> temp) collected.push_back(static_cast<unsigned char>(temp));
      }
      else if (lastTypeWritten == typeid(short))                      {
        short temp; 
        while (fileContent >> temp) collected.push_back(temp);
      }
      else if (lastTypeWritten == typeid(unsigned short))             {
        unsigned short temp; 
        while (fileContent >> temp) collected.push_back(temp);
      }
      else if (lastTypeWritten == typeid(int))                        {
        int temp; 
        while (fileContent >> temp) collected.push_back(temp);
      }
      else if (lastTypeWritten == typeid(unsigned))                   {
        unsigned temp; 
        while (fileContent >> temp) collected.push_back(temp);
      }
      else if (lastTypeWritten == typeid(long))                       {
        long temp; 
        while (fileContent >> temp) collected.push_back(temp);
      }
      else if (lastTypeWritten == typeid(unsigned long))              {
        unsigned long temp; 
        while (fileContent >> temp) collected.push_back(temp);
      }
      else if (lastTypeWritten == typeid(long long))                  {
        long long temp; 
        while (fileContent >> temp) collected.push_back(temp);
      }
      else if (lastTypeWritten == typeid(unsigned long long))         {
        unsigned long long temp; 
        while (fileContent >> temp) collected.push_back(temp);
      }
      else if (lastTypeWritten == typeid(float))                      {
        float temp; 
        while (fileContent >> temp) collected.push_back(temp);
      }
      else if (lastTypeWritten == typeid(double))                     {
        double temp; 
        while (fileContent >> temp) collected.push_back(temp);
      }
      else if (lastTypeWritten == typeid(long double))                {
        long double temp; 
        while (fileContent >> temp) collected.push_back(temp);
      }
      else                                                         {
        fileContent.close(); 
        throw std::runtime_error("Implicit Reading For '" + std::string(lastTypeWritten.name()) + "' Is Not Currently Supported");
      }

      fileContent.close();
      return collected;
    }
    template<typename T> std::vector<T> readValues(std::optional<fs::path> fileToRead = std::nullopt) {
      const auto& chosenFile = (fileToRead ? *fileToRead : currentFile);
      if (!fs::exists(chosenFile))                                       throw std::runtime_error("File: " + chosenFile.string() + " Does Not Exist");
      std::ifstream fileContent(chosenFile); if (!fileContent.is_open()) throw std::runtime_error("Could Not Open File To Read From");
      std::vector<T> collected = {};

      if      constexpr (std::is_same_v<T, char> || std::is_same_v<T, signed char> || std::is_same_v<T, unsigned char>) {
        int temp; while (fileContent >> temp) collected.push_back(static_cast<T>(temp));
      }
      else if constexpr (std::is_same_v<T, std::string>) {
        std::string temp; while (getline(fileContent, temp)) collected.push_back(temp);
      }
      else if constexpr (std::is_arithmetic_v<T>) {
        T temp; while (fileContent >> temp) collected.push_back(temp);
      }
      else {
        fileContent.close(); 
        throw std::runtime_error("Passed Type '" + std::string(typeid(T).name()) + "' Is Not Currently Supported");
      }
      
      fileContent.close();
      return collected;
    }
};

inline Generator& gen = Generator::getInstance();

#endif

/*
 * =====================================================================================
 *
 *                                  USAGE EXAMPLE
 *
 * =====================================================================================
 
#include ".functions/random.hpp" // <-- Assuming you replace random.hpp with this content
#include ".functions/outputs.hpp" // <-- Required for the `cout << vector` functionality
#include <iostream>

int main() {
    ? The .readValues() call now returns a `std::vector<std::any>`.
    ? The custom `operator<<` in `outputs.hpp` knows how to print this vector,
    ? so you can still use `std::cout << gen.readValues()` directly and it will work.
    
   ! std::cout << "--- Implicit Reading (Strings) ---" << std::endl;
              << gen.setFile("strings").setAmount(5).writeValues<std::string>(10, 10, ' ', 'z').readValues() << std::endl;
   !          << "--- Implicit Reading (Doubles) ---" << std::endl;
              << gen.setFile("reals").setAmount(10).writeValues<double>(-100.0, 100.0).readValues() << std::endl;
   !          << "--- Implicit Reading (Bools) ---" << std::endl;
              << gen.setFile("bools").writeValues<bool>().readValues() << std::endl;

     ? You can also still call the templated version explicitly if you need a typed vector
    std::cout << "--- Explicit Reading (vector<int>) ---" << std::endl;
    gen.writeValues<int>(0, 10);
    std::vector<int> myInts = gen.readValues<int>();
    for(int val : myInts) {
        std::cout << "Explicit int: " << val << std::endl;
    }

    return 0;
}

 * =====================================================================================
 */
