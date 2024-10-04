//
// Created by dkoch on 9/26/2024.
//

#include "customer.h"

void Customer::update_username(std::string username) {
    this->username = username;
}

void Customer::update_password(std::string password) {
    this->password = password;
}

void Customer::update_name(std::string name) {
    this->name = name;
}

void Customer::update_age(std::string age) {
    this->age = age;
}

void Customer::update_address(std::string& address) {
    this->address = address;
}

void Customer::update_social_security(std::string social_security) {
    this->social_security_number = social_security;
}

void Customer::update_gender(std::string gender) {
    this->gender = gender;
}

std::string Customer::get_username() {
    return this->username;
}

std::string Customer::get_password() {
    return this->password;
}

std::string Customer::get_name() {
    return this->name;
}

std::string Customer::get_age() {
    return this->age;
}

std::string Customer::get_address() {
    return this->address;
}

std::string Customer::get_social_security_number() {
    return this->social_security_number;
}

std::string Customer::get_gender() {
    return this->gender;
}