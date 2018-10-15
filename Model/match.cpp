#include "match.h"

Match::Match()
{

}

Match::Match(QDate date, Team team_1,
             Team team_2, QString result)
{
    this->date = date;
    this->team_1 = team_1;
    this->team_2 = team_2;
    this->result = result;
}

QDate Match::getDate() const
{
    return date;
}

void Match::setDate(const QDate &value)
{
    date = value;
}

Team Match::getTeam_1() const
{
    return team_1;
}

void Match::setTeam_1(const Team &value)
{
    team_1 = value;
}

Team Match::getTeam_2() const
{
    return team_2;
}

void Match::setTeam_2(const Team &value)
{
    team_2 = value;
}

QString Match::getResult() const
{
    return result;
}

void Match::setResult(const QString &value)
{
    result = value;
}


