#include "bank_account.h"
#include "bank_customer.h"
#include <string>
#include <stdexcept>
#include <numeric>

static void bam() {
  throw std::runtime_error("oops");
}

unsigned Account::nextIdentifier = 0;
Account::Account(const std::string &name, const int &dispo, const int &balance, const std::shared_ptr<Customer> &owner) : identifier{nextIdentifier++} {
  if (name.empty()) 
    --nextIdentifier, bam();
  if (dispo <= 0 or dispo >= 10'000) 
    --nextIdentifier, bam();
  if (balance < -dispo) 
    --nextIdentifier, bam();
  if (!owner) 
    --nextIdentifier, bam();

  this->name = name;
  this->dispo = dispo;
  this->balance = balance;
  this->owners[owner->get_id()] = owner; // std::weak_ptr<Customer>(owner);
} Account::~Account() = default;
auto Account::owner_count() const noexcept -> size_t {
  return std::accumulate(owners.begin(), owners.end(), static_cast<size_t>(0), [&](auto&& sum, const auto& elem) {
    return sum + static_cast<size_t>(elem.second.expired() ? 0 : 1);
  });
}
int Account::withdraw(const int &amount) {
  if (amount <= 0 or ((this->balance - amount) < (-(this->dispo)))) bam();
  return this->balance -= amount;
}
int Account::deposit(const int &amount) {
  if (amount <= 0) bam();
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
  if ((this->owners.find(ownerID) == this->owners.end()) or (this->owners.size() == 1)) return false;
  if (auto customer = this->owners.at(ownerID).lock(); customer) {
    customer->get_accounts().erase(this->identifier);
    this->owners.erase(ownerID);
    return true;
  } return false;
}
std::string Standard_Account::additional_output() const {
  return "Standard";
}
std::string Special_Account::additional_output() const {
  return ("Special, " + std::to_string(fee));;
}
Special_Account::Special_Account(const std::string &name, const int &dispo, const int &balance, const std::shared_ptr<Customer> &owner, const int &fee) 
  : Account(name, dispo, balance, owner) {
  if (fee <= 0) bam();
  this->fee = fee;
}
int Special_Account::withdraw(const int &amount) {
  const auto totalWithdrawalAmount = amount + this->fee;
  if ((this->balance - totalWithdrawalAmount) < (-(this->dispo)) or amount <= 0) bam();
  return this->balance -= totalWithdrawalAmount;
}
// std::string enumToString (const Account_Type &type) {
//   switch (type) {
//     break; case Account_Type::STANDARD: return "Standard";
//     break; case Account_Type::SPECIAL:  return "Special";
//     break; default: bam();
//   }
// }
std::ostream& operator<<(std::ostream& output, const Account_Type &type) {
  switch (type) {
    break; case Account_Type::STANDARD: return output << "Standard";
    break; case Account_Type::SPECIAL:  return output << "Special";
    break; default: bam();
  }
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