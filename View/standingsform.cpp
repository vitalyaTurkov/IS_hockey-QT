#include "standingsform.h"
#include "ui_standingsform.h"

#include <Model/team.h>

StandingsForm::StandingsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StandingsForm)
{
    ui->setupUi(this);
    this->setWindowTitle("Турнирная таблица");

    //Считывание из файла и сортировка всех команд по алфавиту
    QList<Team> teams = Service::getAllTeams();
    qSort(teams.begin(), teams.end(), caseInsensitiveLessThan);

    this->teams = teams;

    //Заполнение заголовков таблицы
    //В заголовки будут написаны имена всех команд как по вертикали
    //так и по горизонтали
    QStringList stringList;
    foreach (Team team, teams)
    {
        stringList << team.getName();
    }

    //Задание количества строк и столбцов турнирной таблицы
    ui->tableWidget->setRowCount(teams.size());
    ui->tableWidget->setColumnCount(teams.size());

    ui->tableWidget->setHorizontalHeaderLabels(stringList);
    ui->tableWidget->setVerticalHeaderLabels(stringList);

    //Настройка таблицы, чтоб она растягивалась на всю длинну
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    updateTable();

}

//Функция для сортировки команд по алфавиту
//Используется в qSort(team_1, team_2, caseInsensitiveLessThan)
bool StandingsForm::caseInsensitiveLessThan(const Team &team_1, const Team &team_2)
{
    return (team_1.getName() < team_2.getName());
}


//Сортировка команд по полученным очкам
//Колличество очков получено с помощью app
bool StandingsForm::caseInsensitiveLessThanScore(const Team &team_1, const Team &team_2)
{
    return Service::calcScored(team_1) > Service::calcScored(team_2);
}

//Получение номера команды в списке
int StandingsForm::getNumber(Team team)
{
    int i = 0;
    foreach (Team buf, teams)
    {
        if(buf.getName() == team.getName())
        {
            return i;
        }
        i++;
    }
    return -1;
}


//Обновление турнирной таблицы
//Считываение информации из файла и запись в таблицу
//с помощью QTableWidgetItem
void StandingsForm::updateTable()
{
    QList<Match> matches = Service::getAllMatches();
    foreach (Match match, matches)
    {
        int row = getNumber(match.getTeam_1());
        int column = getNumber(match.getTeam_2());

        QTableWidgetItem *item = new QTableWidgetItem(match.getResult());
        ui->tableWidget->setItem(row, column, item);

        //Переворачивание строки
        //Например из 3:0 => 0:3
        //Запись перевернутого результата в соответствующую ячейку
        QString matchResult = Service::reverseString(match.getResult());

        item = new QTableWidgetItem(matchResult);
        ui->tableWidget->setItem(column, row, item);
    }

}

StandingsForm::~StandingsForm()
{
    delete ui;
}

void StandingsForm::on_scored_clicked()
{
    //Считывание из файла и сортировка всех команд по алфавиту
    QList<Team> teams = Service::getAllTeams();

    QTableWidget *scoredTable = new QTableWidget();
    scoredTable->setColumnCount(1);
    scoredTable->setRowCount(teams.size());

    qSort(teams.begin(), teams.end(), caseInsensitiveLessThanScore);

    //Заполнение заголовков таблицы
    //В заголовки будут написаны имена всех команд как по вертикали
    //так и по горизонтали
    QStringList stringList;
    foreach (Team team, teams)
    {
        stringList << team.getName();
    }

    int i = 0;
    foreach (Team team, teams)
    {
        int score = Service::calcScored(team);
        QTableWidgetItem *itm = new QTableWidgetItem(QString::number(score));
        scoredTable->setItem(0, i, itm);
        i++;
    }

    //Настройка таблицы, чтоб она растягивалась на всю длинну
    scoredTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    scoredTable->setVerticalHeaderLabels(stringList);
    scoredTable->setWindowModality(Qt::ApplicationModal);
    scoredTable->setWindowTitle("Очки команд");
    scoredTable->show();
}
