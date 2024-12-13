#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <iterator>
using namespace std;

class Account {
public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual double getBalance() const = 0;
    virtual void display() const = 0;
    virtual ~Account() {}
};

class BankAccount : public Account {
protected:
    string owner;
    double balance;

public:
    BankAccount(string owner, double balance) : owner(owner), balance(balance) {}

    void deposit(double amount) override {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited " << amount << ". New balance: " << balance << endl;
        } else {
            cout << "Deposit amount must be positive." << endl;
        }
    }

    void withdraw(double amount) override {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrew " << amount << ". New balance: " << balance << endl;
        } else {
            cout << "Insufficient funds or invalid amount." << endl;
        }
    }

    double getBalance() const override {
        return balance;
    }

    void display() const override {
        cout << "Account Owner: " << owner << endl;
        cout << "Account Balance: " << balance << endl;
    }

    BankAccount& operator+(const BankAccount& other) {
        this->balance += other.balance;
        return *this;
    }

    friend void transferFunds(BankAccount& from, BankAccount& to, double amount);
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string owner, double balance, double interestRate)
        : BankAccount(owner, balance), interestRate(interestRate) {}

    void deposit(double amount) override {
        BankAccount::deposit(amount);
        cout << "Interest applied at rate " << interestRate << "%" << endl;
    }

    void applyInterest() {
        double interest = balance * (interestRate / 100);
        deposit(interest);
        cout << "Interest applied. New balance: " << balance << endl;
    }

    void display() const override {
        BankAccount::display();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }

    void setInterestRate(double rate) {
        interestRate = rate;
    }
};

class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(string owner, double balance, double overdraftLimit)
        : BankAccount(owner, balance), overdraftLimit(overdraftLimit) {}

    void withdraw(double amount) override {
        if (amount > 0 && amount <= (balance + overdraftLimit)) {
            balance -= amount;
            cout << "Withdrew " << amount << " with overdraft. New balance: " << balance << endl;
        } else {
            cout << "Overdraft limit exceeded or invalid withdrawal amount." << endl;
        }
    }

    void display() const override {
        BankAccount::display();
        cout << "Overdraft Limit: " << overdraftLimit << endl;
    }

    friend void transferFunds(CheckingAccount& from, CheckingAccount& to, double amount);
};

void transferFunds(BankAccount& from, BankAccount& to, double amount) {
    if (from.getBalance() >= amount) {
        from.withdraw(amount);
        to.deposit(amount);
        cout << "Transferred " << amount << " from " << from.getBalance() << " to " << to.getBalance() << endl;
    } else {
        cout << "Insufficient funds for transfer." << endl;
    }
}

int main() {
    // Vectors to store BankAccount pointers
    vector<BankAccount*> accounts;

    // Adding accounts dynamically
    accounts.push_back(new BankAccount("Sanjay", 1000));
    accounts.push_back(new SavingsAccount("Sanjay", 2000, 5.0));
    accounts.push_back(new CheckingAccount("Sanjay", 1500, 500));

    // Using Iterators to display account details
    cout << "Displaying all accounts using vector iterator:" << endl;
    for (vector<BankAccount*>::iterator it = accounts.begin(); it != accounts.end(); ++it) {
        (*it)->display();
        cout << "------" << endl;
    }

    // Map to store accounts by owner name (key)
    map<string, BankAccount*> accountMap;
    accountMap["Sanjay"] = new BankAccount("Sanjay", 3000);
    accountMap["Amit"] = new SavingsAccount("Amit", 2500, 4.5);
    accountMap["Ravi"] = new CheckingAccount("Ravi", 1800, 300);

    // Using Iterators to traverse the map
    cout << "Displaying accounts using map iterator:" << endl;
    for (map<string, BankAccount*>::iterator it = accountMap.begin(); it != accountMap.end(); ++it) {
        cout << "Account owner: " << it->first << endl;
        it->second->display();
        cout << "------" << endl;
    }

    // List to store BankAccount pointers
    list<BankAccount*> accountList;
    accountList.push_back(new BankAccount("Sanjay", 1000));
    accountList.push_back(new CheckingAccount("Amit", 1500, 200));
    accountList.push_back(new SavingsAccount("Ravi", 2000, 6.0));

    // Using Iterators to display list content
    cout << "Displaying all accounts using list iterator:" << endl;
    for (list<BankAccount*>::iterator it = accountList.begin(); it != accountList.end(); ++it) {
        (*it)->display();
        cout << "------" << endl;
    }

    // Perform a transaction using accounts in the vector
    transferFunds(*accounts[0], *accounts[1], 500);

    // Clean up dynamic memory
    for (vector<BankAccount*>::iterator it = accounts.begin(); it != accounts.end(); ++it) {
        delete *it;
    }

    for (map<string, BankAccount*>::iterator it = accountMap.begin(); it != accountMap.end(); ++it) {
        delete it->second;
    }

    for (list<BankAccount*>::iterator it = accountList.begin(); it != accountList.end(); ++it) {
        delete *it;
    }

    return 0;
}
