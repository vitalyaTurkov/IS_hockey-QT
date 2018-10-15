#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QDataStream>
#include <QCryptographicHash>

#include "addmatchform.h"
#include "addplayer.h"
#include "addteamform.h"
#include "authorization.h"
#include "mainwindow.h"
#include "standingsform.h"
#include "ui_mainwindow.h"
#include "registration.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Информационная система");

    //Добавления стандартного аккаунта администратора, если его нет
    QFile file("Users.bin");
    file.open(QIODevice::Append);

    if(file.pos() == 0)
    {
        Service::addUser(User("admin", Service::encryption("admin"), "Администратор", "Администратор"));
    }

    file.close();


    authorization = new Authorization;
    authorization->show();
    if(authorization->exec())
    {
        enable();

        //Инициализация количества колонок в таблице с игроками
        ui->tableWidgetPlayers->setColumnCount(7);

        //Инициализация заголовков таблицы
        ui->tableWidgetPlayers->setHorizontalHeaderLabels(QStringList() <<
                                                          "Фамилия" << "Имя" <<
                                                          "Отчество" << "Дата рождения" <<
                                                          "Игровое амплуа" << "Команда" <<
                                                          "Колличество забитых/пропущенных мячей");

        //Настройка таблицы, чтобы она растягивалась на всю длинну
        ui->tableWidgetPlayers->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        //Настройка таблицы, чтобы при нажатии на поле таблицы выделялась вся строка
        ui->tableWidgetPlayers->setSelectionBehavior(QAbstractItemView::SelectRows);
        updateTableWidget(Service::getAllPlayers());
    }
    else
    {
        exit(1);
    }

    updateLabelAboutuser();
    ui->searchLine->setPlaceholderText("Поиск. . .");

}

//Запись всех игроков таблицу
void MainWindow::updateTableWidget(QList<Player> players)
{
    int i = 0;
    ui->tableWidgetPlayers->setRowCount(players.size());
    foreach(Player player, players)
    {
        QTableWidgetItem *item = new QTableWidgetItem(player.getSurname());
        ui->tableWidgetPlayers->setItem(i, 0, item);

        item = new QTableWidgetItem(player.getName());
        ui->tableWidgetPlayers->setItem(i, 1, item);

        item = new QTableWidgetItem(player.getPatronymic());
        ui->tableWidgetPlayers->setItem(i, 2, item);

        item = new QTableWidgetItem(player.getBirthday().toString());
        ui->tableWidgetPlayers->setItem(i, 3, item);

        item = new QTableWidgetItem(player.getRole());
        ui->tableWidgetPlayers->setItem(i, 4, item);

        item = new QTableWidgetItem(player.getTeam().getName());
        ui->tableWidgetPlayers->setItem(i, 5, item);

        item = new QTableWidgetItem(QString::number(player.getCountWashers()));
        ui->tableWidgetPlayers->setItem(i, 6, item);

        i++;
    }
}

void MainWindow::enable()
{
    if(authorization->getUser().getStatus() == "Игрок")
    {
        ui->addPlayer->hide();
        ui->addTeam->hide();
        ui->deletePlayer->hide();
        ui->newMatch->hide();
        ui->addUserButton->hide();
    }
    if(authorization->getUser().getStatus() == "Тренер")
    {
        ui->newMatch->hide();
        ui->addTeam->hide();
        ui->addPlayer->show();
        ui->deletePlayer->show();
        ui->addUserButton->hide();
    }
    if(authorization->getUser().getStatus() == "Администратор")
    {
        ui->newMatch->show();
        ui->addTeam->show();
        ui->addPlayer->show();
        ui->deletePlayer->show();
        ui->addUserButton->show();
    }
}
//Вывод на главное окно информации о пользователе
void MainWindow::updateLabelAboutuser()
{
    QString aboutuser = "Имя пользователя: " + authorization->getUser().getName() + "\n" +
            "Статус пользователя " + authorization->getUser().getStatus();
    if(authorization->getUser().getStatus() == "Тренер")
    {
        aboutuser = aboutuser + "\nВы тренер команды " + "<<"
                + Service::getTeamByName(authorization->getUser().getName()).getName() + ">>";
    }
    ui->aboutuser->setText(aboutuser);
    QMessageBox::about(this, "Информация", "Вы были успешно авторизированны как " + authorization->getUser().getStatus());
}

//Запись игрока в файл
void MainWindow::on_addPlayer_clicked()
{
    AddPlayer *addPlayerForm = new AddPlayer(this);
    addPlayerForm->setUser(authorization->getUser());
    addPlayerForm->setTeams(Service::getAllTeams());
    addPlayerForm->setWindowModality(Qt::ApplicationModal);
    addPlayerForm->show();

    if(addPlayerForm->exec())
    {
        Service::addPlayer(addPlayerForm->getPlayer());
        updateTableWidget(Service::getAllPlayers());
    }
}

