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
};

int main() {
    BankAccount* account1 = new BankAccount("Sanjay", 1000);
    BankAccount* account2 = new SavingsAccount("Sanjay", 2000, 5);
    BankAccount* account3 = new CheckingAccount("Sanjay", 1500, 500);

    account1->deposit(500);
    account1->withdraw(200);
    account1->display();

    account2->deposit(300);
    account2->withdraw(100);
    dynamic_cast<SavingsAccount*>(account2)->applyInterest();
    account2->display();

    account3->deposit(200);
    account3->withdraw(2000);
    account3->display();

    delete account1;
    delete account2;
    delete account3;

    return 0;
}
