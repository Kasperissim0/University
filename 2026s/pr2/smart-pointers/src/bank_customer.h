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
          #include "bank_account.h"
        //.
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
            [[nodiscard]] const inline constexpr auto &get_id() const noexcept {
              return this->identifier;
            }
            [[nodiscard]] const inline constexpr auto &get_name() const noexcept {
              return this->name;
            }
            [[nodiscard]] const inline constexpr auto &get_accounts() const noexcept {
              return this->accounts;
            }
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