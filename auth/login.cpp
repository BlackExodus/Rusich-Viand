#include "auth/login.h"
#include <iostream>

#include "db/psql.h"

User* Login::tryToLogin() {
    std::cout << "Write your email: \n";
    std::string email; // std::cin >> email;
    std::getline(std::cin >> std::ws, email);

    std::cout << "Write your password: \n";
    std::string password; // std::cin >> password;
    std::getline(std::cin >> std::ws, password);

    QSqlQuery q;

    q.prepare("SELECT user_id, user_name, password FROM Users WHERE email = :email;");
    q.bindValue(":email", QString::fromStdString(email));

    q.exec();

    std::string passwordDB;
    if(q.next()) {
        passwordDB = q.value(2).toString().toStdString();
        // std:: cout << "password DB: " << passwordDB << std::endl;
    }

    if(passwordDB.size() && passwordDB == password)
        return new User(q.value(0).toInt(), q.value(1).toString().toStdString(), passwordDB);
    else
        std::cout << "Uncorrect email or password, DB error: " << PSQL::GetDB().lastError().text().toStdString() << ";" << std::endl;

    return nullptr;
}
