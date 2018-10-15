#include "team.h"

QString Team::getTrainerName() const
{
    return trainerName;
}

QString Team::getName() const
{
    return name;
}

QString Team::getTown() const
{
    return town;
}


Team::Team()
{
    this->name = "";
    this->town = "";
    this->trainerName = "";
}

Team::Team(QString name, QString town, QString trainerName)
{
    this->name = name;
    this->town = town;
    this->trainerName = trainerName;
}
