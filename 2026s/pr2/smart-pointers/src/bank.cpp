#include "bank.hpp"
#include <stdexcept>
#include <utility>
#include <format>

Bank::Bank(const std::string &name) {
  if (name.empty())  throw std::runtime_error(std::format("Name Cannot Be Empty"));
  this->name = name;
}
void Bank::create_customer(const std::string &name, const std::string &accountName, const int &dispo, const int &balance, const Account_Type &type, const int &fee) {
  auto ptr = std::make_shared<Customer>(name); ptr->create_account(accountName, dispo, balance, type, fee);
  this->customers.insert_or_assign(ptr->get_id(), std::move(ptr));
}
std::ostream& operator<<(std::ostream &output, const Bank &bank) {
  const auto formatCustomerList = [&](){
    std::string list; bool addComma = false;
    for (const auto &[customerID, customer] : bank.get_customers()) {
      if (addComma) list += ", ";
      list += customer->output();
      if (!addComma) addComma = true;
    } return list;
  }; return output << std::format("[{}, {{{}}}]", bank.get_name(), formatCustomerList());
}