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
        #include "bank_account.hpp"
        #include "bank_customer.hpp"
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
          GETTER(name) GETTER(customers)
        //.
        void create_customer(const std::string&, const std::string&, const int&, const int&, 
                             const Account_Type& = Account_Type::STANDARD, const int& = 0);
  };
  std::ostream& operator<<(std::ostream&, const Bank&);
#endif