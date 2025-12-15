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

std::ostream& operator<<(std::ostream& o, const std::vector<std::any>& v) {
  for (size_t i = 0; i < v.size(); ++i) {
    const auto& item = v.at(i);
    o << Color::FG::Bright::GREEN << "# " << Color::FG::Bright::RED 
      << (i + 1) << r << ": " << Color::FG::Bright::BLUE;
    
    if      (item.type() == typeid(std::string))             {
      o << std::any_cast<const std::string&>(item);
    }
    else if (item.type() == typeid(bool))                    {
      o << (std::any_cast<bool>(item) ? "true" : "false");
    }
    else if (item.type() == typeid(char))                    {
      o << "'" << std::any_cast<char>(item) << "'";
    }
    else if (item.type() == typeid(signed char))             {
      o << "'" << std::any_cast<signed char>(item) << "'";
    }
    else if (item.type() == typeid(unsigned char))           {
      o << "'" << std::any_cast<unsigned char>(item) << "'";
    }
    else if (item.type() == typeid(short))                   {
      o << std::any_cast<short>(item);
    }
    else if (item.type() == typeid(unsigned short))          {
      o << std::any_cast<unsigned short>(item);
    }
    else if (item.type() == typeid(int))                     {
      o << std::any_cast<int>(item);
    }
    else if (item.type() == typeid(unsigned))                {
      o << std::any_cast<unsigned>(item);
    }
    else if (item.type() == typeid(long))                    {
      o << std::any_cast<long>(item);
    }
    else if (item.type() == typeid(unsigned long))           {
      o << std::any_cast<unsigned long>(item);
      }
    else if (item.type() == typeid(long long))               {
      o << std::any_cast<long long>(item);
    }
    else if (item.type() == typeid(unsigned long long))      {
      o << std::any_cast<unsigned long long>(item);
    }
    else if (item.type() == typeid(float))                   {
      std::stringstream ss; ss << std::any_cast<float>(item);
      o << ss.str() << "f";
    }
    else if (item.type() == typeid(double))                  {
      std::stringstream ss; ss << std::any_cast<double>(item);
      o << ss.str();
    }
    else if (item.type() == typeid(long double))             {
      std::stringstream ss; ss << std::any_cast<long double>(item);
      o << ss.str() << "L";
    }
    else                                                     {
      o << "[unknown type]";
    }

    o << r << ((i == v.size() - 1) ? "" : "\n");
  }
  return o;
}
template<typename T> std::ostream& operator<<(std::ostream& o, const std::vector<T> v) {
  for (size_t i = 0; i < v.size(); ++i)
    o << Color::FG::Bright::GREEN << "# " << Color::FG::Bright::RED 
      << (i + 1) << r << ": " << Color::FG::Bright::BLUE << v.at(i) << r << ((i == v.size() - 1) ? "" : "\n");
  return o;
}

#endif