#include "psql.h"
#include <iostream>


QSqlDatabase PSQL::db = QSqlDatabase();

PSQL::PSQL() {}

void PSQL::InitializePSQL() {

    PSQL::db = QSqlDatabase::addDatabase("QPSQL");

    // For local connection
    /* db.setHostName("127.0.0.1");
    db.setDatabaseName("RusichViand");
    db.setUserName("postgres");
    db.setPassword("goshashow28-_-"); */

    // For itmo server connection (for 2024)
    db.setHostName("146.185.211.205");
    db.setDatabaseName("dbstud");
    db.setUserName("itmo409224_2024");
    db.setPassword("itmo409224");

    if(!db.open()) {
        std::cout << "\033[31mError while connecting to DB: \033[0m" << db.lastError().text().toStdString();
        exit(0);
    }
    else
        std::cout << "\033[32mSuccessfuly logged to DB\033[0m, " << db.connectionName().toStdString() << std::endl;
}
