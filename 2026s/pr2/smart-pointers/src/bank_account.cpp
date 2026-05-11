#include "bank_account.hpp"
#include "bank_customer.hpp"
#include <format>
#include <stdexcept>
#include <numeric>

unsigned Account::nextIdentifier = 0;
Account::Account(const std::string &name, const int &dispo, const int &balance, const std::shared_ptr<Customer> &owner) : identifier{nextIdentifier++} {
  if (name.empty()) 
    --nextIdentifier, throw std::runtime_error(std::format("Name Cannot Be Empty"));
  if (dispo <= 0 or dispo >= 10'000) 
    --nextIdentifier, throw std::runtime_error(std::format("Dispo Not Within Valid Range: {}", dispo));
  if (balance < -dispo) 
    --nextIdentifier, throw std::runtime_error(std::format("Balance ({}) Is Smaller Than Dispo ({}): ", balance, dispo));
  if (!owner) 
    --nextIdentifier, throw std::runtime_error(std::format("Owner Cannot Be Empty"));

  this->name = name;
  this->dispo = dispo;
  this->balance = balance;
  this->owners[owner->get_id()] = owner; // std::weak_ptr<Customer>(owner);
} Account::~Account() = default;
[[nodiscard]] auto Account::owner_count() const noexcept -> size_t {
  return std::accumulate(owners.begin(), owners.end(), static_cast<size_t>(0), [&](auto&& sum, const auto& elem) {
    return sum + static_cast<size_t>(elem.second.expired() ? 0 : 1);
  });
}
int Account::withdraw(const int &amount) {
  if (amount <= 0 or ((this->balance - amount) < (-(this->dispo)))) 
    throw std::runtime_error(std::format("Attempting To Withdraw Invalid Amount: {}", amount));
  return this->balance -= amount;
}
int Account::deposit(const int &amount) {
  if (amount <= 0) throw std::runtime_error(std::format("Attempting To Deposit Invalid Amount: {}", amount));
  this->balance += amount;
  return this->balance;
}
bool Account::share_account(std::shared_ptr<Customer> &newOwner) noexcept {
  for (const auto &[ownerID, owner] : this->owners)
    if (ownerID == newOwner->get_id()) return false;

  this->owners.insert_or_assign(newOwner->get_id(), newOwner);
  newOwner->get_accounts().insert_or_assign(this->get_id(), this->getPtr());
  return true;
}
bool Account::remove_owner(const unsigned &ownerID) {
  if (!(this->owners.contains(ownerID)) or (this->owners.size() == 1)) return false;
  if (auto customer = this->owners.at(ownerID).lock(); customer) {
    customer->get_accounts().erase(this->identifier);
    this->owners.erase(ownerID);
    return true;
  } return false;
}
[[nodiscard]] std::string Standard_Account::additional_output() const {
  return "Standard";
}
[[nodiscard]] std::string Special_Account::additional_output() const {
  return std::format("Special, {}", fee);
}
Special_Account::Special_Account(const std::string &name, const int &dispo, const int &balance, const std::shared_ptr<Customer> &owner, const int &fee) 
  : Account(name, dispo, balance, owner) {
  if (fee <= 0)
    throw std::runtime_error(std::format("Fee Cannot Be Negative Or Zero: {}", fee));
  this->fee = fee;
}
int Special_Account::withdraw(const int &amount) {
  const auto totalWithdrawalAmount = amount + this->fee;
  if ((this->balance - totalWithdrawalAmount) < (-(this->dispo)) or amount <= 0) 
    throw std::runtime_error(std::format("Attempting To Withdraw Invalid Amount: {}", amount));
  return this->balance -= totalWithdrawalAmount;
}
constexpr std::string enumToString (const Account_Type &type) {
  switch (type) {
    break; case Account_Type::STANDARD: return "Standard";
    break; case Account_Type::SPECIAL:  return "Special";
    break; default: throw std::runtime_error(std::format("Invalid Account Type Passed: {}", static_cast<size_t>(type)));
  }
}
std::ostream& operator<<(std::ostream& output, const Account_Type &type) {
  return output << enumToString(type);
}
std::ostream& operator<<(std::ostream &output, const Account &account) {
  const auto formatOwnerList = [&](){
    std::string list; bool addComma = true;
    for (const auto &[ownerID, ownerPtr] : account.get_owners()) {
      if (auto owner = ownerPtr.lock(); owner) {
        if (!addComma) list += ", ";
        list += owner->print();
        if (addComma) addComma = false;
      }
    }
    return list;
  };
  return output << std::format("[{}, {}, {}, {}, {{{}}}, {}]", account.get_name(), account.additional_output(), 
                                                                    account.get_balance(), account.get_dispo(), 
                                                                    formatOwnerList(), account.owner_count());
}