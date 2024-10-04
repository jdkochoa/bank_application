
#include "database.h"
#include <iostream>
#include <pqxx/pqxx>


pqxx::connection& Database::get_database_connection() {
    return this->database_connection;
}

void Database::enter_new_customer(Customer& new_customer) {

    pqxx::connection& db_conn = get_database_connection();
    prepare_insert(db_conn);
    pqxx::work W(db_conn);
    execute_insert(W, new_customer.get_name(), new_customer.get_age(), new_customer.get_gender(), new_customer.get_address(),
        new_customer.get_social_security_number(), new_customer.get_username(), new_customer.get_password());
    W.commit();
}

void Database::prepare_insert(pqxx::connection& database_connection) {
    database_connection.prepare(
        "insert",
        "INSERT INTO customer_data VALUES ($1, $2, $3, $4, $5, $6, $7);"
    );
}

void Database::execute_insert(pqxx::transaction_base& transaction,
    std::string name,
    std::string age,
    std::string gender,
    std::string address,
    std::string social_security_number,
    std::string username,
    std::string password) {
    transaction.exec_prepared("insert", name, age, gender, address, social_security_number, username, password);
}

