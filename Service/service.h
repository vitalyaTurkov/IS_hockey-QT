#ifndef SERVICE_H
#define SERVICE_H

#include <QList>
#include <Model/match.h>
#include <Model/player.h>
#include <Model/user.h>
#include <Model/team.h>


class Service
{
public:
    Service();
    static QList<Team> getAllTeams();
    static QList<Match> getAllMatches();
    static QList<Player> getAllPlayers();
    static QList<User> getAllUsers();

    static int deletePlayerByNumber(int number);

    static int addMatch(Match match);
    static int addTeam(Team team);
    static int addUser(User user);
    static int addPlayer(Player player);

    static int calcScored(Team team);

    static QString reverseString(QString string);
    static QList<Player> getByRole(QString role);

    static bool caseInsensitiveLessThan(const Player &player_1, const Player &player_2);
    static bool caseInsensitiveMoreThan(const Player &player_1, const Player &player_2);

    static User getByLogin(QString login);
    static Team getTeamByName(QString name);
    static QList<Player> getPlayersByTeam(Team team);
    static Team getTeamByNameTeam(QString team);

    static bool isCorrectPlayer(Player player);
    static bool isCorrectTeam(Team team);
    static bool isCorrectUser(User user);
    static bool isCorrectMatch(Match match);

    static bool containsUncorrectSymbols(QString string);
    static QString encryption(QString string);

    static QList<Player> searchByNameOrSurname(QString name);

    static QList<Player> sortPlayersAscendingOrder(QList<Player> players);
    static QList<Player> sortPlayersDescendingOrder(QList<Player> players);


};

#endif // SERVICE_H
