#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class BankAccount {
public:
    int accountNumber;
    char name[50];
    double balance;

    void createAccount();
    void displayAccount() const;
    void deposit(double amount);
    void withdraw(double amount);
};

void BankAccount::createAccount() {
    cout << "Enter Account Number: ";
    cin >> accountNumber;
    cin.ignore();  // Clear buffer before taking string input
    cout << "Enter Account Holder Name: ";
    cin.getline(name, 50);
    cout << "Enter Initial Deposit: ";
    cin >> balance;
    cout << "Account Created Successfully!\n";
}

void BankAccount::displayAccount() const {
    cout << "Account Number: " << accountNumber << endl;
    cout << "Holder Name: " << name << endl;
    cout << "Balance: Rs." << balance << endl;
}

void BankAccount::deposit(double amount) {
    balance += amount;
    cout << "Amount Deposited Successfully!\n";
}

void BankAccount::withdraw(double amount) {
    if (balance >= amount) {
        balance -= amount;
        cout << "Withdrawal Successful!\n";
    } else {
        cout << "Insufficient Balance!\n";
    }
}

void saveAccount(const BankAccount& acc) {
    ofstream file("accounts.txt", ios::app);
    if (!file) {
        cout << "Error: Unable to open file!\n";
        return;
    }
    file << acc.accountNumber << "|" << acc.name << "|" << acc.balance << endl;
    file.close();
}

void displayAllAccounts() {
    ifstream file("accounts.txt");
    if (!file) {
        cout << "Error: Unable to open file!\n";
        return;
    }

    BankAccount acc;
    while (file >> acc.accountNumber) {
        file.ignore();  // Ignore separator before name
        file.getline(acc.name, 50, '|'); 
        file >> acc.balance;
        file.ignore();  // Ignore newline character
        acc.displayAccount();
        cout << "----------------------\n";
    }
    file.close();
}

int main() {
    int choice;
    while (true) {
        cout << "\nBank Management System\n";
        cout << "1. Create Account\n2. Display All Accounts\n3. Exit\nChoose an option: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                BankAccount acc;
                acc.createAccount();
                saveAccount(acc);
                break;
            }
            case 2:
                displayAllAccounts();
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid Choice! Try Again.\n";
        }
    }
}
