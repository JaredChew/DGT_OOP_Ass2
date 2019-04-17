#ifndef ADMIN
#define ADMIN

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

#include "current_account.h"

void viewCreatedAccounts(CurrentAccount Admin[80]);
void viewSelectedAccount(CurrentAccount Admin[80]);
void deleteAllAccounts(CurrentAccount Admin[80]);

void admin(CurrentAccount Admin[80]) {

    int selection;

    controlPanel:

    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << "|                                       Admin Control Panel                                      |" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;

    std::cout << "\n\nPlease enter a numbered response to proceed with your selection of choice." << std::endl;
    std::cout << "\nWhat would you like to proceed with:" << std::endl;
    std::cout << "   1. View all created accounts\n   2. View a selected account of choice\n   3. Delete all accounts\n   4. Log-out" << std::endl;
    std::cout << "\nSelection: ";

    std::cin.clear();
    std::cin.ignore();
    std::cin >> selection;

    while (true){
        if (selection == 1) {

            viewCreatedAccounts(Admin);
            goto controlPanel;

        }

        else if (selection == 2) {

            viewSelectedAccount(Admin);
            goto controlPanel;

        }

        else if (selection == 3) {

            deleteAllAccounts(Admin);
            goto controlPanel;

        }

        else if (selection == 4) {

            std::cout << "\n\nYou have successfully logged-out." << std::endl;
            std::cout << "Returning to main menu.\n" << std::endl;

            system("pause");
            system("cls");

            break;

        }

        else if (std::cin.fail()) {

            std::cout << "\nPlease select a valid numbered response." << std::endl;
            std::cout << "\nOptions available:" << std::endl;
            std::cout << "   1. View all created accounts\n   2. View a selected account of choice\n   3. Delete all accounts\n   4. Log-out" << std::endl;
            std::cout << "\nSelection: ";

            std::cin.clear();
            std::cin.ignore();
            std::cin >> selection;
        }

        else {

            std::cout << "\nYour choice of selection does not exist. Please select a valid numbered response." << std::endl;
            std::cout << "\nOptions available:" << std::endl;
            std::cout << "   1. View all created accounts\n   2. View a selected account of choice\n   3. Delete all accounts\n   4. Log-out" << std::endl;
            std::cout << "\nSelection: ";

            std::cin >> selection;
        }
    }

}

void viewCreatedAccounts(CurrentAccount Admin[80]) {

    int j = 0, k = 0;

    for (int i = 0; i < 81; i++) {

        if (i == 80 && k == 0) {
            std::cout << "\nThere are no accounts created to display." << std::endl;
            break;
        }

        else if (i == 80) {
            std::cout << "\nAll created accounts has been displayed." << std::endl;
            break;
        }

        else if (Admin[i].getName() == "N/A" && Admin[i].getIC() == 0000 && Admin[i].getAccount() == 00000 && Admin[i].getBalance() == 0.00) {
            //Here's something to not make this section look odd
        }

        else {

            if (j == 10) {
                system("pause");
                system("cls");
                j = 0;
            }

            if (Admin[i].getFrozen() == 'y') {
                std::cout << "\n\n\nAccount status: !!![ACCOUNT FROZEN]!!!" << std::endl;
            }

            else if (Admin[i].getFrozen() == 'n') {
                std::cout << "\n\n\nAccount status: Clean" << std::endl;
            }

            Admin[i].display();

            std::cout << "\n" << std::endl;

            j++;
            k++;

        }

    }

    std::cout << "\nReturning to control panel.\n" << std::endl;

    system("pause");
    system("cls");

}

