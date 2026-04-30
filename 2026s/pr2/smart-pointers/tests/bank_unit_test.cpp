#include "bank.h"
#include "bank_account.h"
#include "bank_customer.h"
#include "bank_owner.h"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

int main() {
  std::cout << std::boolalpha;

  auto expect_throw = [](const std::string &label, const auto &fn) {
    try {
      fn();
      std::cout << label << " false\n";
    } catch (const std::runtime_error &) {
      std::cout << label << " true\n";
    }
  };

  try {
    std::cout << "constructors\n";
    expect_throw("bank-owner-empty", [] { Bank_Owner owner{""}; });
    expect_throw("bank-empty", [] { Bank bank{""}; });
    expect_throw("customer-empty", [] { Customer customer{""}; });

    auto ctor_owner = std::make_shared<Customer>("Ctor Owner");
    expect_throw("standard-empty-name",
                 [&] { Standard_Account account{"", 50, 0, ctor_owner}; });
    expect_throw("standard-dispo-zero",
                 [&] { Standard_Account account{"Bad", 0, 0, ctor_owner}; });
    expect_throw("standard-dispo-10000",
                 [&] { Standard_Account account{"Bad", 10000, 0, ctor_owner}; });
    expect_throw("standard-balance-too-low",
                 [&] { Standard_Account account{"Bad", 50, -51, ctor_owner}; });
    expect_throw("standard-null-owner",
                 [] { Standard_Account account{"Bad", 50, 0, nullptr}; });
    expect_throw("special-fee-zero",
                 [&] { Special_Account account{"Bad", 50, 0, ctor_owner, 0}; });

    auto c0 = std::make_shared<Customer>("Id Zero");
    expect_throw("customer-empty-2", [] { Customer customer{""}; });
    auto c1 = std::make_shared<Customer>("Id One");
    std::cout << "customer-id-sequential " << (c1->get_id() == c0->get_id() + 1)
              << "\n";

    auto a0 = std::make_shared<Standard_Account>("Direct A", 100, 0, c0);
    expect_throw("standard-balance-too-low-2",
                 [&] { Standard_Account account{"Bad", 20, -21, c0}; });
    auto a1 = std::make_shared<Standard_Account>("Direct B", 100, 0, c0);
    std::cout << "account-id-sequential " << (a1->get_id() == a0->get_id() + 1)
              << "\n";

    std::cout << "account-type " << Account_Type::STANDARD << " "
              << Account_Type::SPECIAL << "\n";

    std::cout << "accounts\n";
    auto alice = std::make_shared<Customer>("Alice");
    auto bob = std::make_shared<Customer>("Bob");
    auto carol = std::make_shared<Customer>("Carol");

    const auto family_id =
        alice->create_account("Family", 500, 100, Account_Type::STANDARD);
    const auto vip_id =
        alice->create_account("VIP", 300, 1000, Account_Type::SPECIAL, 25);

    auto family = alice->get_accounts().at(family_id);
    auto vip = alice->get_accounts().at(vip_id);

    std::cout << "standard-output " << family->additional_output() << "\n";
    std::cout << "special-output " << vip->additional_output() << "\n";
    std::cout << "family-id-match " << (family->get_id() == family_id) << "\n";
    std::cout << "family-owner-count-1 " << family->owner_count() << "\n";
    std::cout << "family-share-direct " << family->share_account(bob) << "\n";
    std::cout << "bob-account-added " << bob->get_accounts().count(family_id)
              << "\n";
    std::cout << "family-share-direct-duplicate " << family->share_account(bob)
              << "\n";
    std::cout << "family-owner-count-2 " << family->owner_count() << "\n";

    auto temp = std::make_shared<Customer>("Temp");
    std::cout << "vip-share-temp " << vip->share_account(temp) << "\n";
    std::cout << "vip-owner-count-before-reset " << vip->owner_count() << "\n";
    temp = nullptr;
    std::cout << "vip-owner-count-after-reset " << vip->owner_count() << "\n";

    std::cout << "family-remove-missing " << family->remove_owner(999999) << "\n";
    std::cout << "family-remove-bob " << family->remove_owner(bob->get_id())
              << "\n";
    std::cout << "bob-account-removed " << bob->get_accounts().count(family_id)
              << "\n";
    std::cout << "family-remove-last-owner "
              << family->remove_owner(alice->get_id()) << "\n";

    expect_throw("family-withdraw-zero", [&] { family->withdraw(0); });
    std::cout << "family-withdraw-50 " << family->withdraw(50) << "\n";
    expect_throw("family-withdraw-too-much", [&] { family->withdraw(1000); });
    expect_throw("family-deposit-zero", [&] { family->deposit(0); });
    std::cout << "family-deposit-25 " << family->deposit(25) << "\n";
    expect_throw("vip-withdraw-negative", [&] { vip->withdraw(-5); });
    std::cout << "vip-withdraw-100 " << vip->withdraw(100) << "\n";
    std::cout << "family-print " << *family << "\n";
    std::cout << "vip-print " << *vip << "\n";

    std::cerr << "ERR account " << *family << "\n";
    std::cerr << "ERR customer " << *alice << "\n";

    std::cout << "customers\n";
    std::cout << "alice-name " << alice->get_name() << "\n";
    std::cout << "alice-id-positive " << (alice->get_id() > c1->get_id()) << "\n";
    std::cout << "alice-account-count " << alice->get_accounts().size() << "\n";
    std::cout << "alice-total-balance-before-share " << alice->total_balance()
              << "\n";
    std::cout << "customer-share " << alice->share_account(vip_id, carol) << "\n";
    std::cout << "customer-share-duplicate " << alice->share_account(vip_id, carol)
              << "\n";
    std::cout << "customer-share-missing " << alice->share_account(123456, carol)
              << "\n";
    std::cout << "carol-account-added " << carol->get_accounts().count(vip_id)
              << "\n";
    expect_throw("customer-transfer-same-id",
                 [&] { alice->transfer(10, vip_id, carol, vip_id); });
    std::cout << "customer-transfer-ok "
              << alice->transfer(200, family_id, carol, vip_id) << "\n";
    std::cout << "customer-transfer-missing-source "
              << alice->transfer(10, 777777, carol, vip_id) << "\n";
    std::cout << "customer-transfer-missing-target "
              << alice->transfer(10, family_id, bob, 888888) << "\n";
    std::cout << "customer-transfer-negative "
              << alice->transfer(-10, family_id, carol, vip_id) << "\n";
    std::cout << "customer-transfer-too-much "
              << alice->transfer(1000, family_id, carol, vip_id) << "\n";
    std::cout << "alice-total-balance-after-transfer " << alice->total_balance()
              << "\n";
    std::cout << "carol-total-balance " << carol->total_balance() << "\n";
    std::cout << "alice-print " << *alice << "\n";
    std::cout << "carol-print " << *carol << "\n";

    std::cout << "banks\n";
    Bank central{"Central Bank"};
    std::cout << "bank-customer-count-0 " << central.get_customers().size() << "\n";
    central.create_customer("Dora", "Dora Standard", 200, 50, Account_Type::STANDARD);
    central.create_customer("Evan", "Evan Special", 300, 400,
                            Account_Type::SPECIAL, 10);
    std::cout << "bank-customer-count-2 " << central.get_customers().size() << "\n";
    std::cout << "bank-print " << central << "\n";
    std::cerr << "ERR bank " << central << "\n";

    std::cout << "bank-owners\n";
    Bank_Owner owner_a{"Owner A"};
    Bank_Owner owner_b{"Owner B"};
    Bank_Owner owner_c{"Owner C"};
    expect_throw("owner-get-customers-no-bank", [&] { owner_a.get_customers(); });
    expect_throw("owner-create-customer-no-bank", [&] {
      owner_a.create_customer("Fail", "Fail", 100, 0, Account_Type::STANDARD);
    });
    std::cout << "owner-a-create-bank " << owner_a.create_bank("Bank A") << "\n";
    std::cout << "owner-a-create-bank-again " << owner_a.create_bank("Bank A")
              << "\n";
    owner_a.create_customer("Fred", "Fred Standard", 150, 20, Account_Type::STANDARD);
    std::cout << "owner-a-customer-count " << owner_a.get_customers().size() << "\n";
    std::cout << "owner-b-create-bank " << owner_b.create_bank("Bank B") << "\n";
    std::cout << "owner-a-transfer-bank-to-owner-b "
              << owner_a.transfer_bank(owner_b) << "\n";
    std::cout << "owner-a-transfer-bank-to-owner-c "
              << owner_a.transfer_bank(owner_c) << "\n";
    std::cout << "owner-b-transfer-bank-to-owner-c "
              << owner_b.transfer_bank(owner_c) << "\n";
    std::cout << "owner-c-customer-count " << owner_c.get_customers().size() << "\n";
    std::cout << "owner-c-transfer-bank-to-self "
              << owner_c.transfer_bank(owner_c) << "\n";
    std::cout << "owner-a-print " << owner_a << "\n";
    std::cout << "owner-b-print " << owner_b << "\n";
    std::cout << "owner-c-print " << owner_c << "\n";

    std::cerr << "ERR owner " << owner_c << "\n";
  } catch (const std::runtime_error &e) {
    std::cout << "unexpected " << e.what() << "\n";
  }
}
