#include "addmatchform.h"
#include "Model/match.h"
#include "Model/team.h"
#include "ui_addmatchform.h"
#include "Service/service.h"

#include <QMessageBox>
#include <QDebug>

AddMatchForm::AddMatchForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMatchForm)
{
    ui->setupUi(this);

    updateComboBoxes();
}

AddMatchForm::~AddMatchForm()
{
    delete ui;
}

void AddMatchForm::updateComboBoxes()
{
    //Считываем все команды и записываем их в комбо боксы,
    //чтобы пользователь мог выбрать команду только из существующих
    QList<Team> teams = Service::getAllTeams();
    foreach (Team team, teams)
    {
        ui->team_1->addItem(team.getName());
        ui->team_2->addItem(team.getName());
    }
}


Match AddMatchForm::getMatch() const
{
    return match;
}

//Инициализация поля match, которое вне этого класса будет получено
//и записано в файл
void AddMatchForm::on_ok_clicked()
{
    //Проверка корректности введенных данных
    //В случае некоректности введенных данных выведется сообщение об ошибке,
    //окно не закроется
    //Создаем обьект матч, который будет проверен на корректность
    Match newMatch(ui->dateMatch->date(),
                   Team(Service::getTeamByNameTeam(ui->team_1->currentText())),
                   Team(Service::getTeamByNameTeam(ui->team_2->currentText())),
                   ui->result->text());

    if(Service::isCorrectMatch(newMatch))
    {
        QList<Team> teams = Service::getAllTeams();
        Team team_1;
        Team team_2;
        foreach (Team team, teams)
        {
            if(team.getName() == ui->team_1->currentText())
            {
                team_1 = team;
            }
            if(team.getName() == ui->team_2->currentText())
            {
                team_2 = team;
            }
        }
        Match match(ui->dateMatch->date(),
                    team_1,
                    team_2,
                    ui->result->text());
        this->match = match;
        accept();
    }
}
