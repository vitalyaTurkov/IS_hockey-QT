#ifndef TEAM_H
#define TEAM_H

#include <QString>

class Team
{
private:
    QString name;
    QString town;
    QString trainerName;
public:
    Team();
    Team(QString name, QString town, QString trainerName);
    QString getName() const;
    QString getTown() const;
    QString getTrainerName() const;

    friend QDataStream& operator>>(QDataStream &dataStream, Team &team);
};

#endif // TEAM_H
