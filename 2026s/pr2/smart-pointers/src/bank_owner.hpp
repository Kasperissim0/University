//§ Contents
  #ifndef BANK_OWNER
  #define BANK_OWNER

  //§ Utilities
    //§ Includes
      //§ C++
        #include <cstddef>
        #include <format>
        #include <ostream>
        #include <stdexcept>
        #include <string>
        #include <map>
        #include <memory>
        #include <utility>
      //.
      //§ Project
        #include "bank.hpp"
        // #include "bank_account.hpp"
        #include "bank_customer.hpp"
        // #include "bank_customer.cpp"
      //.
    //.
    //§ Macros
      #ifndef CUSTOM_MACROS
      #define CUSTOM_MACROS
      //§ Contents
        //§ Repetitive
          #define ARG                     auto&&
          #define GETTER_QUALIFIERS       const noexcept
          #define EXTRA                   [[nodiscard]] const
          #define RETURN_QUALIFIERS       inline constexpr auto&
          #define ASSIGN(VAR)             std::forward<decltype(VAR)>(VAR)
          #define OPTIMIZE(ORIGINAL, NEW) noexcept(noexcept((this->ORIGINAL = ASSIGN(NEW))))
        //.
        //§ Getters
          #define GETTER(MEMBER) \
            EXTRA RETURN_QUALIFIERS get_ ## MEMBER() GETTER_QUALIFIERS { \
              return this->MEMBER; \
            }
          #define GETTER_CUSTOM(MEMBER, NAME) \
            EXTRA RETURN_QUALIFIERS get_ ## NAME() GETTER_QUALIFIERS { \
              return this->MEMBER; \
            }
          #define GETTER_FULLY_CUSTOM(MEMBER, NAME) \
            EXTRA RETURN_QUALIFIERS NAME() GETTER_QUALIFIERS { \
              return this->MEMBER; \
            }
        //.
        //§ Setters
          #define SETTER(MEMBER) \
            RETURN_QUALIFIERS set_ ## MEMBER(ARG newValue) OPTIMIZE(MEMBER, newValue) { \
              return (this->MEMBER = ASSIGN(newValue)), *this; \
            }
          #define SETTER_CUSTOM(MEMBER, NAME) \
            RETURN_QUALIFIERS set_ ## NAME (ARG newValue) OPTIMIZE(MEMBER, newValue) { \
              return (this->MEMBER = ASSIGN(newValue)), *this; \
            }
          #define SETTER_FULLY_CUSTOM(MEMBER, NAME) \
            RETURN_QUALIFIERS NAME (ARG newValue) OPTIMIZE(MEMBER, newValue) { \
              return (this->MEMBER = ASSIGN(newValue)), *this; \
            }
        //.
        #define ACCESS(MEMBER) \
          GETTER(MEMBER) \
          SETTER(MEMBER) \
      //.
      #endif
    //.
  //.
  class Bank_Owner { // : std::enable_shared_from_this<Customer> {
      //§ Class Variables
        std::string           name;
        std::unique_ptr<Bank> bank;
      //.
      public:
        //§ (Con/De)structors
          explicit Bank_Owner(const std::string &name) {
            if (name.empty()) 
              throw std::runtime_error(std::format("Name Cannot Be Empty"));
            this->name = name;
          }
        //.
        //§ Getters
          GETTER(name)
          GETTER(bank)
        //.
        void create_customer(const std::string &name, const std::string &accountName, const int &dispo, const int &balance, const Account_Type &type = Account_Type::STANDARD, const int &fee = 0) {
          if (!bank) throw std::runtime_error("No Bank Avaliable");
          this->bank->create_customer(name, accountName, dispo, balance, type, fee);
        }
  };
  std::ostream& operator<<(std::ostream &output, const  Bank_Owner &owner) {
    return output << "[" << owner.get_name() << ", " << owner.get_bank() << " ]";
}
  #endif
//.