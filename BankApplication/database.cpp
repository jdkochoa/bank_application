
#include "database.h"
#include <iostream>
#include <pqxx/pqxx>


pqxx::connection& Database::get_database_connection() {
    return this->database_connection;
}

bool Database::verify_login(std::string& username, std::string& password) {

    try {

        pqxx::connection& db_conn = get_database_connection();
        pqxx::read_transaction RT(db_conn);
        pqxx::result query_result = execute_get_customer(RT, username, password);

        return !query_result.empty();
    }
    catch (std::exception const& e) {
        std::cout << "Database error: " << e.what() << '\n';
        return false;
    }
}

void Database::enter_new_customer(Customer& new_customer) {

    pqxx::connection& db_conn = get_database_connection();
    pqxx::work W(db_conn);
    execute_insert_customer(
        W, 
        new_customer.get_name(),
        new_customer.get_age(),
        new_customer.get_gender(), 
        new_customer.get_address(),
        new_customer.get_social_security_number(), 
        new_customer.get_username(),
        new_customer.get_password()
    );

    W.commit();
}

/*
* Inserts a new customer into the database
*/
void Database::prepare_insert_customer(pqxx::connection& database_connection) {
    database_connection.prepare(
        "insert",
        "INSERT INTO customer_data VALUES ($1, $2, $3, $4, $5, $6, $7);"
    );
}

/*
* Retrieves a customer from the database
*/
void Database::prepare_get_customer(pqxx::connection& database_connection) {
    database_connection.prepare(
        "get",
        "SELECT * FROM customer_data WHERE username = $1 AND password = $2;"
    );
}

void Database::prepare_database_statements(pqxx::connection& db_conn) {
    prepare_get_customer(db_conn);
    prepare_insert_customer(db_conn);
}

void Database::execute_insert_customer(pqxx::transaction_base& transaction,
    std::string name,
    std::string age,
    std::string gender,
    std::string address,
    std::string social_security_number,
    std::string username,
    std::string password) {
    transaction.exec_prepared("insert", name, age, gender, address, social_security_number, username, password);
}

pqxx::result Database::execute_get_customer(pqxx::transaction_base& transaction, std::string user_name, std::string password) {
    return transaction.exec_prepared("get", user_name, password);
}

