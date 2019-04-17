#ifndef ACCOUNT
#define ACCOUNT

#include <iostream>
#include <string>
#include <iomanip>

class Account {

    private:
        std::string name;
        int ic_number;
        int accountNumber;
        float balance;
        char frozen;

    public:
        Account() {

            name = "N/A";
            ic_number = 0000;
            accountNumber = 00000;
            balance = 0.00;
            frozen = 'n';

        }

        Account(std::string username, int ic, int account, float balanceNumber, char freeze) {

            name = username;
            ic_number = ic;
            accountNumber = account;
            balance = balanceNumber;
            frozen = freeze;

        }

        std::string getName(){
            return name;
        }

        int getIC() {
            return ic_number;
        }

        int getAccount() {
            return accountNumber;
        }

        float getBalance() {
            return balance;
        }

        char getFrozen() {
            return frozen;
        }

        void setName(std::string username) {
            name = username;
        }

        void setIC(int ic) {
            ic_number = ic;
        }

        void setAccount(int account) {
            accountNumber = account;
        }

        void setBalance(float balanceNumber) {
            balance = balanceNumber;
        }

        void setFrozen(char freeze) {
            frozen = freeze;
        }

        void withdraw(float deductMoney) {

            if(deductMoney >= balance) {
                balance = 0;
            }

            else if (deductMoney < balance) {
                balance -= deductMoney;
            }

            std::cout << "\nSuccessfully withdrawn RM" << std::fixed << std::setprecision(2) << deductMoney << std::endl;
        }

        void deposit(float addMoney) {

            balance += addMoney;

            std::cout <<"\n\nSuccessfully deposited RM" << addMoney << std::endl;
            std::cout << "\nNew balance: " << std::fixed << std::setprecision(2) << balance << std::endl;

        }

        void display() {

            std::cout << "=================================================" << std::endl;
            std::cout << "                 Account Details" << std::endl;
            std::cout << "\n\nName: " << name << std::endl;
            std::cout << "IC number: " << ic_number << std::endl;
            std::cout << "Account number: " << accountNumber << std::endl;
            std::cout << "Balance: " << std::fixed << std::setprecision(2) << balance << std::endl;

        }

};

#endif
