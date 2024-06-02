#include "authmenu.h"
#include <iostream>

#include "login.h"
#include "register.h"
AuthMenu::AuthMenu() {}

User* AuthMenu::curUser = nullptr;


void AuthMenu::handleCommands() {
    std::string command;
    do {

        std::cout << "\033[33mcommands\033[0m: login; register; exit;" << std::endl;

        std::cin >> command;

        if(command == "login")
            curUser = Login::tryToLogin();
        else if(command == "register")
            Register::tryToRegister();
        else if(command == "exit")
            exit(0);
        else
            std::cout << "Unknown command: \033[31m" << command << "\033[0m" << std::endl;
    }
    while(curUser == nullptr);
}
