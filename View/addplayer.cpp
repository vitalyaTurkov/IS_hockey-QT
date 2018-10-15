#include "addplayer.h"
#include "mainwindow.h"
#include "ui_addplayer.h"
#include "Service/service.h"

#include <QMessageBox>
#include <QDebug>

AddPlayer::AddPlayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPlayer)
{
    ui->setupUi(this);

    //Инициализация выпадающего списка с амплуа
    ui->role->addItem("Вратарь");
    ui->role->addItem("Нападающий");
    ui->role->addItem("Защитник");

}

AddPlayer::~AddPlayer()
{
    delete ui;
}

//Заполнение выпадающего списка с командами
void AddPlayer::updateComboBox()
{
    //Проверка на присутствие команды у пользователя;
    Team team_ = Service::getTeamByName(user.getName());

    if(team_.getName() == "" && user.getStatus() != "Администратор")
    {
        QMessageBox::warning(this, "У вас нет команды", "У вас нет команды");
        this->hide();
        return;
    }

    else
    {
        ui->team->addItem(team_.getName());
    }

    if(user.getStatus() == "Администратор")
    {
        foreach (Team team, teams)
        {
            ui->team->addItem(team.getName());
        }
    }

}

Player AddPlayer::getPlayer() const
{
    return player;
}

void AddPlayer::setTeams(const QList<Team> &teams)
{
    this->teams = teams;
    updateComboBox();
}


//Инициализация поля player,
//поле player потом будет записано в файл как новый игрок
//Окно закроется только если все данные введены корректно
void AddPlayer::on_ok_clicked()
{    
    Player player(ui->surname->text(),
                  ui->name->text(),
                  ui->patronymic->text(),
                  ui->birthday->date(),
                  ui->role->currentText(),
                  Service::getTeamByNameTeam(ui->team->currentText()),
                  ui->countWashers->text().toInt());

    //Проверка на неотрицательность поля с количеством забитых/полученных мячей
    //toInt() возвращает ноль, если записано не число.
    //Если поле пустое, то присваеваем минус единицу, чтобы
    //в проверке вывести сообщение об ошибке
    if(ui->countWashers->text().isEmpty() ||
            ui->countWashers->text().toInt() == 0 &&
            ui->countWashers->text() != "0")
    {
        player.setCountWashers(-1);
    }

    if(Service::isCorrectPlayer(player))
    {        
        this->player = player;
        accept();
    }
}

User AddPlayer::getUser() const
{
    return user;
}

void AddPlayer::setUser(const User &value)
{
    user = value;
}
