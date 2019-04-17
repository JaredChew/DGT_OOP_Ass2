#include <iostream>
#include <cstdlib>
//#include "stdafx.h"

#include "Header Files/functions.h"
#include "Header Files/current_account.h"

void loadAccounts(CurrentAccount Load[80]);
void logIn(int &i, char &yesNo, CurrentAccount Login[80]);
void createAccount(int &i, char &successfull , CurrentAccount Create[80]);
void withdraw(int i, CurrentAccount InMoney[80]);
void deposit(int i, CurrentAccount OutMoney[80]);
void showDetails(int i, CurrentAccount Details[80]);

int main() {

    int account, selection;
    char check;

    CurrentAccount Main[80];

    loadAccounts(Main);

    main_menu:

    account = 0;

    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << "|                             WELCOME TO AN 'ONLINE' BANKING SYSTEM                              |" << std::endl;
    std::cout << "|            Because all ideas went into the development of this system and not the name         |" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;

    std::cout << "\n\nPlease enter a numbered response to proceed with your selection of choice." << std::endl;
    std::cout << "Would you like to log-in to an existing account or create a new account" << std::endl;
    std::cout << "\n\nOptions available:" << std::endl;
    std::cout << "   1. Log-in\n   2. Create account\n   3. Shut down" << std::endl;
    std::cout << "\nSelection: ";

    std::cin >> selection;

    while(true) {

        if(selection == 1) {

            system("cls");

            logIn(account, check, Main);

            if (check == 'y') {
                goto home;
            }
            else if (check == 'n') {
                goto main_menu;
            }

        }

        else if (selection == 2) {

            system("cls");

            createAccount(account, check, Main);

            if (check == 'y') {
                goto home;
            }
            else if (check == 'n') {
                goto main_menu;
            }

        }

        else if (selection == 3) {

            std::cout << "\n\nThe system will now shut down." << std::endl;
            std::cout << "Thank you for using The Hosiang 'Online' self-service banking system." << std::endl;

            return 0;

        }

        else if (std::cin.fail()) {

            std::cout << "\nPlease select a valid numbered response." << std::endl;
            std::cout << "\nOptions available:" << std::endl;
            std::cout << "   1. Log-in\n   2. Create account\n   3. Shut down" << std::endl;
            std::cout << "\nSelection: ";

            std::cin.clear();
            std::cin.ignore();
            std::cin >> selection;
        }

        else {

            std::cout << "\nYour choice of selection does not exist. Please select a valid numbered response." << std::endl;
            std::cout << "\nOptions available:" << std::endl;
            std::cout << "   1. Log-in\n   2. Create account\n   3. Shut down" << std::endl;
            std::cout << "\nSelection: ";

            std::cin >> selection;
        }
    }

    std::cout << "\n\nAn Error has occurred.\nThe program will now terminate itself" << std::endl;

    return 0;

    home:

    system("cls");

    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << "|                                   An 'online' banking system                                   |" << std::endl;
    std::cout << "|                    Full of surprises that will constantly make you scream 'WOW!!!'             |" << std::endl;
    std::cout << "|                           'WOW!!!' - Directly quoted from Hosiang, 2016                        |" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;

    std::cout << "\n\nPlease enter a numbered response to proceed with your selection of choice." << std::endl;
    std::cout << "\nWhat would you like to proceed with:" << std::endl;
    std::cout << "   1. Withdraw\n   2. Deposit\n   3. View account details\n   4. Log-out" << std::endl;
    std::cout << "\nSelection: ";

    std::cin >> selection;

    while (true){
        if (selection == 1) {

            system("cls");
            withdraw(account, Main);
            goto home;
        }

        else if (selection == 2) {

            system("cls");
            deposit(account, Main);
            goto home;

        }

        else if (selection == 3) {

            system("cls");
            showDetails(account, Main);
            goto home;

        }

        else if (selection == 4) {

            std::cout << "\n\nYou have successfully logged-out." << std::endl;
            std::cout << "\nThank you for using The Hosiang 'Online' self-service banking system." << std::endl;
            std::cout << "Returning to main menu.\n" << std::endl;

            system("pause");
            system("cls");

            goto main_menu;

        }

        else if (std::cin.fail()) {

            std::cout << "\nPlease select a valid numbered response." << std::endl;
            std::cout << "\nOptions available:" << std::endl;
            std::cout << "   1. Withdraw\n   2. Deposit\n   3. View account details\n   4. Log-out" << std::endl;
            std::cout << "\nSelection: ";

            std::cin.clear();
            std::cin.ignore();
            std::cin >> selection;
        }

        else {

            std::cout << "\nYour choice of selection does not exist. Please select a valid numbered response." << std::endl;
            std::cout << "\nOptions available:" << std::endl;
            std::cout << "   1. Withdraw\n   2. Deposit\n   3. View account details\n   4. Log-out" << std::endl;
            std::cout << "\nSelection: ";

            std::cin.clear();
            std::cin.ignore();
            std::cin >> selection;
        }
    }

    std::cout << "\n\nAn Error has occurred.\nThe program will now terminate itself" << std::endl;

    return 0;
}
