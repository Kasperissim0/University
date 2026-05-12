#include "bank_customer.hpp"
#include "bank_account.hpp"
#include <format>
#include <numeric>
#include <stdexcept>

unsigned Customer::nextIdentifier = 0;

Customer::Customer(const std::string &name) : identifier{nextIdentifier++} {
  if (name.empty()) --nextIdentifier, throw std::runtime_error(std::format("Name Cannot Be Empty"));
  this->name = name;
}
int Customer::total_balance() const noexcept {
  return std::accumulate(this->accounts.begin(), this->accounts.end(), 0, [&](auto&& sum, const auto& elem){
    const auto& [id, account] = elem;
    return sum + account->get_balance();
  });
}
auto Customer::output() const noexcept -> std::string {
  const auto formatAccountList = [&](){
      std::string list; bool addComma = false;
      for (const auto &[accountID, account] : this->get_accounts()) {
        if (addComma) list += ", ";
        list += std::format("[{}, {}]", account->get_name(), account->owner_count());
        if (!addComma) addComma = true;
      } return list;
    };
    return std::format("[{}, {{{}}}, {}]", this->get_name(), formatAccountList(), this->total_balance());
}
decltype(Customer::identifier) Customer::create_account(const std::string &accountName, const int &dispo, const int &balance, const Account_Type &type, const int &fee) {
  std::shared_ptr<Account> ptr;
  switch (type) {
    break; case Account_Type::STANDARD: ptr = std::make_shared<Standard_Account>(accountName, dispo, balance, this->getPtr());  // std::make_shared<Customer>(*this)); //? why is this wrong?
    break; case Account_Type::SPECIAL:  ptr = std::make_shared<Special_Account> (accountName, dispo, balance, this->getPtr() , fee); // std::make_shared<Customer>(*this), fee); //? why is this wrong?
    // break; default: throw std::runtime_error(std::format("Invalid Account Type Passed: {}", enumToString(type)));
  }
  const auto &finalID = ptr->get_id();
  this->accounts[finalID] = std::move(ptr);
  return finalID;
}
bool Customer::share_account(const unsigned &accountID, std::shared_ptr<Customer> &newOwner) {
  const auto accountIterator = this->accounts.find(accountID); if (accountIterator == this->accounts.end()) return false;
  return accountIterator->second->share_account(newOwner);
}
bool Customer::transfer(const int &amount, const unsigned &sourceID, const std::shared_ptr<Customer> &target, const unsigned &targetID) {
  if (sourceID == targetID) throw std::runtime_error("Transfer From Account To Itself Makes No Sense");
  const auto sourceIterator = this->accounts.find(sourceID);   if (sourceIterator == this->accounts.end())   return false;
  const auto targetIterator = target->accounts.find(targetID); if (targetIterator == target->accounts.end()) return false;

  try { 
    sourceIterator->second->withdraw(amount);
    targetIterator->second->deposit(amount);
    return true;
  } catch (...) { return false; }
}
std::ostream& operator<<(std::ostream &output, const Customer &customer) {
  return output << customer.output();
}