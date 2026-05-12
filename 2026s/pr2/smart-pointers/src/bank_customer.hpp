#ifndef BANK_CUSTOMER
#define BANK_CUSTOMER
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
    class Customer : public std::enable_shared_from_this<Customer> {
        //§ Class Variables
          static unsigned nextIdentifier;

          const unsigned  identifier      { 0 };
          std::string     name;
          std::map<unsigned, std::shared_ptr<Account>> accounts;
        //.
        public:
          //§ (Con/De)structors
            explicit Customer(const std::string &name);
          //.
          //§ Getters
            [[nodiscard]] int total_balance()  const noexcept;
            [[nodiscard]] std::string output() const noexcept;
            GETTER_CUSTOM(identifier, id)
            SETTER_CUSTOM(identifier, id)
            GETTER(name) GETTER(accounts)
            constexpr auto& get_accounts() noexcept {
              return this->accounts;
            }
            auto getPtr() {
              return shared_from_this();
            }
            auto getPtr() const {
              return shared_from_this();
            }
          //.
          //§ Methods
            decltype(identifier) create_account(const std::string&, const int&, const int&,   const Account_Type& = Account_Type::STANDARD, const int& = 0);
            bool share_account(const unsigned&, std::shared_ptr<Customer>&);
            bool transfer(const int&, const unsigned&, const std::shared_ptr<Customer>&, const unsigned&);
          //.
    };
    std::ostream& operator<<(std::ostream& /*output*/, const Customer& /*customer*/);
#endif