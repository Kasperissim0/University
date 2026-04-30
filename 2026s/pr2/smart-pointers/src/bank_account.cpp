#include "bank_account.hpp"
#include "bank_customer.hpp"
#include "bank_customer.cpp"

unsigned Account::nextIdentifier = 0;

bool Account::share_account(const std::shared_ptr<Customer> &newOwner) noexcept {
  for (const auto &[ownerID, owner] : this->owners)
    if (ownerID == newOwner->get_id()) return false;

  this->owners[newOwner->get_id()] = newOwner;
  return true;
}
inline std::ostream& operator<<(std::ostream &output, const Account &account) {
  const auto formatOwnerList = [&](){
    std::string list;
    for (const auto &[ownerID, owner] : account.get_owners())
      list += owner.lock()->print() + ", "; // TODO do not give out last comma
    return list;
  };
  return output << std::format("[{}, {}, {}, {}, {{{}}}, {}]", account.get_name(), 
                                                                    account.additional_output(), 
                                                                    account.get_balance(), 
                                                                    account.get_dispo(), 
                                                                    formatOwnerList(),
                                                                    account.owner_count());
}