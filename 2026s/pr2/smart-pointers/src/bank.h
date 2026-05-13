#ifndef BANK
#define BANK

  //§ Utilities
    //§ Includes
      //§ C++
        #include <cstddef>
        #include <ostream>
        #include <string>
        #include <map>
        #include <memory>
      //.
      //§ Project
        #include "bank_account.h"
        #include "bank_customer.h"
      //.
    //.
  //.
  class Bank {
      //§ Class Variables
        std::string name;
        std::map<unsigned, std::shared_ptr<Customer>> customers;
      //.
      public:
        //§ (Con/De)structors
          explicit Bank(const std::string&);
        //.
        //§ Getters
          [[nodiscard]] const inline constexpr auto &get_name() const noexcept {
            return this->name;
          }
          [[nodiscard]] const inline constexpr auto &get_customers() const noexcept {
            return this->customers;
          }
        //.
        void create_customer(const std::string&, const std::string&, const int&, const int&, 
                             const Account_Type& = Account_Type::STANDARD, const int& = 0);
  };
  std::ostream& operator<<(std::ostream&, const Bank&);
#endif