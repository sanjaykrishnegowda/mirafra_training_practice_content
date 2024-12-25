#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <stack>
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

    bool operator<(const BankAccount& other) const {
        return balance < other.balance;
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
    
    priority_queue<BankAccount> priorityQueue;
    priorityQueue.push(BankAccount("Sanjay", 2000));
    priorityQueue.push(SavingsAccount("Sanjay", 3000, 5.0));
    priorityQueue.push(CheckingAccount("Sanjay", 1000, 500));

    cout << "Priority Queue - Processing accounts based on balance (highest first):" << endl;
    while (!priorityQueue.empty()) {
        priorityQueue.top().display();
        priorityQueue.pop();
        cout << "------" << endl;
    }
    stack<string> operationHistory;
    operationHistory.push("Deposit 500 to Sanjay's account");
    operationHistory.push("Withdraw 200 from Sanjay's account");
    operationHistory.push("Deposit 1000 to Sanjay's account");

    cout << "Stack - Operation History:" << endl;
    while (!operationHistory.empty()) {
        cout << operationHistory.top() << endl;
        operationHistory.pop();
    }
    queue<BankAccount*> customerQueue;
    customerQueue.push(new BankAccount("Sanjay", 5000));
    customerQueue.push(new SavingsAccount("Amit", 2500, 4.5));
    customerQueue.push(new CheckingAccount("Ravi", 1500, 300));

    cout << "Queue - Processing customer service requests:" << endl;
    while (!customerQueue.empty()) {
        customerQueue.front()->display();
        customerQueue.pop();
        cout << "------" << endl;
    }
    while (!customerQueue.empty()) {
        delete customerQueue.front();
        customerQueue.pop();
    }

    return 0;
}
}hagsjhsgfj