void viewSelectedAccount(CurrentAccount Admin[80]) {

    std::ofstream accountFiles_input;
    std::ostringstream convert;
    std::string name, filename, directory;
    char confirm;
    int accountNum, account, selection, ic;
    float overdraft, overdraftNow;

    account = 0;

    std::cout << "\nPlease enter an account number: ";
    std::cin >> accountNum;

    for ( ; account < 81; account++) {

        if (account == 80) {
            std::cout << "\nAccount does not exist." << std::endl;
            goto returnCP;
        }

        else if (accountNum == Admin[account].getAccount()) {
            break;
        }

    }

    accountManip:

    system("cls");

    if (Admin[account].getFrozen() == 'y') {
        std::cout << "Account status: !!![ACCOUNT FROZEN]!!!" << std::endl;
    }

    else if (Admin[account].getFrozen() == 'n') {
        std::cout << "Account status: Clean" << std::endl;
    }

    Admin[account].display();

    std::cout << "\nPlease enter a numbered response to proceed with your selection of choice." << std::endl;
    std::cout << "\nWhat would you like to proceed with:" << std::endl;
    std::cout << "   1. Delete account\n   2. Freeze/unfreeze account.\n   3. Change account name\n   4. Change IC number\n   5. Set overdraft limit\n   6. Exit" << std::endl;
    std::cout << "\nSelection: ";

    std::cin >> selection;

    while (true){
        if (selection == 1) {

            std::cout << "\nAre you sure? (y/n): ";
            std::cin >> confirm;

            while(true) {

                if (confirm == 'y' || confirm == 'Y') {

                    convert << Admin[account].getAccount();
                    filename = convert.str();

                    directory = "Accounts/" + std::string(filename) + ".wow";

                    Admin[account].setName("N/A");
                    Admin[account].setIC(0000);
                    Admin[account].setAccount(00000);
                    Admin[account].setBalance(0.00);

                    std::remove(directory.c_str());

                    convert.str("");
                    convert.clear();

                    std::cout << "\nAccount deleted." << std::endl;

                    goto returnCP;

                }

                else if (confirm == 'n' || confirm == 'N') {

                    std::cout << "\nReturning to selection screen.\n" << std::endl;

                    system("pause");
                    system("cls");
                    break;

                }

                else if (std::cin.fail()) {

                    std::cout << "\nPlease enter a valid response. (y/n): ";

                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> confirm;

                }

                else {

                    std::cout << "\nPlease enter a valid response. (y/n): ";

                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> confirm;

                }

            }

            goto accountManip;

        }

        else if (selection == 2) {

            if (Admin[account].getFrozen() == 'n') {

                std::cout << "\nWould yo like to freeze this account? (y/n): ";
                std::cin >> confirm;

                while(true) {

                    if (confirm == 'y' || confirm == 'Y') {

                        std::cout << "\nAccount frozen." << std::endl;

                        Admin[account].setFrozen('y');

                        convert << Admin[account].getAccount();
                        filename = convert.str();

                        directory = "Accounts/" + std::string(filename) + ".wow";

                        accountFiles_input.open(directory.c_str());

                        accountFiles_input << Admin[account].getName() << std::endl;
                        accountFiles_input << Admin[account].getIC() << std::endl;
                        accountFiles_input << Admin[account].getAccount() << std::endl;
                        accountFiles_input << Admin[account].getBalance() << std::endl;
                        accountFiles_input << Admin[account].getFrozen() << std::endl;
                        accountFiles_input << Admin[account].getOverdraft() << std::endl;
                        accountFiles_input << Admin[account].getCurrentOverdraft();

                        accountFiles_input.close();

                        convert.str("");
                        convert.clear();

                        break;

                    }

                    else if (confirm == 'n' || confirm == 'N') {

                        break;

                    }

                    else if (std::cin.fail()) {

                        std::cout << "\nPlease enter a valid response. (y/n): ";

                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> confirm;

                    }

                    else {

                        std::cout << "\nPlease enter a valid response. (y/n): ";

                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> confirm;

                    }

                }

            }

            else if (Admin[account].getFrozen() == 'y') {

                std::cout << "\nWould yo like to unfreeze this account? (y/n): ";
                std::cin >> confirm;

                while(true) {

                    if (confirm == 'y' || confirm == 'Y') {

                        std::cout << "\nAccount unfreeze." << std::endl;

                        Admin[account].setFrozen('n');

                        convert << Admin[account].getAccount();
                        filename = convert.str();

                        directory = "Accounts/" + std::string(filename) + ".wow";

                        accountFiles_input.open(directory.c_str());

                        accountFiles_input << Admin[account].getName() << std::endl;
                        accountFiles_input << Admin[account].getIC() << std::endl;
                        accountFiles_input << Admin[account].getAccount() << std::endl;
                        accountFiles_input << Admin[account].getBalance() << std::endl;
                        accountFiles_input << Admin[account].getFrozen() << std::endl;
                        accountFiles_input << Admin[account].getOverdraft() << std::endl;
                        accountFiles_input << Admin[account].getCurrentOverdraft();

                        accountFiles_input.close();

                        convert.str("");
                        convert.clear();

                        break;

                    }

                    else if (confirm == 'n' || confirm == 'N') {

                        break;

                    }

                    else if (std::cin.fail()) {

                        std::cout << "\nPlease enter a valid response. (y/n): ";

                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> confirm;

                    }

                    else {

                        std::cout << "\nPlease enter a valid response. (y/n): ";

                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> confirm;

                    }

                }

            }

            std::cout << "Returning to selection screen.\n" << std::endl;

            system("pause");
            system("cls");

            goto accountManip;

        }

        else if (selection == 3) {

            std::cout << "\nAre you sure? (y/n): ";
            std::cin >> confirm;

            while(true) {

                if (confirm == 'y' || confirm == 'Y') {

                    std::cout << "\nPlease enter a new name: ";
                    std::cin.clear();
                    std::cin.ignore();
                    getline(std::cin, name);

                    while(true){

                        if(name.empty()) {
                            std::cin.clear();
                            std::cin.ignore();
                            getline(std::cin, name);
                        }

                        else {
                            break;
                        }

                    }

                    Admin[account].setName(name);

                    convert << Admin[account].getAccount();
                    filename = convert.str();

                    directory = "Accounts/" + std::string(filename) + ".wow";

                    accountFiles_input.open(directory.c_str());

                    accountFiles_input << Admin[account].getName() << std::endl;
                    accountFiles_input << Admin[account].getIC() << std::endl;
                    accountFiles_input << Admin[account].getAccount() << std::endl;
                    accountFiles_input << Admin[account].getBalance() << std::endl;
                    accountFiles_input << Admin[account].getFrozen() << std::endl;
                    accountFiles_input << Admin[account].getOverdraft() << std::endl;
                    accountFiles_input << Admin[account].getCurrentOverdraft();

                    accountFiles_input.close();

                    convert.str("");
                    convert.clear();

                    std::cout << "\n\nAccount's name successfully changed." << std::endl;
                    std::cout << "\nReturning to selection screen.\n" << std::endl;

                    system("pause");
                    system("cls");
                    break;

                }

                else if (confirm == 'n' || confirm == 'N') {

                    std::cout << "\nReturning to selection screen.\n" << std::endl;

                    system("pause");
                    system("cls");
                    break;

                }

                else if (std::cin.fail()) {

                    std::cout << "\nPlease enter a valid response. (y/n): ";

                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> confirm;

                }

                else {

                    std::cout << "\nPlease enter a valid response. (y/n): ";

                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> confirm;

                }

            }

            goto accountManip;

        }

        else if (selection == 4) {

            std::cout << "\nAre you sure? (y/n): ";
            std::cin >> confirm;

            while(true) {

                if (confirm == 'y' || confirm == 'Y') {

                    std::cout << "\nPlease enter a new IC number (only the last 4 digits): ";
                    std::cin >> ic;

                    Admin[account].setIC(ic);

                    convert << Admin[account].getAccount();
                    filename = convert.str();

                    directory = "Accounts/" + std::string(filename) + ".wow";

                    accountFiles_input.open(directory.c_str());

                    accountFiles_input << Admin[account].getName() << std::endl;
                    accountFiles_input << Admin[account].getIC() << std::endl;
                    accountFiles_input << Admin[account].getAccount() << std::endl;
                    accountFiles_input << Admin[account].getBalance() << std::endl;
                    accountFiles_input << Admin[account].getFrozen() << std::endl;
                    accountFiles_input << Admin[account].getOverdraft() << std::endl;
                    accountFiles_input << Admin[account].getCurrentOverdraft();

                    accountFiles_input.close();

                    convert.str("");
                    convert.clear();

                    std::cout << "\n\nAccount's IC number successfully changed." << std::endl;
                    std::cout << "\nReturning to selection screen.\n" << std::endl;

                    system("pause");
                    system("cls");
                    break;

                }

                else if (confirm == 'n' || confirm == 'N') {

                    std::cout << "\nReturning to selection screen.\n" << std::endl;

                    system("pause");
                    system("cls");
                    break;

                }

                else if (std::cin.fail()) {

                    std::cout << "\nPlease enter a valid response. (y/n): ";

                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> confirm;

                }

                else {

                    std::cout << "\nPlease enter a valid response. (y/n): ";

                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> confirm;

                }

            }

            goto accountManip;

        }

        else if (selection == 5) {

            std::cout << "\nAre you sure? (y/n): ";
            std::cin >> confirm;

            while(true) {

                if (confirm == 'y' || confirm == 'Y') {

                    std::cout << "\nPlease enter a new overdraft limit: ";
                    std::cin >> overdraft;

                    if (Admin[account].getCurrentOverdraft() == Admin[account].getOverdraft()) {

                        Admin[account].setOverdraft(overdraft);
                        Admin[account].setCurrentOverdraft(overdraft);

                        convert << Admin[account].getAccount();
                        filename = convert.str();

                        directory = "Accounts/" + std::string(filename) + ".wow";

                        accountFiles_input.open(directory.c_str());

                        accountFiles_input << Admin[account].getName() << std::endl;
                        accountFiles_input << Admin[account].getIC() << std::endl;
                        accountFiles_input << Admin[account].getAccount() << std::endl;
                        accountFiles_input << Admin[account].getBalance() << std::endl;
                        accountFiles_input << Admin[account].getFrozen() << std::endl;
                        accountFiles_input << Admin[account].getOverdraft() << std::endl;
                        accountFiles_input << Admin[account].getCurrentOverdraft();

                        accountFiles_input.close();

                        convert.str("");
                        convert.clear();

                    }

                    else if (Admin[account].getCurrentOverdraft() < Admin[account].getOverdraft()) {

                        if (overdraft < Admin[account].getCurrentOverdraft()) {

                            overdraftNow = (overdraft - (Admin[account].getOverdraft() - Admin[account].getCurrentOverdraft()));

                            Admin[account].setOverdraft(overdraft);
                            Admin[account].setCurrentOverdraft(overdraftNow);

                            convert << Admin[account].getAccount();
                            filename = convert.str();

                            directory = "Accounts/" + std::string(filename) + ".wow";

                            accountFiles_input.open(directory.c_str());

                            accountFiles_input << Admin[account].getName() << std::endl;
                            accountFiles_input << Admin[account].getIC() << std::endl;
                            accountFiles_input << Admin[account].getAccount() << std::endl;
                            accountFiles_input << Admin[account].getBalance() << std::endl;
                            accountFiles_input << Admin[account].getFrozen() << std::endl;
                            accountFiles_input << Admin[account].getOverdraft() << std::endl;
                            accountFiles_input << Admin[account].getCurrentOverdraft();

                            accountFiles_input.close();

                        }

                        else if (overdraft > Admin[account].getCurrentOverdraft()) {

                            overdraftNow = (overdraft * (overdraft / (Admin[account].getOverdraft() + Admin[account].getCurrentOverdraft())));

                            Admin[account].setOverdraft(overdraft);
                            Admin[account].setCurrentOverdraft(overdraftNow);

                            convert << Admin[account].getAccount();
                            filename = convert.str();

                            directory = "Accounts/" + std::string(filename) + ".wow";

                            accountFiles_input.open(directory.c_str());

                            accountFiles_input << Admin[account].getName() << std::endl;
                            accountFiles_input << Admin[account].getIC() << std::endl;
                            accountFiles_input << Admin[account].getAccount() << std::endl;
                            accountFiles_input << Admin[account].getBalance() << std::endl;
                            accountFiles_input << Admin[account].getFrozen() << std::endl;
                            accountFiles_input << Admin[account].getOverdraft() << std::endl;
                            accountFiles_input << Admin[account].getCurrentOverdraft();

                            accountFiles_input.close();

                        }

                    }

                    std::cout << "\n\nAccount's overdraft limit successfully changed." << std::endl;
                    std::cout << "\nReturning to selection screen.\n" << std::endl;

                    system("pause");
                    system("cls");
                    break;

                }

                else if (confirm == 'n' || confirm == 'N') {

                    std::cout << "\nReturning to selection screen.\n" << std::endl;

                    system("pause");
                    system("cls");
                    break;

                }

                else if (std::cin.fail()) {

                    std::cout << "\nPlease enter a valid response. (y/n): ";

                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> confirm;

                }

                else {

                    std::cout << "\nPlease enter a valid response. (y/n): ";

                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> confirm;

                }

            }

            goto accountManip;

        }

        else if (selection == 6) {

            returnCP:

            std::cout << "\nReturning to control panel.\n" << std::endl;

            system("pause");
            system("cls");
            break;

        }


        else if (std::cin.fail()) {

            std::cout << "\nPlease select a valid numbered response." << std::endl;
            std::cout << "\nOptions available:" << std::endl;
            std::cout << "   1. Delete account\n   2. Freeze/unfreeze account.\n   3. Change account name\n   4. Change IC number\n   5. Set overdraft limit\n   6. Exit" << std::endl;
            std::cout << "\nSelection: ";

            std::cin.clear();
            std::cin.ignore();
            std::cin >> selection;
        }

        else {

            std::cout << "\nYour choice of selection does not exist. Please select a valid numbered response." << std::endl;
            std::cout << "\nOptions available:" << std::endl;
            std::cout << "   1. Delete account\n   2. Freeze/unfreeze account.\n   3. Change account name\n   4. Change IC number\n   5. Set overdraft limit\n   6. Exit" << std::endl;
            std::cout << "\nSelection: ";

            std::cin >> selection;
        }
    }

}