//Удаление игрока из файла
void MainWindow::on_deletePlayer_clicked()
{
    //Получение номера выделенной строки
    QModelIndex index = ui->tableWidgetPlayers->selectionModel()->currentIndex();

    if(ui->tableWidgetPlayers->selectionModel()->isSelected(index))
    {
        QList<Player> players = Service::getAllPlayers();
        Player player = players.at(index.row());
        if(player.getTeam().getTrainerName() == authorization->getUser().getName()
                || authorization->getUser().getStatus() == "Администратор")
        {
            Service::deletePlayerByNumber(index.row());
            updateTableWidget(Service::getAllPlayers());
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Вы можете удалить только своего игрока");
        }
    }
    else
    {
        QMessageBox::warning(this, "Выберите пользователя",
                             "Выберите игрока, которого хотите удалить");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Запись нового матча в файл
void MainWindow::on_newMatch_clicked()
{
    AddMatchForm *addMatchForm = new AddMatchForm(this);
    addMatchForm->setWindowModality(Qt::ApplicationModal);
    addMatchForm->show();

    if(addMatchForm->exec())
    {
        Match match_1 = addMatchForm->getMatch();
        Service::addMatch(match_1);
        Match match_2(match_1.getDate(), match_1.getTeam_2(),
                      match_1.getTeam_1(), Service::reverseString(match_1.getResult()));
        Service::addMatch(match_2);
    }
}

//Запись новой команды в файл
void MainWindow::on_addTeam_clicked()
{
    AddTeamForm *addTeamForm = new AddTeamForm(this);
    addTeamForm->setWindowModality(Qt::ApplicationModal);
    addTeamForm->show();
    if(addTeamForm->exec())
    {
        Team team = addTeamForm->getTeam();
        Service::addTeam(team);
    }
}

//Вывод турнирной таблицы
void MainWindow::on_showStandings_clicked()
{
    StandingsForm *standingsForm = new StandingsForm();
    standingsForm->setWindowModality(Qt::ApplicationModal);
    standingsForm->show();
    standingsForm->exec();
}


//Вывод рейтинга нападающих
void MainWindow::on_forwardsRanking_clicked()
{
    QList<Player> forwards = Service::getByRole("Нападающий");
    forwards = Service::sortPlayersDescendingOrder(forwards);
    updateTableWidget(forwards);
}


//Вывод рейтинга вратарей
void MainWindow::on_goalkeeperRanking_clicked()
{
    QList<Player> goalkeepers = Service::getByRole("Вратарь");
    goalkeepers = Service::sortPlayersAscendingOrder(goalkeepers);
    updateTableWidget(goalkeepers);
}

//Выход из аккаунта
void MainWindow::on_action_triggered()
{
    this->hide();
    authorization->show();
    if(authorization->exec())
    {
        this->show();
        enable();
        updateLabelAboutuser();
    }
    else
    {
        exit(1);
    }
}

Authorization *MainWindow::getAuthorization() const
{
    return authorization;
}

//Добавление нового пользователя
void MainWindow::on_addUserButton_clicked()
{
    Registration *registration = new Registration(this);
    registration->show();
    if(registration->exec())
    {
        Service::addUser(registration->getUser());
    }
}

//Вывод всех игроков по командам
void MainWindow::on_teamsButton_clicked()
{
    QList<QList<Player>> teams;

    QList<Team> _teams = Service::getAllTeams();

    foreach(Team team, _teams)
    {
        teams.push_back(Service::getPlayersByTeam(team));
    }

    QString teamsString = "";
    for(int i = 0; i < _teams.size(); i++)
    {
        for(int j = 0; j < teams[i].size(); j++)
        {
            teamsString += teams[i][j].getName() + " " +
                    teams[i][j].getSurname() + " " +
                    teams[i][j].getPatronymic()+ "\n";
        }

        QLabel *label = new QLabel;
        label->setWindowTitle(_teams[i].getName());
        label->setText("Тренер: " +
                      _teams[i].getTrainerName() + "\nКоманда:\n" + teamsString);
        label->show();
        teamsString = "";
    }
}

void MainWindow::on_exit_triggered()
{
    this->close();
}

void MainWindow::on_searchLine_textChanged(const QString &arg1)
{
    QList<Player> players = Service::searchByNameOrSurname(arg1);
    updateTableWidget(players);
}


void MainWindow::on_allPlayersButton_clicked()
{
    updateTableWidget(Service::getAllPlayers());
}

void MainWindow::on_defenderRankingButton_clicked()
{
    QList<Player> players = Service::getByRole("Защитник");
    players = Service::sortPlayersDescendingOrder(players);
    updateTableWidget(players);
}
