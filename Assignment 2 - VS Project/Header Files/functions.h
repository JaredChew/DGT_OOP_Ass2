#ifndef FUNCTIONS
#define FUNCTIONS

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

#include "current_account.h"
#include "admin.h"

void randomNumberGenerator(int &rng);
void admin(CurrentAccount Admin[80]);

void loadAccounts(CurrentAccount Load[80]) {

    std::ostringstream convert;
    std::string filename, directory, input[7];
    int counter;

    for (int i = 0 ; i < 10000; i++) {

        convert << i;
        filename = convert.str();

        directory = "Accounts/" + std::string(filename) + ".wow";

        std::ifstream accountFiles_output(directory.c_str());

        if (accountFiles_output.is_open()) {

            counter = 0;

            while (true) {

				if (counter == 7) {
					break;
				}

				else if (counter < 7) {
					getline(accountFiles_output, input[counter]);
					counter++;
				}

            }

            std::ostringstream convertName;
            convertName << input[0];
            std::string name = convertName.str();

            int ic = std::stoi(input[1]);
            int accountNum = std::stoi(input[2]);

            float balance = std::stof(input[3]);
            float overdraft = std::stof(input[5]);
            float overdraftNow = std::stof(input[6]);

            char freeze = input[4][0];

            for (int j = 0; j < 80; j++) {

                if (Load[j].getAccount() == 0000) {

                    Load[j].setAccount(accountNum);
                    Load[j].setName(name);
                    Load[j].setBalance(balance);
                    Load[j].setFrozen(freeze);
                    Load[j].setIC(ic);
                    Load[j].setOverdraft(overdraft);
                    Load[j].setCurrentOverdraft(overdraftNow);

                    break;

                }

            }

            accountFiles_output.close();

        }

        convert.str("");
        convert.clear();

    }

    system("cls");

}

void logIn(int &i, char &successfull, CurrentAccount Login[80]) {

    std::string name;
    int ic, accountNum;

    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << "|                                            LOG-IN                                              |" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;

    std::cout << "\n\nPlease enter your full name: ";
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

    std::cout << "Please enter your account number: ";
    std::cin >> accountNum;

    while(true) {

        if (std::cin.fail()) {

            std::cout << "\n\nInvalid Input.\nPlease key-in a valid account number: ";

            std::cin.clear();
            std::cin.ignore();
            std::cin >> accountNum;

        }

        else {

            break;

        }

    }

    std::cout << "Please key-in the last 4 digits of your IC number: ";
    std::cin >> ic;

    while(true) {

        if (ic > 9999) {

            std::cout << "\n\nInvalid Input.\n\nPlease key-in the last 4 digits of your IC number: ";

            std::cin.clear();
            std::cin.ignore();
            std::cin >> ic;

        }

        else if (std::cin.fail()) {

            std::cout << "\n\nInvalid Input.\n\nPlease key-in the last 4 digits of your IC number: ";

            std::cin.clear();
            std::cin.ignore();
            std::cin >> ic;

        }

        else {

            break;

        }

    }

    for( ; i < 81; i++) {

        if (name == "admin" && accountNum == 99999 && ic == 00000) {

            std::cout << "\n\nLog-in successful." << std::endl;
            std::cout << "Proceeding to Admin Control Panel\n" << std::endl;

            system("pause");
            system("cls");

            admin(Login);

            successfull = 'n';

            break;

        }

        else if (name == "N/A" && accountNum == 00000 && ic == 0000) {

            std::cout << "\n\nLog-in unsuccessful." << std::endl;
            successfull = 'n';

            std::cout << "\nReturning to main menu.\n" << std::endl;

            system("pause");
            system("cls");

            break;

        }

        else if (i == 80) {

            std::cout << "\n\nLog-in unsuccessful." << std::endl;
            successfull = 'n';

            std::cout << "\nReturning to main menu.\n" << std::endl;

            system("pause");
            system("cls");

            break;

        }

        else if (name == Login[i].getName() && accountNum == Login[i].getAccount() && ic == Login[i].getIC()) {

            if (Login[i].getFrozen() == 'y') {

                std::cout << "\n\nAccount Frozen." << std::endl;

                successfull = 'n';

                std::cout << "\nReturning to main menu.\n" << std::endl;

                system("pause");
                system("cls");

                break;

            }

            else if (Login[i].getFrozen() == 'n') {

                std::cout << "\n\nLog-in successful." << std::endl;

                successfull = 'y';

            }

            std::cout << "\nProceeding to home screen." << std::endl;

            system("pause");
            system("cls");

            break;

        }

    }

}

