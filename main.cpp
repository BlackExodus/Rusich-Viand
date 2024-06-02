#include <QCoreApplication>
#include <iostream>

#include <user.h>
#include "auth/login.h"
#include "cart/productlist.h"
#include "cart/cart.h"
#include "db/psql.h"
#include "profile/profilemenu.h"
#include "auth/authmenu.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PSQL::InitializePSQL();

    /* Start process of auth */
    AuthMenu::handleCommands();

    User* curUser = AuthMenu::getUser();

    /* User* curUser = nullptr;
    while(!curUser)
        curUser = Login::tryToLogin(); */

    cout << curUser->getId() << " || " << curUser->getName() << " || " << curUser->getEmail() << endl;
    string command;
    do {
        cout << "\033[33mcommands\033[0m: storeMenu; profileMenu; exit" << std::endl;

        cin >> command;

        if(command == "storeMenu") {
            ProductList::handleCommands(new Cart(curUser->getId()));
        }
        else if(command == "profileMenu")
            ProfileMenu::OpenProfile(curUser->getId());
        else if(command == "exit")
            exit(0);
        else
            cout << "Unknown command: \033[31m" << command << "\033[0m" << endl;
    }
    while(command != "exit");


    return 0;
}
