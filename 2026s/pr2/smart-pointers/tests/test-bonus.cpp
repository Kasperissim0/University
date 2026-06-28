#include <iostream>
#include <memory>
#include <stdexcept>
#include <exception>
#include <string>

#include "bank_account.h"
#include "bank_customer.h"


/*
  DESIGN CHOICE: Multiple Inheritance with Virtual Base (Diamond)

  - Nested generalization: rejected — trait order is fixed in the inheritance chain; types are not independently reusable or freely composable.
  - Decorator:             rejected — requires all Account methods to be virtual and adds runtime overhead for no gain here.
  - Bridge:                rejected — would require a Account refactor and manual delegation boilerplate we get for free from the base class.

  Multiple inheritance with virtual bases fits naturally: Foreign_Currency_Account and Business_Account are both genuinely "is-a Account", 
  virtual inheritance  collapses the diamond into a single shared subobject, and AccountConfig absorbs the constructor forwarding overhead.

  NOTE: Fees in Foreign_Business_Account are calculated on the converted (foreign 
  currency) amount — the account operates in that currency, so fees are denominated 
  in it. The spec is silent on this; this is the most internally consistent choice.
*/
const static auto                   DEFAULT_CUSTOMER = std::make_shared<Customer>("Bob");
const static Account::AccountConfig DEFAULT_CONFIGURATION {"Mr. Moneybags", 100, 1000, DEFAULT_CUSTOMER};

template <typename T, typename... Args>
std::shared_ptr<T> create(Args&&... args) {
    return std::make_shared<T>(DEFAULT_CONFIGURATION, std::forward<Args>(args)...);
}

int main() {
    int failedCount = 0;

    auto expectThrow = [&failedCount](const std::string &label, const auto &fn) {
        try { fn(); std::cerr << "FAIL (No throw): " << label << "\n"; failedCount++; } 
        catch (const std::runtime_error &) {}
    };

    auto expectBalance = [&failedCount](const std::string &label, const std::shared_ptr<Account>& acc, int expected) {
        if (acc->get_balance() != expected) {
            std::cerr << "FAIL (Math): " << label << " | Expected " << expected << " got " << acc->get_balance() << "\n";
            failedCount++;
        }
    };

    try {
        // Edge Cases: Constructors
        expectThrow("Foreign Zero Rate", [&] { create<Foreign_Currency_Account>("GBP", "£", 0.0); });
        expectThrow("Foreign Negative Rate", [&] { create<Foreign_Currency_Account>("GBP", "£", -1.0); });
        expectThrow("Business Zero Fee", [&] { create<Business_Account>(0.0); });
        
        // Edge Cases: Special Account (using 'make_shared' since i was too lazy to refactor this constructor ¯\ _(ツ)_ /¯)
        auto specialAccount = std::make_shared<Special_Account>("Special", 100, 1000, DEFAULT_CUSTOMER, 10);
        expectThrow("Special Negative Withdraw Exploit", [&] { specialAccount->withdraw(-5); });

        // Functionality: Foreign Account (rate: 0.85 — amounts converted EUR → GBP via truncating int cast)
        auto foreignAccount = create<Foreign_Currency_Account>("GBP", "£", 0.85);
        foreignAccount->deposit(100); // 1000 + floor(100 * 0.85) = 1000 + 85  = 1085
        expectBalance("Foreign Deposit", foreignAccount, 1085);
        foreignAccount->withdraw(50); // 1085 - floor(50  * 0.85) = 1085 - 42  = 1043
        expectBalance("Foreign Withdraw", foreignAccount, 1043);

        // Functionality: Business Account (fee: 5% of transaction amount)
        auto businessAccount = create<Business_Account>(0.05);
        businessAccount->deposit(100); // 1000 + (100 - floor(100 * 0.05)) = 1000 + 95 = 1095
        expectBalance("Business Deposit", businessAccount, 1095);
        businessAccount->withdraw(50); // 1095 - (50  + floor(50  * 0.05)) = 1095 - 52 = 1043
        expectBalance("Business Withdraw", businessAccount, 1043);

        // Functionality: Foreign Business Account (rate: 0.85, fee: 5%)
        // Fee is applied on the converted (foreign currency) amount, not the original EUR amount.
        auto combinedAccount = create<Foreign_Business_Account>("GBP", "£", 0.85, 0.05);
        combinedAccount->deposit(100); // converted = floor(100 * 0.85) = 85; net = 85 - floor(85 * 0.05) = 85 - 4 = 81; 1000 + 81 = 1081
        expectBalance("Combined Deposit", combinedAccount, 1081);
        combinedAccount->withdraw(50); // converted = floor(50  * 0.85) = 42; net = 42 + floor(42 * 0.05) = 42 + 2 = 44; 1081 - 44 = 1037
        expectBalance("Combined Withdraw", combinedAccount, 1037);

    } catch (const std::exception& error) {
        std::cerr << "FATAL UNEXPECTED ERROR: " << error.what() << "\n";
        return 1;
    }

    if (failedCount == 0) {
        std::cout << "OK\n";
        return 0;
    }
    
    return 1;
}