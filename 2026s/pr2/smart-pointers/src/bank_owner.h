#ifndef BANK_OWNER
#define BANK_OWNER

  //§ Utilities
    //§ Includes
      //§ C++
        #include <cstddef>
        #include <ostream>
        #include <string>
        #include <memory>
      //.
      //§ Project
        #include "bank.h"
      //.
    //.
  //.
  class Bank_Owner {
      //§ Class Variables
        std::string           name;
        std::unique_ptr<Bank> bank;
      //.
      public:
        //§ (Con/De)structors
          explicit Bank_Owner(const std::string&);
        //.
        //§ Getters
          [[nodiscard]] const inline constexpr auto &get_name() const noexcept {
            return this->name;
          }
          [[nodiscard]] const inline constexpr auto &get_bank() const noexcept {
            return this->bank;
          }
          decltype(bank->get_customers())& get_customers() const;
        //.
        void create_customer(const std::string&, const std::string&, const int&, const int&, 
                             const Account_Type& = Account_Type::STANDARD, const int& = 0);
        bool create_bank(const std::string&);
        bool transfer_bank(Bank_Owner&);
  };
  std::ostream& operator<<(std::ostream&, const Bank_Owner&);
#endif