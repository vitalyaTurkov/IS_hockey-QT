#include "service.h"
#include "Database/Database.h"

#include <QCryptographicHash>
#include <QList>
#include <QMessageBox>


Service::Service()
{

}

QList<Team> Service::getAllTeams()
{
    return Database::getAllTeams();
}

QList<Match> Service::getAllMatches()
{
    return Database::getAllMatches();
}

int Service::addPlayer(Player player)
{
    return Database::addPlayer(player);
}

int Service::deletePlayerByNumber(int number)
{
    return Database::deletePlayerByNumber(number);
}

QList<Player> Service::getAllPlayers()
{
    return Database::getAllPlayers();
}

int Service::addMatch(Match match)
{
    return Database::addMatch(match);
}

int Service::addTeam(Team team)
{
    return Database::addTeam(team);
}

//Считаем кол-во очков команды
int Service::calcScored(Team team)
{
    int result = 0;
    QList<Match> matches = Database::getAllMatches();
    foreach (Match match, matches)
    {
        if(team.getName() == match.getTeam_1().getName())
        {
            QList<QString> strings;

            //Считывание по-символьно до двоеточия
            int i;
            for(i = 0; i < match.getResult().size(); i++)
            {
                if(match.getResult()[i] == ":")
                {
                    break;
                }
                strings.push_back(QString(match.getResult()[i]));
            }

            //соеденение строки, которую мы посимвольно записали в список
            QString resultBuf;
            foreach(QString string, strings)
            {
                resultBuf += string;
            }
            result += resultBuf.toInt();
        }


    }
    return result;
}

//Переворачивание строки
//Например, из 20:0 => 0:20
QString Service::reverseString(QString string)
{
    QString string1, string2;

    int i = 0;
    for(i; i < string.size(); i++)
    {
        if(string[i] == ":")
        {
            break;
        }
        string1 += string[i];
    }
    i++;
    for(i; i < string.size(); i++)
    {
        string2 += string[i];
    }

    return string2 + ":" + string1;
}

QList<Player> Service::getByRole(QString role)
{
    return Database::getByRole(role);
}

//Сортировка по количеству забитых мячей
bool Service::caseInsensitiveLessThan(const Player &player_1, const Player &player_2)
{
    return player_1.getCountWashers() > player_2.getCountWashers();
}

//Сортировка по количеству забитых мячей
bool Service::caseInsensitiveMoreThan(const Player &player_1, const Player &player_2)
{
    return player_1.getCountWashers() < player_2.getCountWashers();
}

int Service::addUser(User user)
{
    return Database::addUser(user);
}

QList<User> Service::getAllUsers()
{
    return Database::getAllUsers();
}

User Service::getByLogin(QString login)
{
    return Database::getByLogin(login);
}

Team Service::getTeamByName(QString name)
{
    return Database::getTeamByName(name);
}

QList<Player> Service::getPlayersByTeam(Team team)
{
    return Database::getPlayersByTeam(team);
}

//Проверка на корректность введенных данных
//Все поля должны быть заполнены
//Поле result должно быть вида result1:result2
//Команды в выпадающих списках не должны совпадать
bool Service::isCorrectMatch(Match match)
{
    if(match.getResult().isEmpty())
    {
        QMessageBox::warning(NULL, "Введите результат", "Введите результат матча");
        return false;
    }

    QString result = match.getResult();
    QList<QString> strings;

    //Считывание по-символьно до двоеточия и проверка на то, является ли строка
    //неотрицательным числом,
    //если нет, то выводится сообщение об ошибке
    //Если двоеточия в поле результата нет, то выведется сообщение об ошибке
    int i;
    for(i = 0; i < result.size(); i++)
    {
        if(result[i] == ":")
        {
            break;
        }
        strings.push_back(QString(result[i]));
        if (i == result.size())
        {
            QMessageBox::warning(NULL, "Введите корректный результат",
                                 "Введите корректный результат матча вида 1:1");
            return false;
        }
    }
    //пропуск двоеточия
    i++;

    //соеденение строки, которую мы посимвольно записали в список
    QString resultBuf;
    foreach(QString string, strings)
    {
        resultBuf += string;
    }

    if(resultBuf.toInt() == 0 && resultBuf != "0" || resultBuf.toInt() < 0)
    {
        QMessageBox::warning(NULL, "Введите корректный результат",
                             "Введите корректный результат матча вида 1:1");
        return false;
    }

    strings.clear();
    resultBuf.clear();

    //Считывание по-символьно строки до конца и проверка
    //является ли строка неотрицательным числом
    //если нет, то выводится сообщение об ошибке
    for(i; i < result.size(); i++)
    {
        strings.push_back(QString(result[i]));
    }

    foreach(QString string, strings)
    {
        resultBuf += string;
    }

    if(resultBuf.toInt() == 0 && resultBuf != "0" || resultBuf.toInt() < 0)
    {
        QMessageBox::warning(NULL, "Введите корректный результат",
                             "Введите корректный результат матча вида 1:1");
        return false;
    }

    if(match.getTeam_1().getName() == match.getTeam_2().getName())
    {
        QMessageBox::warning(NULL, "Ошибка",
                             "Команда не может сыграть сама с собой");
        return false;
    }

    QList<Match> matches = Service::getAllMatches();
    foreach (Match matchBuf, matches)
    {
        if(matchBuf.getTeam_1().getName() == match.getTeam_2().getName() &&
                matchBuf.getTeam_2().getName() == match.getTeam_2().getName())
        {
            QMessageBox::warning(NULL, "Матч уже был записан", "Матч этих команд уже был записан ранее");
            return false;
        }
    }

    return true;
}

