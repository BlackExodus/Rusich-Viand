#include "profilemenu.h"

#include <iomanip>

int ProfileMenu::user_id = -1;

ProfileMenu::ProfileMenu() {}

void ProfileMenu::OpenProfile(int _user_id) {
    user_id = _user_id;

    handleCommands();
}

void ProfileMenu::printProfileInfo() {
    QSqlQuery q;
    q.prepare("SELECT user_name, email, phone FROM Users WHERE user_id = :user_id;");

    q.bindValue(":user_id", user_id);

    q.exec();

    if(!q.next()) {
        std::cout << "\033[31mError\033[0m: no info for user " << user_id << " provided" << std::endl;
        return;
    }

    std::cout << setiosflags(std::ios::left);

    std::cout << std::setw(3) << "id";
    std::cout << std::setw(20) << "name";
    std::cout << std::setw(30) << "email";
    std::cout << std::setw(5) << "phone" << std::endl;

    std::cout << std::setw(3) << user_id;
    std::cout << std::setw(20) << q.value(0).toString().toStdString();
    std::cout << std::setw(30) << q.value(1).toString().toStdString();
    std::cout << std::setw(5) << q.value(2).toString().toStdString() << std::endl;
}

void ProfileMenu::handleCommands(){

    std::string command;

    printProfileInfo();

    do {

        std::cout << "\033[33mcommands\033[0m: changeName; changePhone; back; exit" << std::endl;

        std::cin >> command;

        if(command == "changeName")
            ProfileMenu::changeName();
        else if(command == "changePhone")
            ProfileMenu::changePhone();
        else if(command == "back")
            return;
        else if(command == "exit")
            exit(0);
        else
            std::cout << "Unknown command: \033[31m" << command << "\033[0m" << std::endl;
    }
    while(command != "back");
}

void ProfileMenu::changeName() {
    std::string new_name;
    std::cout << "new name: ";
    std::cin >> new_name;

    QSqlQuery q;
    q.prepare("UPDATE Users SET user_name = :user_name WHERE user_id = :user_id");

    q.bindValue(":user_name", QString::fromStdString(new_name));
    q.bindValue(":user_id", user_id);

    q.exec();

    std::cout << "Successfully updated user name" << std::endl;
}

void ProfileMenu::changePhone() {
    std::string new_phone;
    std::cout << "new phone: ";
    std::cin >> new_phone;

    QSqlQuery q;
    q.prepare("UPDATE Users SET phone = :phone WHERE user_id = :user_id");

    q.bindValue(":phone", QString::fromStdString(new_phone));
    q.bindValue(":user_id", user_id);

    q.exec();

    std::cout << "Successfully updated user phone" << std::endl;
}