void createAccount(int &i, char &yesNo, CurrentAccount Create[80]) {

    std::ofstream accountFiles_input;
    std::ostringstream convert;
    std::string name, filename, directory;
    int ic, accountNum;

    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << "|                                    CREATE NEW ACCOUNT                                          |" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;

    for ( ; i < 81; i++) {

        if (i == 80) {

            std::cout << "\n\nOur system has reached full account capacity and are not able to create any new accounts." << std::endl;
            std::cout << "\nWe sincerely appologise for the inconvenience." << std::endl;

            yesNo = 'n';

            std::cout << "\n\nReturning to main menu.\n" << std::endl;

            system("pause");
            system("cls");

            break;

        }

        else if (Create[i].getName() == "N/A" && Create[i].getIC() == 0000 && Create[i].getAccount() == 0000 && Create[i].getBalance() == 0.0) {

            std::cout << "\n\nPlease enter your full name: ";
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

            Create[i].setName(name);

            std::cout << "Please key-in the last 4 digits of your IC number: ";
            std::cin >> ic;

            while (true) {

                if (ic > 9999) {

                    std::cout << "\n\nInvalid Input.\n\nPlease key-in the last 4 digits of your IC number: ";

                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> ic;

                }

                else if (std::cin.fail()) {

                    std::cout << "\n\nInvalid Input.\n\nPlease key-in the last 4 digits of your IC number: ";

                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> ic;

                }

                else {

                    break;

                }

            }

            Create[i].setIC(ic);


            randomNumberGenerator(accountNum);
            Create[i].setAccount(accountNum);

            for (int j = 0; j < 80; j++) {

                if (accountNum == Create[j].getAccount()) {

                    randomNumberGenerator(accountNum);
                    Create[i].setAccount(accountNum);

                }

            }

            convert << accountNum;
            filename = convert.str();

            directory = "Accounts/" + std::string(filename) + ".wow";

            accountFiles_input.open(directory.c_str());

            accountFiles_input << name << std::endl;
            accountFiles_input << ic << std::endl;
            accountFiles_input << accountNum << std::endl;
            accountFiles_input << Create[i].getBalance() << std::endl;
            accountFiles_input << Create[i].getFrozen() << std::endl;
            accountFiles_input << Create[i].getOverdraft() << std::endl;
            accountFiles_input << Create[i].getCurrentOverdraft();

            accountFiles_input.close();

            std::cout << "\n\nAccount successfully created." << std::endl;
            std::cout << "Please save the information given below." << std::endl;

            yesNo = 'y';

            std::cout << "\n===============================================" << std::endl;
            std::cout << "                Account Details" << std::endl;
            std::cout << "\n\nName: " << Create[i].getName() << std::endl;
            std::cout << "IC Number: " << Create[i].getIC() << std::endl;
            std::cout << "Account Number: " << Create[i].getAccount() << std::endl;
            std::cout << "=================================================" << std::endl;

            std::cout << "\n\nProceeding to home screen.\n\n" << std::endl;

            system("pause");
            system("cls");

            break;

        }

    }

}

void withdraw(int i, CurrentAccount InMoney[80]) {

    std::ofstream accountFiles_input;
    std::ostringstream convert;
    std::string filename, directory;
    float money;

    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << "|                                       WITHDRAW MONEY                                           |" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;

    std::cout << "\n\nPlease input the amount you wish to withdraw: RM";
    std::cin >> money;

    while(true) {

        if (std::cin.fail()) {

            std::cout << "\n\nInvalid input.\n\nPlease key-in a valid value: RM";

            std::cin.clear();
            std::cin.ignore();
            std::cin >> money;

        }

        else {

            break;

        }

    }

    InMoney[i].withdraw(money);

    convert << InMoney[i].getAccount();
    filename = convert.str();

    directory = "Accounts/" + std::string(filename) + ".wow";

    accountFiles_input.open(directory.c_str());

    accountFiles_input << InMoney[i].getName() << std::endl;
    accountFiles_input << InMoney[i].getIC() << std::endl;
    accountFiles_input << InMoney[i].getAccount() << std::endl;
    accountFiles_input << InMoney[i].getBalance() << std::endl;
    accountFiles_input << InMoney[i].getFrozen() << std::endl;
    accountFiles_input << InMoney[i].getOverdraft() << std::endl;
    accountFiles_input << InMoney[i].getCurrentOverdraft();

    accountFiles_input.close();

    std::cout << "\n\nReturning to home screen.\n" << std::endl;

    system("pause");
    system("cls");

}

void deposit(int i, CurrentAccount OutMoney[80]) {

    std::ofstream accountFiles_input;
    std::ostringstream convert;
    std::string filename, directory;
    float money;

    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << "|                                       DEPOSIT MONEY                                            |" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;

    std::cout << "\n\nPlease input the amount you wish to deposit: RM";
    std::cin >> money;

    while(true) {

        if (std::cin.fail()) {

            std::cout << "\n\nInvalid input.\n\nPlease key-in a valid value: RM";

            std::cin.clear();
            std::cin.ignore();
            std::cin >> money;

        }

        else {

            break;

        }

    }

    OutMoney[i].deposit(money);

    convert << OutMoney[i].getAccount();
    filename = convert.str();

    directory = "Accounts/" + std::string(filename) + ".wow";

    accountFiles_input.open(directory.c_str());

    accountFiles_input << OutMoney[i].getName() << std::endl;
    accountFiles_input << OutMoney[i].getIC() << std::endl;
    accountFiles_input << OutMoney[i].getAccount() << std::endl;
    accountFiles_input << OutMoney[i].getBalance() << std::endl;
    accountFiles_input << OutMoney[i].getFrozen() << std::endl;
    accountFiles_input << OutMoney[i].getOverdraft() << std::endl;
    accountFiles_input << OutMoney[i].getCurrentOverdraft();

    accountFiles_input.close();

    std::cout << "\n\nReturning to home screen.\n" << std::endl;

    system("pause");
    system("cls");

}

void showDetails(int i, CurrentAccount Details[80]) {

    std::cout << " ------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << "|                                      ACCOUNT DETAILS                                           |" << std::endl;
    std::cout << "|                                                                                                |" << std::endl;
    std::cout << " ------------------------------------------------------------------------------------------------\n\n" << std::endl;

    Details[i].display();

    std::cout << "\n\nReturning to home screen.\n" << std::endl;

    system("pause");
    system("cls");

}

void randomNumberGenerator(int &rng) {

    srand((unsigned)time(0));
    rng = rand() % 10000;

}

#endif
