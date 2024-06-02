#ifndef CART_H
#define CART_H

#include <vector>

#include <QSqlQuery>
#include <QSqlError>

class Cart
{
private:
    int cart_id = -1;
    std::vector<int> products;
    int user_id;

    int productCount;
    int stockCount;

public:
    Cart(int _user_id);
    void addToCart(int id);
    void removeFromCart(int id);
    std::vector<int> getCart() const {return products;}
    void print();
    void clearCart();

    bool buy();
};

#endif // CART_H
