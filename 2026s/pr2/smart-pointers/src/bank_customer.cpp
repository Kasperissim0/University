#include "bank_customer.hpp"
#include "bank_account.hpp"

unsigned Customer::nextIdentifier = 0;

[[nodiscard]] constexpr auto Customer::total_balance() const noexcept {
  return [&]{
    int sum = 0; 
    for (const auto &[id, account] : this->accounts)
      sum += account->get_balance();
    return sum;
  }();
}
[[nodiscard]] constexpr auto Customer::print() const noexcept {
  return static_cast<std::string>((std::format("[{}, {}]", this->name, this->total_balance())));
}
auto Customer::create_account(const std::string &accountName, const int &dispo, const int &balance, const Account_Type &type = Account_Type::STANDARD, const int &fee = 0) {
  std::unique_ptr<Account> ptr;
  switch (type) {
    break; case Account_Type::STANDARD: ptr = std::make_unique<Standard_Account>(accountName, dispo, balance, this->getPtr());  // std::make_shared<Customer>(*this)); //? why is this wrong?
    break; case Account_Type::SPECIAL:  ptr = std::make_unique<Special_Account> (accountName, dispo, balance, this->getPtr() , fee); // std::make_shared<Customer>(*this), fee); //? why is this wrong?
    break; default: throw std::runtime_error(std::format("Invalid Account Type Passed: {}", enumToString(type)));
  }
  accounts[ptr->get_id()] = std::move(ptr);
  return ptr->get_id(); // is this undefined?
}
inline std::ostream& operator<<(std::ostream &output, const Customer &customer) {
  const auto formatAccountList = [&](){
    std::string list;
    for (const auto &[accountID, account] : customer.accounts)
      list += std::format("[{}, {}]", account->get_name(), account->owner_count()) + ", "; // TODO do not give out last comma
    return list;
  };
  return output << std::format("[{}, {{{}}}, {}]", customer.name, formatAccountList(), customer.total_balance());
}