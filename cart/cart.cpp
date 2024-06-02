#include "cart.h"
#include <iostream>
// #include <algorithm>
#include <iomanip>
#include "stock.h"


/* Initialize: get already existing cart or create a new one in BD */
Cart::Cart(int _user_id) {
    user_id = _user_id;

    QSqlQuery q;

    q.prepare("SELECT cart_id FROM Cart WHERE user_id = :user_id AND finished = 'false';");
    q.bindValue(":user_id", user_id);

    q.exec();
    // qDebug() << q.lastError().text();
    if(q.next()) { // unfinished cart already exist

        cart_id = q.value(0).toInt();

        /* Get list of already existing products in cart */
        q.prepare("SELECT product_id, product_count FROM ProductsInCart WHERE cart_id = :cart_id");
        q.bindValue(":cart_id", cart_id);
        q.exec();
        while(q.next()) {
            for(int i = 0; i < q.value(1).toInt(); ++i) // for product_count
                products.push_back(q.value(0).toInt());
        }

        std::cout << "loaded cart at id \033[32m" << cart_id << "\033[0m" << std::endl;

        /* for(int i = 0; i < products.size(); ++i) {
            std::cout << products[i] << " ";
        }
        std::cout << std::endl; */

        // Get count of products
        q.exec("SELECT COUNT(*) FROM Products;");
        if(q.next()) productCount = q.value(0).toInt();

        // Get count of Stocks
        q.exec("SELECT COUNT(*) FROM Stocks;");
        if(q.next()) stockCount = q.value(0).toInt();

    }
    else { // need new cart

        q.exec("SELECT COUNT(*) FROM Cart;");
        q.next();
        cart_id = q.value(0).toInt() + 1;

        q.prepare("INSERT INTO Cart VALUES (:cart_id, :user_id, NOW(), 'false');");
        q.bindValue(":cart_id", cart_id);
        q.bindValue(":user_id", user_id);
        //q.bindValue(":creation_date", QTime::currentTime());

        q.exec();

        //qDebug() << q.lastError().text();

        std::cout << "Cart created at id " << cart_id << " for user " << user_id << std::endl;
    }

}

void Cart::addToCart(int id) {

    if( !( (id <= productCount) || (1100 < id && id <= stockCount + 1100) ) ) {
        std::cout << "\033[31mError\033[0m: no product with id \033[31m" << id << "\033[0m" << std::endl;
        return;
    }

    products.push_back(id);

    QSqlQuery q;

    q.prepare("SELECT product_count FROM ProductsInCart WHERE cart_id = :cart_id AND product_id = :product_id;");

    q.bindValue(":cart_id", cart_id);
    q.bindValue(":product_id", id);

    q.exec();
    if(q.next()) { // need +1 to product_count
        int product_count = q.value(0).toInt() + 1;
        q.prepare("UPDATE ProductsInCart SET product_count = :product_count WHERE cart_id = :cart_id AND product_id = :product_id;");

        q.bindValue(":product_count", product_count);
        q.bindValue(":cart_id", cart_id);
        q.bindValue(":product_id", id);

        q.exec();
    }
    else {
        q.prepare("INSERT INTO ProductsInCart VALUES (:cart_id, :product_id, :product_count);");

        q.bindValue(":cart_id", cart_id);
        q.bindValue(":product_id", id);
        q.bindValue(":product_count", 1);

        q.exec();
    }

    if(q.lastError().text() != "") {
        std::cout << "Something went wrong...\n";
        return;
    }

    std::cout << "Successfuly added product with id " << id << "\n";
}

