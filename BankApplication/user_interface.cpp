//
// Created by dkoch on 9/16/2024.
//

#include "customer.h"
#include "database.h"
#include "user_interface.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>

void UserInterface::login(Database& database) {
    std::cout << "Hello, welcome to The Bank of Ochoa!" << '\n';
    std::cout << "Are you an existing customer? (1 for Yes and 0 for No): ";

    std::string user_input;
    std::getline(std::cin, user_input);

    if (user_input == "1") {

        std::string customer_email;
        std::string customer_password;

		Customer customer;
        do {
            std::cout << "Email: ";
            std::getline(std::cin, customer_email);

            std::cout << "Password: ";
            customer_password = get_sensitive_data();
            std::cout << "\n";

            // Verify that the credentials are valid and that the customer exists.
            customer = database.verify_login(customer_email, customer_password);
            if (customer) {
                menu(customer);
            }
            else {
                std::cout << "Invalid login credentials.\n";
                // TODO: Main page that displays the users account information.
            }

        } while (!customer);

    }
    else if (user_input == "0") {
        std::cout << "Would you like to open an account? (1 for Yes and 0 for No): ";

        std::getline(std::cin, user_input);
        if (user_input == "1") {
            signup(database);
        }
    }
    else {
        std::cout << "Invalid input. Please enter 1 for Yes or 0 for No." << '\n';
    }
}

void UserInterface::signup(Database& database) {

    Customer new_customer = Customer();

    std::cout << "Please enter the following details.\n";
    std::cout << std::endl;

    std::cout << "Enter username: ";
    std::string username;
    std::getline(std::cin, username);
    new_customer.update_username(username);

    std::cout << "Enter password: ";
    new_customer.update_password(get_sensitive_data());

    std::cout << "Name: ";
    std::string name;
    std::getline(std::cin, name);
    new_customer.update_name(name);

    std::cout << "Age: ";
    std::string age;
    std::getline(std::cin, age);
    new_customer.update_age(age);

    std::cout << "Gender: ";
    std::string gender;
    std::getline(std::cin, gender);
    new_customer.update_gender(gender);

    std::cout << "Address: ";
    std::string address;
    std::getline(std::cin, address);
    new_customer.update_address(address);

    std::cout << "Social Security Number: ";
    new_customer.update_social_security(get_sensitive_data());

    database.enter_new_customer(new_customer);

    std::string type_of_account;
    std::cout << "Would you like to open a checking account? (1 for Yes or 0 for NO): ";
    std::getline(std::cin, type_of_account);

    std::cout << "Would you like to open a savings account? (1 for Yes or 0 for NO): ";
    std::getline(std::cin, type_of_account);

    std::cout << "Congrats! You have successfully created an account!";
}

std::string UserInterface::get_sensitive_data() {
    
    std::string sensitive_data;
    bool done = false;

    while (!done) {
        char ch = _getch();

        if (ch == INPUT::ENTER) {
            done = true;
            continue;
        }
        else if (ch == INPUT::BACKSPACE && sensitive_data.size() > 0) {
            sensitive_data.pop_back();
            std::cout << "\b \b";
            continue;
        }
        else if (ch == INPUT::BACKSPACE && sensitive_data.size() == 0) {
            continue;
        }
        
        sensitive_data.push_back(ch);
        std::cout << '*';
    }

    return sensitive_data;
}

void UserInterface::get_password_and_ssn() {

    std::cout << "Enter password: ";
    std::string password = get_sensitive_data();
  
    std::cout << "Enter Social Security Number: ";
    std::string social_security_number = get_sensitive_data();
}

void UserInterface::menu(Customer& customer) {
    std::cout << "\n=========================================================================\n";
	std::cout << '\n';
    std::cout << "Hi, " << customer.get_name() << "\n";

    std::cout << "Balance: $\n";
    std::cout << '\n';
	std::cout << "What would you like to do today?:\n";
	std::cout << "1. Deposit\n";
	std::cout << "2. Withdraw\n";
	std::cout << "3. Exit\n";
	std::cout << '\n';
	std::cout << "=========================================================================\n";
}