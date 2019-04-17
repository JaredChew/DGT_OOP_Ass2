#ifndef CURRENT_ACCOUNT
#define CURRENT_ACCOUNT

#include <iostream>
#include <string>
#include <iomanip>

#include "account.h"

class CurrentAccount :public Account {

    private:
        float overdraftLimit;
        float currentOverdraft;

    public:
        CurrentAccount() :Account() {

            overdraftLimit = 500;
            currentOverdraft = 500;

        }

        CurrentAccount(std::string username, int ic, int account, float balanceNumber, char freeze, float overdraft, float overdraftNow)
        :Account(username, ic, account, balanceNumber, freeze) {

            overdraftLimit = overdraft;
            currentOverdraft = overdraftNow;

        }

        float getOverdraft() {
            return overdraftLimit;
        }

        float getCurrentOverdraft() {
            return currentOverdraft;
        }

        void setOverdraft(float overdraft) {
            overdraftLimit = overdraft;
        }

        void setCurrentOverdraft(float overdraftNow) {
            currentOverdraft = overdraftNow;
        }

        void deposit(float deposit) {

            char yesNo;
            float repay;

            if (currentOverdraft < overdraftLimit) {

                repay = overdraftLimit - currentOverdraft;

                std::cout << "\nOverdraft limit below agreed value.\nYour deposited money will payoff your current overdraft debt before going into your bank account." << std::endl;
                std::cout << "Any remainder after paying off the overdraft debt will be put into your bank account." << std::endl;
                std::cout << "\nWould you like to proceed with the deposit? (y/n): ";
                std::cin >> yesNo;

                while(true) {

                    if(yesNo == 'y' || yesNo == 'Y') {

                        if (deposit > repay) {

                            deposit -= repay;
                            Account::deposit(deposit);
                            currentOverdraft += repay;

                            std::cout << "\nOverdraft debt paid off.\nCurrent overdraft limit: " << std::fixed << std::setprecision(2) << currentOverdraft << std::endl;

                            break;

                        }

                        else if (deposit < repay) {

                            currentOverdraft += deposit;

                            std::cout << "\nOverdraft debt partially paid.\nCurrent overdraft limit: " << std::fixed << std::setprecision(2) << currentOverdraft << std::endl;

                            break;

                        }

                    }

                    else if(yesNo == 'n' || yesNo == 'N') {
                        break;
                    }

                    else if(std::cin.fail()) {
                        std::cout << "Please enter a valid response. (y/n): ";
                        std::cin >> yesNo;
                    }

                    else {
                        std::cout << "Please enter a valid response. (y/n): ";
                        std::cin >> yesNo;
                    }

                }

            }

            else if (overdraftLimit == currentOverdraft) {
                Account::deposit(deposit);
            }

        }

        void withdraw(float withdraw) {

            char yesNo;

            if (withdraw > (Account::getBalance() + currentOverdraft)) {
                std::cout << "\nYou do not have sufficient funds in your bank account including overdraft limit." << std::endl;
            }

            else if(withdraw <= Account::getBalance()) {
                Account::withdraw(withdraw);
                std::cout << "\nNew balance: " << std::fixed << std::setprecision(2) << Account::getBalance() << std::endl;
            }

            else if (withdraw <= (Account::getBalance() + currentOverdraft)) {

                std::cout << "\nWithdrawal amount exceeds account balance." << std::endl;
                std::cout << "Your current withdrawal limit including overdraft is: " << currentOverdraft + Account::getBalance() << std::endl;
                std::cout << "\nWould you like to proceed with the withdrawal? (y/n): ";
                std::cin >> yesNo;

                while(true) {

                    if(yesNo == 'y' || yesNo == 'Y') {

                        currentOverdraft = (currentOverdraft - (withdraw - Account::getBalance()));

                        Account::withdraw(withdraw);

                        std::cout << "\nNew balance: " << std::fixed << std::setprecision(2) << Account::getBalance() << std::endl;
                        std::cout << "Current overdraft limit: " << std::fixed << std::setprecision(2) << currentOverdraft << std::endl;

                        break;

                    }

                    else if(yesNo == 'n' || yesNo == 'N') {
                        break;
                    }

                    else if(std::cin.fail()) {
                        std::cout << "Please enter a valid response. (y/n): ";
                        std::cin >> yesNo;
                    }

                    else {
                        std::cout << "Please enter a valid response. (y/n): ";
                        std::cin >> yesNo;
                    }

                }

            }

        }

        void display() {

            Account::display();

            std::cout << "Overdraft limit: " << std::fixed << std::setprecision(2) << currentOverdraft << " (" << overdraftLimit << ")" << std::endl;
            std::cout << "=================================================" << std::endl;

        }


};

#endif
