#include "stock.h"
#include <iostream>
#include <iomanip>

Stock::Stock() {}

void Stock::printAllStocks() {

    QSqlQuery stockQ;

    stockQ.exec("SELECT stock_id, date(begin_date), date(end_date), price FROM Stocks WHERE begin_date < NOW() AND NOW() < end_date;");

    std::cout << setiosflags(std::ios::left);
    std::cout << std::setw(6) << "id";
    std::cout << std::setw(12) << "begin_date";
    std::cout << std::setw(12) << "end_date";
    std::cout << std::setw(5) << "price" << std::endl;


    while(stockQ.next()) {
        // Основная ифнормация об акции
        std::cout << setiosflags(std::ios::left);
        std::cout << "\033[1m" << std::setw(6) << stockQ.value(0).toInt() << "\033[0m";
        std::cout << std::setw(12) <<stockQ.value(1).toString().toStdString();
        std::cout << std::setw(12) << stockQ.value(2).toString().toStdString();
        std::cout << std::setw(5) << "\033[32m" << stockQ.value(3).toInt() << "\033[0m\n";

        printStock(stockQ.value(0).toInt());

        std::cout << "-----------------------------------\n";

    }

}

void Stock::printStock(int stock_id) {
    // Какие продукты в этой акции?
    QSqlQuery productQ;
    productQ.prepare("SELECT Products.product_id, Products.product_name, Products.description "
                     "FROM stockProducts "
                     "LEFT JOIN Products ON "
                     "stockProducts.product_id = Products.product_id "
                     "WHERE stock_id = :stock_id;");
    productQ.bindValue(":stock_id", stock_id);
    productQ.exec();

    while(productQ.next()) {
        std::cout << std::setw(3) << productQ.value(0).toInt();
        std::cout << std::setw(10) << productQ.value(1).toString().toStdString();
        std::cout << std::setw(35) << productQ.value(2).toString().toStdString() << "\n";
    }
}
