#ifndef PLAYER_H
#define PLAYER_H

#include "Model/team.h"

#include <QDataStream>
#include <qdatetime.h>
#include <qstring.h>

class Player
{
public:
    Player(QString surname, QString name,
           QString patronymic, QDate birthday,
           QString role, Team team, int countWashers);
    Player();
    QString getSurname() const;
    void setSurname(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getPatronymic() const;
    void setPatronymic(const QString &value);

    QDate getBirthday() const;
    void setBirthday(const QDate &value);

    QString getRole() const;
    void setRole(const QString &value);

    Team getTeam() const;
    void setTeam(const Team &value);

    int getCountWashers() const;
    void setCountWashers(int value);

    QUuid getId() const;

    QString toString();

    friend QDataStream& operator>>(QDataStream& dataStream, Player& player);

private:
    QString surname;
    QString name;
    QString patronymic;
    QDate birthday;
    QString role;
    Team team;
    int countWashers;
};

#endif // PLAYER_H
