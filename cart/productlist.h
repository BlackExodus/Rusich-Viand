#ifndef PRODUCTLIST_H
#define PRODUCTLIST_H

#include <QSqlQuery>
#include <QSqlError>

#include <cart/cart.h>


class ProductList
{
public:
    ProductList();

    static void viewProductList();

    static void addToCart(Cart* cart, int id);

    static void removeFromCart(Cart* cart, int id);

    static void handleCommands(Cart* cart);

    static void viewStockList();

};

#endif // PRODUCTLIST_H
