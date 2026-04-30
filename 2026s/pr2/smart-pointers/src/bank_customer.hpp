//§ Contents
  #ifndef BANK_CUSTOMER
  #define BANK_CUSTOMER

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
  class Account;
  class Customer : std::enable_shared_from_this<Customer> {
      //§ Class Variables
        static unsigned nextIdentifier;

        const unsigned  identifier      { 0 };
        std::string     name;
        std::map<unsigned, std::shared_ptr<Account>> accounts;
      //.
      public:
        //§ (Con/De)structors
          explicit Customer(const std::string &name) : identifier{nextIdentifier++}{
            if (name.empty()) 
              throw std::runtime_error(std::format("Name Cannot Be Empty"));
            this->name = name;
          }
        //.
        //§ Getters
          [[nodiscard]] constexpr auto  total_balance() const noexcept;
          [[nodiscard]] constexpr auto  print() const noexcept;
          GETTER_CUSTOM(identifier, id)
          SETTER_CUSTOM(identifier, id)
          GETTER(name)
          GETTER(accounts)
          auto getPtr() {
            return shared_from_this();
          }
          auto getPtr() const {
            return shared_from_this();
          }
        //.
        auto create_account(const std::string &, const int &, const int &, const Account_Type &, const int &);
        bool share_account(const unsigned &accountID, const std::shared_ptr<Customer> &newOwner) {
          const auto element = this->accounts.find(accountID); if (element == this->accounts.end()) return false;
          return static_cast<bool>(newOwner->accounts.at(accountID) = element->second->getPtr());
        }
        bool transfer(const int &amount, const unsigned &sourceID, const std::shared_ptr<Customer> &target, const unsigned &targetID) {
          if (sourceID == targetID) throw std::runtime_error("Transfer From Account To Itself Makes No Sense");
          const auto sourceIterator = this->accounts.find(sourceID);   if (sourceIterator == this->accounts.end())   return false;
          const auto targetIterator = target->accounts.find(targetID); if (targetIterator == target->accounts.end()) return false;
          // if (sourceIterator->second->get_balance() < amount) return false; // TODO add check about dispo?

          sourceIterator->second->withdraw(amount);
          targetIterator->second->deposit(amount);
          return true;
        }

        friend std::ostream& operator<<(std::ostream& /*output*/, const Customer& /*customer*/);
  };

  #endif
//.