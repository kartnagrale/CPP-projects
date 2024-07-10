#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <memory>
using namespace std;

// Abstract Base Class for BankAccount
class BankAccount {
protected:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(int accNum, string accHolderName, double bal)
        : accountNumber(accNum), accountHolderName(accHolderName), balance(bal) {}

    virtual ~BankAccount() {}

    int getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolderName() const {
        return accountHolderName;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    virtual void withdraw(double amount) = 0;

    virtual void displayAccountDetails() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }
};

// Derived Class for SavingsAccount
class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(int accNum, string accHolderName, double bal, double intRate)
        : BankAccount(accNum, accHolderName, bal), interestRate(intRate) {}

    void withdraw(double amount) override {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: " << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient balance." << endl;
        }
    }

    void displayAccountDetails() const override {
        BankAccount::displayAccountDetails();
        cout << "Account Type: Savings" << endl;
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

// Derived Class for CurrentAccount
class CurrentAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CurrentAccount(int accNum, string accHolderName, double bal, double odLimit)
        : BankAccount(accNum, accHolderName, bal), overdraftLimit(odLimit) {}

    void withdraw(double amount) override {
        if (amount > 0 && (balance + overdraftLimit) >= amount) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: " << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or overdraft limit exceeded." << endl;
        }
    }

    void displayAccountDetails() const override {
        BankAccount::displayAccountDetails();
        cout << "Account Type: Current" << endl;
        cout << "Overdraft Limit: $" << fixed << setprecision(2) << overdraftLimit << endl;
    }
};

// Class to manage the Banking System
class BankingSystem {
private:
    vector<shared_ptr<BankAccount>> accounts;
    int nextAccountNumber = 1;

public:
    void createSavingsAccount(string accountHolderName, double initialDeposit, double interestRate) {
        auto newAccount = make_shared<SavingsAccount>(nextAccountNumber++, accountHolderName, initialDeposit, interestRate);
        accounts.push_back(newAccount);
        cout << "Savings account created successfully. Account Number: " << newAccount->getAccountNumber() << endl;
    }

    void createCurrentAccount(string accountHolderName, double initialDeposit, double overdraftLimit) {
        auto newAccount = make_shared<CurrentAccount>(nextAccountNumber++, accountHolderName, initialDeposit, overdraftLimit);
        accounts.push_back(newAccount);
        cout << "Current account created successfully. Account Number: " << newAccount->getAccountNumber() << endl;
    }

    void deposit(int accountNumber, double amount) {
        for (auto &account : accounts) {
            if (account->getAccountNumber() == accountNumber) {
                account->deposit(amount);
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    void withdraw(int accountNumber, double amount) {
        for (auto &account : accounts) {
            if (account->getAccountNumber() == accountNumber) {
                account->withdraw(amount);
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    void displayAccountDetails(int accountNumber) {
        for (auto &account : accounts) {
            if (account->getAccountNumber() == accountNumber) {
                account->displayAccountDetails();
                return;
            }
        }
        cout << "Account not found." << endl;
    }
};

int main() {
    BankingSystem bank;
    int choice;
    string name;
    int accountNumber;
    double amount;
    double interestRate;
    double overdraftLimit;

    do {
        cout << "\nBanking System Menu\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Current Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Display Account Details\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter account holder name: ";
                cin.ignore(); // To clear the buffer
                getline(cin, name);
                cout << "Enter initial deposit amount: ";
                cin >> amount;
                cout << "Enter interest rate: ";
                cin >> interestRate;
                bank.createSavingsAccount(name, amount, interestRate);
                break;

            case 2:
                cout << "Enter account holder name: ";
                cin.ignore(); // To clear the buffer
                getline(cin, name);
                cout << "Enter initial deposit amount: ";
                cin >> amount;
                cout << "Enter overdraft limit: ";
                cin >> overdraftLimit;
                bank.createCurrentAccount(name, amount, overdraftLimit);
                break;

            case 3:
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                bank.deposit(accountNumber, amount);
                break;

            case 4:
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                bank.withdraw(accountNumber, amount);
                break;

            case 5:
                cout << "Enter account number: ";
                cin >> accountNumber;
                bank.displayAccountDetails(accountNumber);
                break;

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
