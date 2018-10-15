#include "Database.h"
#include "Model/datastreamconf.cpp"

#include <QDataStream>
#include <QFile>
#include <QDebug>

Database::Database()
{

}

//Запись игрока в файл
int Database::addPlayer(Player player)
{
    QFile file("Players.bin");
    if(file.open(QIODevice::Append))
    {
        //Для того, чтобы файл был бинарный
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_4_2);
        stream << player;
        if(stream.status() != QDataStream::Ok)
        {
            qDebug() << "Ошибка записи";
            return -1;
        }
    }
    file.close();
    return 0;
}

//Получение всех игроков из файла
QList<Player> Database::getAllPlayers()
{
    QFile file("Players.bin");
    QList<Player> players;
    Player player;

    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_4_2);
        while(!stream.atEnd())
        {
            stream >> player;
            if(stream.status() != QDataStream::Ok)
            {
                qDebug() << "Ошибка записи";
            }
            players.push_back(player);
        }
    }
    file.close();
    return players;
}

//Удаление из файла игрока по номеру его расположения в файле
//Удаление происходит за счет считывания в буферный список только
//тех игроков, которые находятся не под номером number и файл
//перезаписывается по-новой
int Database::deletePlayerByNumber(int number)
{
    QFile file("Players.bin");

    QList<Player> players = getAllPlayers();

    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_4_2);

        int i = 0;
        foreach(Player player, players)
        {
            if(i != number)
            {
                stream << player;
            }
            if(stream.status() != QDataStream::Ok)
            {
                qDebug() << "Ошибка записи";
                return -1;
            }
            i++;
        }
    }
    file.close();
    return 0;
}

//Запись матча в файл
int Database::addMatch(Match match)
{
    QFile file("Matches.bin");
    if(file.open(QIODevice::Append))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_4_2);
        stream << match;
        if(stream.status() != QDataStream::Ok)
        {
            qDebug() << "Ошибка записи";
            return -1;
        }
    }
    file.close();
    return 0;
}

//Считывание всех матчей из файла
QList<Match> Database::getAllMatches()
{
    QFile file("Matches.bin");
    QList<Match> matches;
    Match match;

    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_4_2);
        while(!stream.atEnd())
        {
            stream >> match;
            if(stream.status() != QDataStream::Ok)
            {
                qDebug() << "Ошибка записи";
            }
            matches.push_back(match);
        }
    }
    file.close();
    return matches;
}

//Запись команды в файл
int Database::addTeam(Team team)
{
    QFile file("Teams.bin");
    if(file.open(QIODevice::Append))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_4_2);
        stream << team;
        if(stream.status() != QDataStream::Ok)
        {
            qDebug() << "Ошибка записи";
            return -1;
        }
    }
    file.close();
    return 0;
}

//Считывание всех команд из файла
QList<Team> Database::getAllTeams()
{
    QFile file("Teams.bin");
    QList<Team> teams;
    Team team;

    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_4_2);
        while(!stream.atEnd())
        {
            stream >> team;
            if(stream.status() != QDataStream::Ok)
            {
                qDebug() << "Ошибка записи";
            }
            teams.push_back(team);
        }
    }
    file.close();
    return teams;
}

//Получение игроков с ролью, которая приходит в аргументы
QList<Player> Database::getByRole(QString role)
{
    QList<Player> teams = getAllPlayers();
    QList<Player> teamsResult;
    foreach(Player team, teams)
    {
        if(team.getRole() == role)
        {
            teamsResult.push_back(team);
        }
    }
    return teamsResult;
}

//Добавление пользователя в файл
int Database::addUser(User user)
{
    QFile file("Users.bin");
    if(file.open(QIODevice::Append))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_4_2);
        stream << user;
        if(stream.status() != QDataStream::Ok)
        {
            qDebug() << "Ошибка записи";
            return -1;
        }
    }
    file.close();
    return 0;
}

//Получение из файла всех пользователей
QList<User> Database::getAllUsers()
{
    QFile file("Users.bin");
    QList<User> users;
    User user;

    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_4_2);
        while(!stream.atEnd())
        {
            stream >> user;
            if(stream.status() != QDataStream::Ok)
            {
                qDebug() << "Ошибка записи";
            }
            users.push_back(user);
            qDebug() << user.getLogin() << user.getPassword();
        }
    }
    file.close();
    return users;
}

//Получение пользователя из файла по логину пользователя
User Database::getByLogin(QString login)
{
    QFile file("Users.bin");
    User user;

    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_4_2);
        while(!stream.atEnd())
        {
            stream >> user;
            if(user.getLogin() == login)
            {
                return user;
            }
            if(stream.status() != QDataStream::Ok)
            {
                qDebug() << "Ошибка записи";
            }
        }
    }
    file.close();
    return User();
}


//Получение команды по имени тренера
Team Database::getTeamByName(QString name)
{
    QFile file("Teams.bin");
    Team team;

    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_4_2);
        while(!stream.atEnd())
        {
            stream >> team;
            if(team.getTrainerName() == name)
            {
                return team;
            }
            if(stream.status() != QDataStream::Ok)
            {
                qDebug() << "Ошибка записи";
            }
        }
    }
    file.close();
    return Team();
}

QList<Player> Database::getPlayersByTeam(Team team)
{
    QList<Player> players = getAllPlayers();
    QList<Player> resultList;

    foreach(Player player, players)
    {
        if(player.getTeam().getName() == team.getName())
        {
            resultList.push_back(player);
        }
    }
    if (resultList.isEmpty())
    {
        resultList.push_back(Player());
    }
    return resultList;
}

Team Database::getTeamByNameTeam(QString name)
{
    QFile file("Teams.bin");
    Team team;

    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_4_2);
        while(!stream.atEnd())
        {
            stream >> team;
            if(team.getName() == name)
            {
                return team;
            }
            if(stream.status() != QDataStream::Ok)
            {
                qDebug() << "Ошибка записи";
            }
        }
    }
    file.close();
    return Team();
}




