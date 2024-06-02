#ifndef USER_H
#define USER_H
#include <iostream>

class User
{
private:
    int id;
    std::string name;
    std::string email;

public:
    User(int _id, std::string _name, std::string _email) : id(_id), name(_name), email(_email) {}

    int getId() const {return id;}
    std::string getName() const {return name;}
    std::string getEmail() const {return email;}

};

#endif // USER_H
