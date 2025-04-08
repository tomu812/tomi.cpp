#include <iostream>
using namespace std;

// Clasa de bază Account
class Account {
protected:
    double balance;

public:
    // Constructor
    Account(double initialBalance) {
        if (initialBalance >= 0.0)
            balance = initialBalance;
        else {
            balance = 0.0;
            cout << "Error: Initial balance is invalid. Setting balance to 0.0" << endl;
        }
    }

    // Credit (depune bani)
    virtual void credit(double amount) {
        balance += amount;
    }

    // Debit (retrage bani)
    virtual bool debit(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        } else {
            cout << "Debit amount exceeded account balance." << endl;
            return false;
        }
    }

    // Returnează soldul curent
    double getBalance() const {
        return balance;
    }
};

// Clasa derivată SavingsAccount
class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(double initialBalance, double rate)
        : Account(initialBalance), interestRate(rate) {}

    // Calculează dobânda acumulată
    double calculateInterest() const {
        return balance * interestRate;
    }
};

// Clasa derivată CheckingAccount
class CheckingAccount : public Account {
private:
    double transactionFee;

    // Aplică taxa
    void chargeFee() {
        balance -= transactionFee;
    }

public:
    CheckingAccount(double initialBalance, double fee)
        : Account(initialBalance), transactionFee(fee) {}

    // Suprascrie credit pentru a aplica taxa
    void credit(double amount) override {
        Account::credit(amount);
        chargeFee();
    }

    // Suprascrie debit pentru a aplica taxa doar dacă debitul e posibil
    bool debit(double amount) override {
        bool success = Account::debit(amount);
        if (success) {
            chargeFee();
        }
        return success;
    }
};

// Program principal de test
int main() {
    // Creare conturi
    SavingsAccount savings(1000.0, 0.05); // 5% dobândă
    CheckingAccount checking(1000.0, 1.5); // 1.5 comision pe tranzacție

    // Teste SavingsAccount
    cout << "Initial savings balance: " << savings.getBalance() << endl;
    double interest = savings.calculateInterest();
    cout << "Interest earned: " << interest << endl;
    savings.credit(interest); // Adaugă dobânda
    cout << "Savings balance after interest: " << savings.getBalance() << endl;

    // Teste CheckingAccount
    cout << "\nInitial checking balance: " << checking.getBalance() << endl;
    checking.credit(200); // Adaugă bani (cu comision)
    cout << "Checking balance after credit of 200 (minus fee): " << checking.getBalance() << endl;
    checking.debit(100); // Retrage bani (cu comision dacă e succes)
    cout << "Checking balance after debit of 100 (minus fee): " << checking.getBalance() << endl;
    checking.debit(2000); // Încearcă retragere prea mare
    cout << "Final checking balance: " << checking.getBalance() << endl;

    return 0;
}