Team Service::getTeamByNameTeam(QString name)
{
    return Database::getTeamByNameTeam(name);
}

//Проверка на корректность введенных данных
//Все поля формы должны быть заполнены
//Если поля не заполнены, выведется сообщение о предупреждении
//Число мячей должно быть неотрицательным числом, если это не так, то выведется
//окно о предупреждении
bool Service::isCorrectPlayer(Player player)
{
    if(player.getSurname().isEmpty())
    {
        QMessageBox::warning(NULL, "Введите фамилию", "Заполните поле фамилии");
        return false;
    }
    if(player.getName().isEmpty())
    {
        QMessageBox::warning(NULL, "Введите имя", "Заполните поле имени");
        return false;
    }
    if(player.getPatronymic().isEmpty())
    {
        QMessageBox::warning(NULL, "Введите отчество", "Заполните поле отчества");
        return false;
    }

    if(player.getCountWashers() == -1)
    {
        QMessageBox::warning(NULL, "Введите корректное количество мячей", "Введите корректное количество мячей");
        return false;
    }

    if(player.getCountWashers() < 0)
    {
        QMessageBox::warning(NULL, "Введите корректное количество мячей", "Введите корректное количество мячей");
        return false;
    }

    if(player.getTeam().getName() == "")
    {
        QMessageBox::warning(NULL, "Выберите команду", "Выберите команду");
        return false;
    }


    return true;
}

//Проверка на корректность введенных данных
//Все поля формы должны быть заполнены
//Если поля не заполнены, выведется сообщение о предупреждении, окно не закроется
bool Service::isCorrectTeam(Team team)
{
    if(team.getName().isEmpty())
    {
        QMessageBox::warning(NULL, "Введите название команды", "Введите название команды");
        return false;
    }
    if(team.getTown().isEmpty())
    {
        QMessageBox::warning(NULL, "Введите название города", "Введите название города");
        return false;
    }
    if(team.getTrainerName().isEmpty())
    {
        QMessageBox::warning(NULL, "Введите имя тренера", "Введите имя тренера");
        return false;
    }
    return true;
}

bool Service::isCorrectUser(User user)
{
    if(user.getName().isEmpty())
    {
        QMessageBox::warning(NULL, "Введите свое имя", "Введите свое имя");
        return false;
    }
    if(user.getPassword().isEmpty())
    {
        QMessageBox::warning(NULL, "Введите пароль", "Введите пароль");
        return false;
    }
    if(user.getLogin().isEmpty())
    {
        QMessageBox::warning(NULL, "Введите логин", "Введите логин");
        return false;
    }
    if(getByLogin(user.getLogin()).getLogin() != "")
    {
        QMessageBox::warning(NULL, "Такой логин уже есть", "Введите другой логин, данный уже используется");
        return false;
    }
    //Проверка на посторонние символы в логине и пароле
    if(containsUncorrectSymbols(user.getLogin()) || containsUncorrectSymbols(user.getPassword()))
    {
        QMessageBox::warning(NULL, "Недопустимые символы", "Логин и пароль учётной записи должны состоять "
                                                           "из латинских букв, цифр и не содержать иных символов, включая пробел.");
        return false;
    }
    return true;
}

bool Service::containsUncorrectSymbols(QString string)
{
    QString uncorrectSymbols = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЫЬЪЭЮЯ";
    uncorrectSymbols += uncorrectSymbols.toLower();
    uncorrectSymbols += "!@#$%^&*()_+{}:;?/>.,<~`";

    foreach(QChar ch, uncorrectSymbols)
    {
        if(string.contains(ch))
        {
            return true;
        }
    }
    return false;
}

QString Service::encryption(QString string)
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(string.toUtf8());
    QString hashStr(hash.result().toHex());
    return hashStr;
}

QList<Player> Service::searchByNameOrSurname(QString name)
{
    QList<Player> players = Database::getAllPlayers();
    QList<Player> result;
    foreach(Player player, players)
    {
        if(player.getName().contains(name) || player.getSurname().contains(name)
                || (player.getName() + " " + player.getSurname()).contains(name)
                || (player.getSurname() + " " + player.getName()).contains(name))
        {
            result.push_back(player);
        }
    }
    return result;
}

QList<Player> Service::sortPlayersAscendingOrder(QList<Player> players)
{
    qSort(players.begin(), players.end(), caseInsensitiveMoreThan);
    return players;
}

QList<Player> Service::sortPlayersDescendingOrder(QList<Player> players)
{
    qSort(players.begin(), players.end(), caseInsensitiveLessThan);
    return players;
}


