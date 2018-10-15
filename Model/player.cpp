#include "player.h"

#include <QDebug>

Player::Player(QString surname, QString name,
               QString patronymic, QDate birthday,
               QString role, Team team, int countWashers)
{
    this->surname = surname;
    this->name = name;
    this->patronymic = patronymic;
    this->birthday = birthday;
    this->role = role;
    this->team = team;
    this->countWashers = countWashers;
}

Player::Player()
{
}

QString Player::getSurname() const
{
    return surname;
}

void Player::setSurname(const QString &value)
{
    surname = value;
}

QString Player::getName() const
{
    return name;
}

void Player::setName(const QString &value)
{
    name = value;
}

QString Player::getPatronymic() const
{
    return patronymic;
}

void Player::setPatronymic(const QString &value)
{
    patronymic = value;
}

QDate Player::getBirthday() const
{
    return birthday;
}

void Player::setBirthday(const QDate &value)
{
    birthday = value;
}

QString Player::getRole() const
{
    return role;
}

void Player::setRole(const QString &value)
{
    role = value;
}

Team Player::getTeam() const
{
    return team;
}

void Player::setTeam(const Team &value)
{
    team = value;
}

int Player::getCountWashers() const
{
    return countWashers;
}

void Player::setCountWashers(int value)
{
    countWashers = value;
}

QString Player::toString()
{
    return surname + name + patronymic;
}




