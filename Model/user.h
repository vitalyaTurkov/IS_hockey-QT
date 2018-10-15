#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    User(QString login, QString password, QString name,
         QString status);
    QString getLogin() const;

    QString getPassword() const;

    QString getName() const;

    QString getStatus() const;

    friend QDataStream& operator>>(QDataStream &dataStream, User &user);

private:
    QString login;
    QString password;
    QString name;
    QString status;
};

#endif // USER_H
