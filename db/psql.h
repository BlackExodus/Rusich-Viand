#ifndef PSQL_H
#define PSQL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class PSQL
{
private:
    static QSqlDatabase db;

public:
    PSQL();

    static void InitializePSQL();
    static QSqlDatabase GetDB() {return db;}
};

#endif // PSQL_H
