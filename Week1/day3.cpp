#include <iostream>
#include <string>
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

struct AccountData {
    string owner;
    double balance;
};

int main() {
    const int numAccounts = 3;

    AccountData accountData[numAccounts] = {
        {"Sanjay", 1000.0},
        {"Sanjay", 2000.0},
        {"Sanjay", 1500.0}
    };

    BankAccount* accounts[numAccounts];  // Array of pointers to BankAccount

    accounts[0] = new BankAccount(accountData[0].owner, accountData[0].balance);
    accounts[1] = new SavingsAccount(accountData[1].owner, accountData[1].balance, 5.0);
    accounts[2] = new CheckingAccount(accountData[2].owner, accountData[2].balance, 500.0);

    accounts[0]->deposit(500);
    accounts[0]->withdraw(200);
    accounts[0]->display();

    accounts[1]->deposit(300);
    accounts[1]->withdraw(100);
    dynamic_cast<SavingsAccount*>(accounts[1])->applyInterest();
    accounts[1]->display();

    accounts[2]->deposit(200);
    accounts[2]->withdraw(2000);
    accounts[2]->display();

    *accounts[0] = *dynamic_cast<BankAccount*>(accounts[1]);
    accounts[0]->display();

    transferFunds(*dynamic_cast<BankAccount*>(accounts[1]), *dynamic_cast<BankAccount*>(accounts[2]), 100);

    
    for (int i = 0; i < numAccounts + 1; ++i) {  
        delete accounts[i];
    }

    return 0;
}
