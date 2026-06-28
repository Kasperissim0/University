#include "bank_account.h"
#include "bank_customer.h"
#include <string>
#include <stdexcept>
#include <numeric>
#include <memory>
#include <sstream>
#include <iomanip>

static void bam() {
  throw std::runtime_error("oops");
}
static std::string fmt(const double digit, const int precision = 2) {
    std::ostringstream output;
    output << std::fixed << std::setprecision(precision) << digit;
    return output.str();
}

unsigned Account::nextIdentifier = 0;
Account::Account(const std::string &name, const int dispo, const int balance, 
                 const std::shared_ptr<Customer> &owner) : identifier{nextIdentifier++} {
  if (name.empty() or dispo <= 0 or dispo >= 10'000 or balance < -dispo or !owner) 
    --nextIdentifier, bam();
  this->name = name;
  this->dispo = dispo;
  this->balance = balance;
  this->owners[owner->get_id()] = owner; // std::weak_ptr<Customer>(owner);
}
Account::Account(const AccountConfig& config) : Account(config.name, config.dispo, config.balance, config.owner) {}
auto Account::owner_count() const noexcept -> size_t {
  return std::accumulate(owners.begin(), owners.end(), static_cast<size_t>(0), [&](auto&& sum, const auto& elem) {
    return sum + static_cast<size_t>(elem.second.expired() ? 0 : 1);
  });
}
int Account::withdraw(const int amount) {
  if ((amount <= 0) or ((this->balance - amount) < (-(this->dispo)))) bam();
  return this->balance -= amount;
}
int Account::deposit(const int amount) {
  if (amount <= 0) bam();
  return this->balance += amount;
}
bool Account::share_account(const std::shared_ptr<Customer> &newOwner) {
  for (const auto &[ownerID, owner] : this->owners)
    if (ownerID == newOwner->get_id()) return false;

  this->owners.insert_or_assign(newOwner->get_id(), newOwner);
  newOwner->get_accounts().insert_or_assign(this->get_id(), this->getPtr());
  return true;
}
bool Account::remove_owner(const unsigned &ownerID) {
  if ((this->owners.find(ownerID) == this->owners.end()) or (this->owners.size() == 1)) return false;
  if (auto customer = this->owners.at(ownerID).lock(); customer) {
    customer->get_accounts().erase(this->identifier);
    this->owners.erase(ownerID);
    return true;
  } return false;
}
Special_Account::Special_Account(const std::string &name, const int dispo, const int balance, const std::shared_ptr<Customer> &owner, 
                                 const int fee) : Account(name, dispo, balance, owner) {
  if (fee <= 0) bam();
  this->fee = fee;
}
int Special_Account::withdraw(const int amount) {
  if (amount <= 0) bam(); // explicit check since amount can be negative, and amount + fee makes it positive
  return Account::withdraw(amount + fee);
}
Foreign_Currency_Account::Foreign_Currency_Account(const AccountConfig &config, const std::string &currency, 
                                                   const std::string &symbol, const double rate) : Account(config) {
  if (rate <= 0.0) bam();
  this->currency = currency;
  this->currencySymbol = symbol;
  this->exchangeRate = rate;
}
int Foreign_Currency_Account::withdraw(const int amount)  {
  return Account::withdraw(convertCurrency(amount));
}
int Foreign_Currency_Account::deposit(const int amount)  {
  return Account::deposit(convertCurrency(amount));
}
Business_Account::Business_Account(const AccountConfig &config, const double percentage) : Account(config) {
  if (percentage <= 0.0) bam();
  this->percentage = percentage;  
}
int Business_Account::withdraw(const int amount)  {
  return Account::withdraw((amount + calculateFeeFor(amount)));
}
int Business_Account::deposit(const int amount)  {
  return Account::deposit((amount - calculateFeeFor(amount)));
}
Foreign_Business_Account::Foreign_Business_Account(const AccountConfig &config, const std::string &currency, const std::string &symbol,
                                                   const double rate, const double percentage) : Account(config), 
                                                   Foreign_Currency_Account(config, currency, symbol, rate), 
                                                   Business_Account(config, percentage) {}
int Foreign_Business_Account::withdraw(const int amount)  {
  return Business_Account::withdraw(convertCurrency(amount));
}
int Foreign_Business_Account::deposit(const int amount)  {
  return Business_Account::deposit(convertCurrency(amount));
}
std::string Standard_Account::additional_output() const {
  return "Standard";
}
std::string Special_Account::additional_output() const {
  return ("Special, " + std::to_string(fee));
}
std::string Foreign_Currency_Account::additional_output() const {
  return ("Foreign, " + currency + " (" + currencySymbol + ") with rate: " + fmt(exchangeRate));
}
std::string Business_Account::additional_output() const {
  return ("Business, with " + fmt(percentage) + "% fee");
}
std::string Foreign_Business_Account::additional_output() const {
  return (Foreign_Currency_Account::additional_output() + " and " + Business_Account::additional_output());
}
std::ostream& operator<<(std::ostream& output, const Account_Type &type) {
  switch (type) {
    break; case Account_Type::STANDARD: return output << "Standard";
    break; case Account_Type::SPECIAL:  return output << "Special";
    break; default: bam();
  } return output;
}
std::ostream& operator<<(std::ostream &output, const Account &account) {
  const std::string c = ", ";
  const auto formatOwnerList = [&](){
    std::string list; bool addComma = true;
    for (const auto &[ownerID, ownerPtr] : account.get_owners()) {
      if (auto owner = ownerPtr.lock(); owner) {
        if (!addComma) list += c;
        list += "[" + owner->get_name() + c + std::to_string(owner->total_balance()) + "]";
        if (addComma) addComma = false;
      }
    }
    return list;
  };
  return output << "[" << account.get_name() << c << account.additional_output() << c 
                << account.get_balance() << c  << account.get_dispo() << c 
                << "{" << formatOwnerList() << "}" << c  << account.owner_count() << "]";
}