#include "match.h"
#include "player.h"
#include "user.h"

#include <QDataStream>


//В этом файле происходит сериализация пользовательских типов данных
//В дальнейшем это позволит записывать в двоичный файл, например, таким образом:
//dataStream << team; dataStream << match;
QDataStream& operator<<(QDataStream &dataStream, const Team &team)
{
    dataStream << team.getName() << team.getTown() <<
                  team.getTrainerName();
    return dataStream;
}

QDataStream& operator>>(QDataStream &dataStream, Team &team)
{
    dataStream >> team.name >> team.town >>
                  team.trainerName;
    return dataStream;
}

QDataStream& operator<<(QDataStream &dataStream, const Match &match)
{
    dataStream << match.getDate() << match.getTeam_1() <<
                  match.getTeam_2() << match.getResult();
    return dataStream;
}

QDataStream& operator>>(QDataStream &dataStream, Match &match)
{
    dataStream >> match.date >> match.team_1 >>
                  match.team_2 >> match.result;
    return dataStream;
}

QDataStream& operator<<(QDataStream &dataStream, const Player &player)
{
    dataStream << player.getSurname() << player.getName() <<
                  player.getPatronymic() << player.getBirthday() <<
                  player.getTeam() << player.getRole() <<
                  player.getCountWashers();
    return dataStream;
}

QDataStream& operator>>(QDataStream &dataStream, Player &player)
{
    dataStream >> player.surname >> player.name >>
                  player.patronymic >> player.birthday >>
                  player.team >> player.role >>
                  player.countWashers;
    return dataStream;
}

QDataStream& operator<<(QDataStream &dataStream, const User &user)
{
    dataStream << user.getLogin() << user.getName() <<
                  user.getPassword() << user.getStatus();
    return dataStream;
}

QDataStream& operator>>(QDataStream &dataStream, User &user)
{
    dataStream >> user.login >> user.name >>
                  user.password >> user.status;
    return dataStream;
}