void Cart::removeFromCart(int id) { // should be used to delete 1 elem
    int index1 = -1; // find index of firest elem = product_id
    int index2 = -1; // do we have another elements?
    for(int i = 0; i < products.size() && index2 == -1; ++i) {
        if(products[i] == id) {
            if(index1 == -1) index1 = i;
            else if(index2 == -1) index2 = i;
        }
    }

    // std::cout << "index 1: " << index1 << " , index 2: " << index2 << std::endl;

    if(index1 == -1)
        std::cout << "\033[31mError\033[0m: no product with id " << id << std::endl;
    else {
        products.erase(products.begin() + index1);

        QSqlQuery q;

        if(index2 == -1) {
            q.prepare("DELETE FROM ProductsInCart WHERE cart_id = :cart_id AND product_id = :product_id");

            q.bindValue(":cart_id", cart_id);
            q.bindValue(":product_id", id);

            q.exec();

            //std::cout << q.lastError().text().toStdString() << std::endl;
        }
        else {
            q.prepare("UPDATE ProductsInCart SET product_count = product_count - 1 WHERE cart_id = :cart_id AND product_id = :product_id");

            q.bindValue(":cart_id", cart_id);
            q.bindValue(":product_id", id);

            q.exec();
        }

        std::cout << "Successfully removed product with id " << id << std::endl;

        //std::cout << q.lastError().text().toStdString() << "\n";
    }
}

void Cart::print() {

    // TODO: Вынести логику товаров и акций в отдельный parent class

    std::cout << "Cart \033[34m" << cart_id << "\033[0m for user \033[34m" << user_id << "\033[0m: " << std::endl;

    QSqlQuery q;
    for(int i = 0; i < products.size(); ++i) {

        if(products[i] < 1000) {
            q.prepare("SELECT product_name, price FROM Products WHERE product_id = :product_id;");

            q.bindValue(":product_id", products[i]);

            q.exec();

            std::cout << setiosflags(std::ios::left);
            if(!q.next()) {
                std::cout << "Some error: " << q.lastError().text().toStdString() << std::endl;
                return;
            }
            std::cout << std::setw(3) << products[i];
            std::cout << std::setw(10) << q.value(0).toString().toStdString();
            std::cout << std::setw(5) << q.value(1).toInt() << "\n";
        }
        else {
            q.prepare("SELECT * FROM Stocks where stock_id = :stock_id");
            q.bindValue(":stock_id", products[i]);
            q.exec();
            if(q.next()) {
                std::cout << "STOCK \033[033m" << products[i] << "\033[0m, price: \033[32m" << q.value(3).toInt() << "\033[0m\n";

                Stock::printStock(q.value(0).toInt());
                std::cout << "-----------------------------------\n";
            }
        }
    }

}

void Cart::clearCart() {
    if(!products.size()) {
        std::cout << "Cart is alredy cleared!" << std::endl;
        return;
    }

    products.clear();

    QSqlQuery q;

    q.prepare("DELETE FROM ProductsInCart WHERE cart_id = :cart_id;");
    q.bindValue(":cart_id", cart_id);
    q.exec();

    std::cout << "Successfully cleared a cart" << std::endl;
}

bool Cart::buy() {
    if(!products.size()) {
        std::cout << "\033[31mError\033[31m: No products in cart" << std::endl;
        return 0;
    }

    int sum = 0;
    QSqlQuery q;
    for(auto it : products) {
        if(it < 1000) {
            q.prepare("SELECT price FROM Products WHERE product_id = :product_id;");
            q.bindValue(":product_id", it);
            q.exec();
        }
        else {
            q.prepare("SELECT price FROM Stocks WHERE stock_id = :stock_id");
            q.bindValue(":stock_id", it);
            q.exec();
        }

        if(!q.next()) {
            std::cout << "Something went wrong..." << std::endl;
            return 0;
        }

        sum += q.value(0).toInt();

    }

    std::cout << "Summary: \033[32m" << sum << "\033[0m" << std::endl;

    clearCart();

    q.prepare("UPDATE Cart SET finished = true WHERE cart_id = :cart_id;");
    q.bindValue(":cart_id", cart_id);
    q.exec();

    return 1;
}
