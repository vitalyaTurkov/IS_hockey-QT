#include "addteamform.h"
#include "ui_addteamform.h"

#include <QMessageBox>

#include <Service/service.h>

AddTeamForm::AddTeamForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTeamForm)
{
    ui->setupUi(this);
}

AddTeamForm::~AddTeamForm()
{
    delete ui;
}

Team AddTeamForm::getTeam() const
{
    return team;
}




//Инициализация поля team и закрытие окна
//поле team потом будет записано в файл как новая команда
void AddTeamForm::on_ok_clicked()
{
    Team team(ui->name->text(),
              ui->town->text(),
              ui->trainer->text());
    //Проверка на корректность вверденных данных
    if(Service::isCorrectTeam(team))
    {
        this->team = team;
        accept();
    }
}
