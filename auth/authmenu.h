#ifndef AUTHMENU_H
#define AUTHMENU_H

#include "user.h"

class AuthMenu
{
private:
    static void registerMenu();
    static User* curUser;

public:
    AuthMenu();
    static void handleCommands();
    static User* getUser() {return curUser;}
};

#endif // AUTHMENU_H
