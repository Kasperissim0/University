//§ Contents
  #ifndef BANK_ACCOUNT
  #define BANK_ACCOUNT

  //§ Utilities
    //§ Includes
      #include <cstddef>
      #include <format>
      #include <ostream>
      #include <stdexcept>
      #include <string>
      #include <map>
      #include <memory>
      #include <utility>
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
    //§ Helpers
      class Customer;
      enum class Account_Type : unsigned char { STANDARD, SPECIAL };
      constexpr std::string enumToString (const Account_Type &type) {
        switch (type) {
          break; case Account_Type::STANDARD: return "Standard";
          break; case Account_Type::SPECIAL:  return "Special";
          break; default: throw std::runtime_error(std::format("Invalid Account Type Passed: {}", static_cast<size_t>(type)));
        }
      }
    //.
  //.
  class Account : std::enable_shared_from_this<Account> {
      //§ Class Variables
        protected:
          static unsigned nextIdentifier;

          const unsigned    identifier      { 0 };
          int               dispo           { 0 }, 
                            balance         { 0 };
          std::string       name;
          std::map<unsigned, std::weak_ptr<Customer>> owners;
      //.
    public:
      //§ (Con/De)structors
        Account(const std::string &name, const int &dispo, const int &balance, const std::shared_ptr<Customer> &owner) : identifier{nextIdentifier++} {
          if (name.empty()) 
            throw std::runtime_error(std::format("Name Cannot Be Empty"));
          if (dispo < 0 or dispo > 10'000) 
            throw std::runtime_error(std::format("Dispo Not Within Valid Range: {}", dispo));
          if (balance < -dispo) 
            throw std::runtime_error(std::format("Balance ({}) Is Smaller Than Dispo ({}): ", balance, dispo));

          this->name = name;
          this->dispo = dispo;
          this->owners[identifier] = owner; // std::weak_ptr<Customer>(owner);
        }
        virtual ~Account();
      //.
      //§ Getters
        [[nodiscard]] auto owner_count() const noexcept {
          return static_cast<unsigned>(this->owners.size());
        }
        GETTER_CUSTOM(identifier, id)
        GETTER(balance)
        GETTER(dispo)
        GETTER(name)
        GETTER(owners)
        auto getPtr() {
            return shared_from_this();
          }
        auto getPtr() const {
          return shared_from_this();
        }
      //.
      [[nodiscard]] virtual std::string additional_output() const = 0;
      virtual int withdraw(const int &amount) {
        if (amount <= 0) throw std::runtime_error(std::format("Attempting To Withdraw Invalid Amount: {}", amount));
        if ((this->balance - amount) >= (-(this->dispo))) 
          this->balance -= amount;
        return this->balance;
      }
      int deposit(const int &amount) {
        if (amount <= 0) throw std::runtime_error(std::format("Attempting To Deposit Invalid Amount: {}", amount));
        this->balance += amount;
        return this->balance;
      }
      bool share_account(const std::shared_ptr<Customer>&) noexcept;
      bool remove_owner(const unsigned &ownerID) noexcept {
        return (!this->owners.empty() and (static_cast<bool>(this->owners.erase(ownerID))));
      }
  };
  //§ Derived
    struct Standard_Account : public Account {
      using Account::Account;

      [[nodiscard]] std::string additional_output() const override {
        return "Standard";
      }
    };
    class Special_Account : public Account {
        int fee = 0;
      public:
        Special_Account(const std::string &name, const int &dispo, const int &balance, const std::shared_ptr<Customer> &owner, const int &fee) 
          : Account(name, dispo, balance, owner) {
          if (fee <= 0)
            throw std::runtime_error(std::format("Fee Cannot Be Negative Or Zero: {}", fee));
          this->fee = fee;
        }

        [[nodiscard]] std::string additional_output() const override {
          return std::format("Standard, {}", fee);
        }
        int withdraw(const int &amount) override {  if (amount <= 0) throw std::runtime_error(std::format("Attempting To Withdraw Invalid Amount: {}", amount));
          const auto totalWithdrawalAmount = amount + this->fee;
          if ((this->balance - totalWithdrawalAmount) >= (-(this->dispo))) 
            this->balance -= totalWithdrawalAmount;
          return this->balance;
      }
    };
  //.
  std::ostream& operator<<(std::ostream& /*output*/, const Account& /*account*/);
  #endif
//.