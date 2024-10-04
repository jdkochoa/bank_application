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
			}
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
		}
	}
	void enter_new_customer(Customer& new_customer);

	pqxx::connection& get_database_connection();

	void prepare_insert(pqxx::connection& database_connection);

	void execute_insert(pqxx::transaction_base& transaction, std::string name, std::string age, std::string gender,
		std::string address, std::string social_security_number, std::string username, std::string password);
};

