
#include "database.h"
#include <iostream>
#include <pqxx/pqxx>
#include "user_interface.h"


int main() {

    const std::string connection_string = "dbname=bank user=postgres password=#jdk_102418#";
    Database database = Database(connection_string);

    UserInterface ui;
    ui.login(database);
}