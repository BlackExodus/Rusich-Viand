#include "productlist.h"
#include <iostream>
#include "stock.h"

#include <iomanip>


ProductList::ProductList() {}


void ProductList::viewProductList() {
    QSqlQuery q;

    q.prepare("SELECT * FROM products");
    q.exec();

    std::cout << setiosflags(std::ios::left);

    std::cout << std::setw(4) << "id";
    std::cout << std::setw(20) << "name";
    std::cout << std::setw(30) << "desctiption";
    std::cout << std::setw(5) << "price" << std::endl;

    while(q.next()) {
        //std::cout << q.value(0).toInt() << ".\t" << q.value(1).toString().toStdString() << ";\t\t" << q.value(2).toString().toStdString() << ";\t\t" << q.value(3).toInt() << std::endl;

        std::cout << std::setw(4) << q.value(0).toInt();
        std::cout << std::setw(20) << q.value(1).toString().toStdString();
        std::cout << std::setw(30) << q.value(2).toString().toStdString();
        std::cout << std::setw(5) << q.value(3).toInt() << std::endl;
    }
}

void ProductList::addToCart(Cart* cart, int id) {
    cart->addToCart(id);
}

void ProductList::removeFromCart(Cart* cart, int id) {
    cart->removeFromCart(id);
}


void ProductList::handleCommands(Cart* cart) {
    std::string command;

    do {
        std::cout << "\033[33mcommands\033[0m: productList; stockList; printCart; add; remove; \033[1mbuy\033[0m; clearCart; back; exit;" << std::endl;

        std::cin >> command;

        if(command == "add") {
            std::cout << "write id: ";
            int id; std::cin >> id;
            ProductList::addToCart(cart, id);
        }
        else if(command == "remove") {
            std::cout << "write id: ";
            int id; std::cin >> id;
            ProductList::removeFromCart(cart, id);
        }
        else if (command == "productList")
            ProductList::viewProductList();
        else if (command == "stockList")
            ProductList::viewStockList();
        else if(command == "printCart")
            cart->print();
        else if(command == "clearCart")
            cart->clearCart();
        else if(command == "buy") {
            bool correct = cart->buy();
            if(correct)
                return;
        }
        else if(command == "back")
            return;
        else if(command == "exit")
            exit(0);
        else
            std::cout << "Unknown command: \033[31m" << command << "\033[0m" << std::endl;
    }
    while(command != "back");
}

void ProductList::viewStockList() {
    Stock::printAllStocks();
}
