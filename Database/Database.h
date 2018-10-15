#ifndef DATABASE_H
#define DATABASE_H

#include "Model/match.h"
#include "Model/player.h"
#include "Model/user.h"
#include "Model/team.h"


class Database
{
public:
    Database();
    static int addPlayer(Player player);
    static int deletePlayerByNumber(int number);
    static QList<Player> getAllPlayers();
    static int addMatch(Match match);
    static QList<Match> getAllMatches();
    static int addTeam(Team team);
    static QList<Team> getAllTeams();
    static QList<Player> getByRole(QString role);
    static int addUser(User user);
    static QList<User> getAllUsers();
    static User getByLogin(QString login);
    static Team getTeamByName(QString name);
    static QList<Player> getPlayersByTeam(Team team);
    static Team getTeamByNameTeam(QString name);

};

#endif // DATABASE_H
