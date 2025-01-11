#pragma once

#include <string>
#include <vector>

struct UserInterface {
    void login(Database& database);
    void signup(Database& database);
    std::string get_sensitive_data();
    void get_password_and_ssn();
    void menu(Customer& customer);

    enum INPUT {
        ENTER = 13,
        BACKSPACE = 8
    };
};
