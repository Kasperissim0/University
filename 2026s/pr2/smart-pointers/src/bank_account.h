#ifndef BANK_ACCOUNT
#define BANK_ACCOUNT
  //§ Utilities
    //§ Includes
      #include <cstddef>
      #include <ostream>
      #include <string>
      #include <map>
      #include <memory>
    //.
    //§ Helpers
      class Customer;
      enum class Account_Type : unsigned char { STANDARD, SPECIAL };
      // constexpr std::string enumToString (const Account_Type &type);
      std::ostream& operator<<(std::ostream&, const Account_Type&);
    //.
  //.
  class Account : public std::enable_shared_from_this<Account> {
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
      struct AccountConfig {
          std::string name;
          int dispo { 0 }, balance { 0 };
          std::shared_ptr<Customer> owner = nullptr;
      };
      //§ (Con/De)structors
        Account(const std::string&, const int, const int, const std::shared_ptr<Customer>&);
        explicit Account(const AccountConfig&);
        virtual ~Account() = default;
      //.
      //§ Getters
        [[nodiscard]] auto owner_count() const noexcept -> size_t;
        [[nodiscard]] const constexpr auto &get_id() const noexcept {
          return this->identifier;
        }
        [[nodiscard]] const constexpr auto &get_balance() const noexcept {
          return this->balance;
        }
        [[nodiscard]] const constexpr auto &get_dispo() const noexcept {
          return this->dispo;
        }
        [[nodiscard]] const constexpr auto &get_name() const noexcept {
          return this->name;
        }
        [[nodiscard]] const constexpr auto &get_owners() const noexcept {
          return this->owners;
        }
        auto getPtr() {
            return shared_from_this();
        }
        auto getPtr() const {
          return shared_from_this();
        }
      //.
      //§ Methods
        [[nodiscard]] virtual std::string additional_output() const = 0;
        virtual int withdraw(const int);
        virtual int deposit(const int);
        bool share_account(const std::shared_ptr<Customer>&);
        bool remove_owner(const unsigned&);
      //.
  };
  //§ Derived
    struct Standard_Account : public Account {
      using Account::Account;
      ~Standard_Account() override = default;
      [[nodiscard]] std::string additional_output() const override;
    };
    class Special_Account : public Account {
        int fee { 0 };
      public:
        Special_Account(const std::string&, const int, const int, const std::shared_ptr<Customer>&, const int);
        ~Special_Account() override = default;
        [[nodiscard]] std::string additional_output() const override;
        int withdraw(const int) override;
    };
    class Foreign_Currency_Account : virtual public Account {
      protected:
        std::string currency, currencySymbol;
        double exchangeRate { 0 };
        [[nodiscard]] int convertCurrency(const int &amount) const { return static_cast<int>(amount * this->exchangeRate); }
      public:
        Foreign_Currency_Account(const AccountConfig&, const std::string&, const std::string&, const double);
        ~Foreign_Currency_Account() override = default;
         int deposit (const int) override;
         int withdraw(const int) override;
         [[nodiscard]] std::string additional_output() const override;
         
    };
    class Business_Account : virtual public Account {
      protected:
        double percentage { 0 };
        [[nodiscard]] int calculateFeeFor(const int &amount) const { return static_cast<int>(amount * this->percentage); }
      public:
        Business_Account(const AccountConfig&, const double);
        ~Business_Account() override = default;
        int deposit (const int) override;
        int withdraw(const int) override;
        [[nodiscard]] std::string additional_output() const override;
        
    };
    struct Foreign_Business_Account : public Foreign_Currency_Account, public Business_Account {
      Foreign_Business_Account(const AccountConfig&, const std::string&, const std::string&, const double, const double);
      ~Foreign_Business_Account() override = default;
      int deposit (const int) override;
      int withdraw(const int) override;
      [[nodiscard]] std::string additional_output() const override;
      
    };
  //.
  std::ostream& operator<<(std::ostream&, const Account&);
#endif