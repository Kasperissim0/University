#ifndef OUTPUTS
#define OUTPUTS
#include "colors.hpp"
#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <any>

std::ostream& operator<<(std::ostream& o, const std::any a) {
    if      (a.type() == typeid(std::string))             {
      o << std::any_cast<const std::string&>(a);
    }
    else if (a.type() == typeid(bool))                    {
      o << (std::any_cast<bool>(a) ? "true" : "false");
    }
    else if (a.type() == typeid(char))                    {
      o << "'" << std::any_cast<char>(a) << "'";
    }
    else if (a.type() == typeid(signed char))             {
      o << "'" << std::any_cast<signed char>(a) << "'";
    }
    else if (a.type() == typeid(unsigned char))           {
      o << "'" << std::any_cast<unsigned char>(a) << "'";
    }
    else if (a.type() == typeid(short))                   {
      o << std::any_cast<short>(a);
    }
    else if (a.type() == typeid(unsigned short))          {
      o << std::any_cast<unsigned short>(a);
    }
    else if (a.type() == typeid(int))                     {
      o << std::any_cast<int>(a);
    }
    else if (a.type() == typeid(unsigned))                {
      o << std::any_cast<unsigned>(a);
    }
    else if (a.type() == typeid(long))                    {
      o << std::any_cast<long>(a);
    }
    else if (a.type() == typeid(unsigned long))           {
      o << std::any_cast<unsigned long>(a);
      }
    else if (a.type() == typeid(long long))               {
      o << std::any_cast<long long>(a);
    }
    else if (a.type() == typeid(unsigned long long))      {
      o << std::any_cast<unsigned long long>(a);
    }
    else if (a.type() == typeid(float))                   {
      std::stringstream ss; ss << std::any_cast<float>(a);
      o << ss.str(); // << "f";
    }
    else if (a.type() == typeid(double))                  {
      std::stringstream ss; ss << std::any_cast<double>(a);
      o << ss.str();
    }
    else if (a.type() == typeid(long double))             {
      std::stringstream ss; ss << std::any_cast<long double>(a);
      o << ss.str(); // << "L";
    }
    else throw std::runtime_error("Unknown Type Encountered - " + std::string(a.type().name()));
  return o;
}
std::ostream& operator<<(std::ostream& o, const std::vector<std::any>& v) {
  for (size_t i = 0; i < v.size(); ++i) {
    const auto& item = v.at(i);
    o << Color::FG::Bright::GREEN << "# " 
      << Color::FG::Bright::RED << (i + 1) << r << ": " 
      << Color::FG::Bright::BLUE << item 
      << r << ((i == v.size() - 1) ? "" : "\n");
  }
  return o;
}
template<typename T> std::ostream& operator<<(std::ostream& o, const std::vector<T> v) {
  bool isAChar = false;
  if (std::is_same_v<T, char> || std::is_same_v<T, signed char> || std::is_same_v<T, unsigned char>) isAChar = true;
  for (size_t i = 0; i < v.size(); ++i)
    o << Color::FG::Bright::GREEN << "# " << Color::FG::Bright::RED 
      << (i + 1) << r << ": " << Color::FG::Bright::BLUE << (isAChar ? "'" : "") << v.at(i)<< (isAChar ? "'" : "")
      << r << ((i == v.size() - 1) ? "" : "\n");
  return o;
}

#endif