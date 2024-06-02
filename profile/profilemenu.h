#ifndef PROFILEMENU_H
#define PROFILEMENU_H

#include "user.h"

#include <QSqlQuery>
#include <QSqlError>

class ProfileMenu
{
private:
    static int user_id;

    static void changeName();
    static void changePhone();
    static void printProfileInfo();


public:
    ProfileMenu();

    static void OpenProfile(int user_id);
    static void handleCommands();

};

#endif // PROFILEMENU_H
