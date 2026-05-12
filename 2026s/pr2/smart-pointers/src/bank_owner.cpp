#include "bank_owner.hpp"
#include <stdexcept>
#include <utility>
#include <format>

Bank_Owner::Bank_Owner(const std::string &name) {
  if (name.empty()) 
    throw std::runtime_error(std::format("Name Cannot Be Empty"));
  this->name = name;
}
decltype(Bank_Owner::bank->get_customers()) Bank_Owner::get_customers() const {
  if (!this->bank) throw std::runtime_error("No Bank Present");
  return this->bank->get_customers();
}
void Bank_Owner::create_customer(const std::string &name, const std::string &accountName, const int &dispo, const int &balance, const Account_Type &type, const int &fee) {
  if (!bank) throw std::runtime_error("No Bank Avaliable");
  this->bank->create_customer(name, accountName, dispo, balance, type, fee);
}
bool Bank_Owner::create_bank(const std::string &name) {
  return (!(this->bank) and (this->bank = std::make_unique<Bank>(name)));
}
bool Bank_Owner::transfer_bank(Bank_Owner &target) {
  return ((this->bank and !target.bank) and (static_cast<bool>(target.bank = std::move(this->bank))));
}
std::ostream& operator<<(std::ostream &output, const Bank_Owner &owner) {
                        output << "[" << owner.get_name();
  if (owner.get_bank()) output << ", " << *owner.get_bank();
  return                output << "]";
}