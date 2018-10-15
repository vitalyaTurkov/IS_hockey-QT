#include "user.h"

User::User()
{
    this->login = "";
    this->password = "";
    this->name = "";
    this->status = "";
}

User::User(QString login, QString password, QString name,
           QString status)
{
    this->login = login;
    this->password = password;
    this->name = name;
    this->status = status;
}

QString User::getLogin() const
{
    return login;
}

QString User::getPassword() const
{
    return password;
}

QString User::getName() const
{
    return name;
}

QString User::getStatus() const
{
    return status;
}

