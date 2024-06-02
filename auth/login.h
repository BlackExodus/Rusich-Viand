#ifndef LOGIN_H
#define LOGIN_H

#include <user.h>

#include <QSqlQuery>
#include <QSqlError>


class Login {

public:
    static void printInfo();
    static User* tryToLogin();

};

#endif // LOGIN_H
