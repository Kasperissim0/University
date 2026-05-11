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
        //§ Editors
          #define EDITOR(MEMBER) \
            [[nodiscard]] RETURN_QUALIFIERS edit_ ## MEMBER() GETTER_QUALIFIERS{ \
              return this->MEMBER; \
            }
          #define EDITOR_CUSTOM(MEMBER, NAME) \
            [[nodiscard]] RETURN_QUALIFIERS edit_ ## NAME() GETTER_QUALIFIERS{ \
              return this->MEMBER; \
            }
          #define EDITOR_FULLY_CUSTOM(MEMBER, NAME) \
            [[nodiscard]] RETURN_QUALIFIERS NAME() GETTER_QUALIFIERS{ \
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
          EDITOR(MEMBER) \
          SETTER(MEMBER) \
      //.
      #endif
    //.
    //§ Helpers
      class Customer;
      enum class Account_Type : unsigned char { STANDARD, SPECIAL };
      constexpr std::string enumToString (const Account_Type &type);
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
      //§ (Con/De)structors
        Account(const std::string&, const int&, const int&, const std::shared_ptr<Customer>&);
        virtual ~Account(); // = 0;
      //.
      //§ Getters
        [[nodiscard]] auto owner_count() const noexcept -> size_t;
        GETTER_CUSTOM(identifier, id)
        GETTER(balance) GETTER(dispo) 
        GETTER(name) GETTER(owners)
        auto getPtr() {
            return shared_from_this();
        }
        auto getPtr() const {
          return shared_from_this();
        }
      //.
      //§ Methods
        [[nodiscard]] virtual std::string additional_output() const = 0;
        virtual int withdraw(const int&);
        int deposit(const int&);
        bool share_account(std::shared_ptr<Customer>&) noexcept;
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
        int fee = 0;
      public:
      Special_Account(const std::string&, const int&, const int&, const std::shared_ptr<Customer>&, const int&);
      ~Special_Account() override = default;
      [[nodiscard]] std::string additional_output() const override;
      int withdraw(const int&) override;
    };
  //.
  std::ostream& operator<<(std::ostream&, const Account&);
#endif