void deleteAllAccounts(CurrentAccount Admin[80]) {

    std::ofstream accountFiles_input;
    std::ostringstream convert;
    std::string filename, directory;
    int j = 0;
    char confirm;

    std::cout << "\nAre you sure? (y/n): ";
    std::cin >> confirm;

    while(true) {

        if (confirm == 'y' || confirm == 'Y') {

            for (int i = 0; i < 81; i++) {

                if (i == 80 && j == 0) {

                    std::cout << "\nNo accounts created to delete." << std::endl;
                    break;

                }

                else if (i == 80) {

                    std::cout << "\n\nAll accounts deleted" << std::endl;
                    break;

                }

                else if (Admin[i].getName() == "N/A" && Admin[i].getIC() == 0000 && Admin[i].getAccount() == 00000 && Admin[i].getBalance() == 0.00) {
                    //Nothing to see here
                }

                else {

                    std::cout << "\n\nAccount ID: " << Admin[i].getAccount();

                    convert << Admin[i].getAccount();
                    filename = convert.str();

                    directory = "Accounts/" + std::string(filename) + ".wow";

                    Admin[i].setName("N/A");
                    Admin[i].setIC(0000);
                    Admin[i].setAccount(00000);
                    Admin[i].setBalance(0.00);

                    std::remove(directory.c_str());

                    convert.str("");
                    convert.clear();

                    std::cout << " deleted" << std::endl;

                    j++;

                }

            }

            std::cout << "Returning to control panel.\n" << std::endl;

            system("pause");
            system("cls");
            break;

        }

        else if (confirm == 'n' || confirm == 'N') {

            std::cout << "\nReturning to control panel.\n" << std::endl;

            system("pause");
            system("cls");
            break;

        }

        else if (std::cin.fail()) {

            std::cout << "\nPlease enter a valid response. (y/n): ";

            std::cin.clear();
            std::cin.ignore();
            std::cin >> confirm;

        }

        else {

            std::cout << "\nPlease enter a valid response. (y/n): ";

            std::cin.clear();
            std::cin.ignore();
            std::cin >> confirm;

        }

    }

}

#endif
