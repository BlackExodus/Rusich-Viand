#ifndef STOCK_H
#define STOCK_H

#include <QSqlQuery>
#include <QSqlError>

class Stock
{
public:
    Stock();
    static void printAllStocks();

    static void printStock(int stock_id);
};

#endif // STOCK_H
