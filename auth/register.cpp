#include "register.h"
#include <iostream>

#include <QSqlQuery>
#include <QSqlError>


Register::Register() {}


void Register::tryToRegister() {
    std::cout << "Write your name: \n";
    std::string name;
    std::getline(std::cin >> std::ws, name);


    std::cout << "Write your email: \n";
    std::string email; // std::cin >> email;
    std::getline(std::cin >> std::ws, email);

    std::cout << "Write your password: \n";
    std::string password; // std::cin >> password;
    std::getline(std::cin >> std::ws, password);

    std::cout << "Confirm password: \n";
    std::string confirmPassword;//  std::cin >> confirmPassword;
    std::getline(std::cin >> std::ws, confirmPassword);


    if(password != confirmPassword) {
        std::cout << "\033[31mError\033[0m: passwords don't match" << std::endl;
        return;
    }

    std::cout << "Write your phone: \n";
    std::string phone; std::cin >> phone;

    QSqlQuery q;

    q.exec("SELECT COUNT(*) FROM Users");
    q.next();
    int id = q.value(0).toInt() + 1;

    q.prepare("INSERT INTO Users VALUES (:id, :name, :email, :password, :phone);");

    q.bindValue(":id", id);
    q.bindValue(":name", QString::fromStdString(name));
    q.bindValue(":email", QString::fromStdString(email));
    q.bindValue(":password", QString::fromStdString(password));
    q.bindValue(":phone", QString::fromStdString(phone));

    q.exec();

    if(q.lastError().text().toStdString() != "")
        std::cout << "\033[31mError\033[0m: account with email " << email << " alredy exist" << std::endl;
}
