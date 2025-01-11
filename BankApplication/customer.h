#pragma once

#include <string>

class Customer {
private:
    std::string username;
    std::string password;
    std::string name;
    std::string age;
    std::string address;
    std::string social_security_number;
    std::string gender;
    int balance = 0; // in-line class initialization
public:
    Customer() = default;
    Customer(const std::string& name, std::string age, const std::string& address,
        const std::string& social_security, std::string gender) :
        name(name),
        age(age),
        address(address),
        social_security_number(social_security),
        gender(gender)
    {};

	explicit operator bool() const {
		return !name.empty();
	}

    void update_username(std::string username);
    void update_password(std::string password);
    void update_name(std::string name);
    void update_age(std::string age);
    void update_address(std::string& address);
    void update_social_security(std::string social_security);
    void update_gender(std::string gender);

    std::string get_username();
    std::string get_password();
    std::string get_name();
    std::string get_age();
    std::string get_address();
    std::string get_social_security_number();
    std::string get_gender();
};