#pragma once

#include "customer.h"
#include <pqxx/pqxx>
#include <iostream>

/*
* Class variables need to be defined in the declaration or the constructor initializer list.
*/

class Database {
private:
	pqxx::connection database_connection;
public:
	Database(const std::string connection_string) :
		database_connection(connection_string) {
		try {
			if (database_connection.is_open()) {
				std::cout << "Connected to database: " << database_connection.dbname() << '\n';
				prepare_database_statements(database_connection);
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Database error: " << e.what() << '\n';
		}
	}

	pqxx::connection& get_database_connection();

	/*
	* Enter a new customer into the Database.
	*/
	void enter_new_customer(Customer& new_customer);

	/*
	* Verify that user credentials are valid.
	*/
	Customer verify_login(std::string& user_name, std::string& password);

	/*
	* SQL query to insert a customer into the database.
	*/
	void prepare_insert_customer(pqxx::connection& database_connection);

	/*
	* SQL query to verify whether a customer exists in the database.
	*/
	void prepare_get_customer(pqxx::connection& database_connection);

	/*
	* Statements are prepared once per connection. Once a statement is prepared, it remains prepared for the lifetime of the
	* connection or until explicitly deallocated.
	*/
	void prepare_database_statements(pqxx::connection& db_conn);

	void execute_insert_customer(pqxx::transaction_base& transaction, std::string name, std::string age, std::string gender,
		std::string address, std::string social_security_number, std::string username, std::string password);

	pqxx::result execute_get_customer(pqxx::transaction_base& transaction, std::string user_name, std::string password);

	std::vector<unsigned char> generate_salt();
};

