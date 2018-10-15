#ifndef MATCH_H
#define MATCH_H

#include "Model/team.h"

#include <QDate>

class Match
{
private:

    QDate date;
    Team team_1;
    Team team_2;
    QString result;

public:

    Match();

    Match(QDate date, Team team_1,
          Team team_2, QString result);

    QDate getDate() const;

    void setDate(const QDate &value);

    Team getTeam_1() const;

    void setTeam_1(const Team &value);

    Team getTeam_2() const;

    void setTeam_2(const Team &value);

    QString getResult() const;

    void setResult(const QString &value);

    friend QDataStream& operator>>(QDataStream &dataStream, Match &match);
};

#endif // MATCH_H
