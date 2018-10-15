#include "registration.h"
#include "ui_registration.h"

#include <QCryptographicHash>
#include <QMessageBox>
#include <QDebug>

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);

    ui->status->addItem("Игрок");
    ui->status->addItem("Тренер");
}

Registration::~Registration()
{
    delete ui;
}

User Registration::getUser() const
{
    return user;
}

//Инициализация поля user
//Позже будет поле user будет записано в файл
void Registration::on_ok_clicked()
{
    QString password;
    if(!ui->password->text().isEmpty())
    {
        password = Service::encryption(ui->password->text());
    }
    User user(ui->login->text(), password,
              ui->name->text(), ui->status->currentText());
    if(Service::isCorrectUser(user))
    {
        this->user = user;
        accept();
    }

}
