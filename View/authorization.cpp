#include "authorization.h"
#include "registration.h"
#include "ui_authorization.h"
#include "Service/service.h"

#include <QCryptographicHash>
#include <QMessageBox>

Authorization::Authorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authorization)
{
    ui->setupUi(this);

    this->setWindowTitle("Авторизация");

    //Вывод звездочек вместо вводимых символов
    ui->password->setEchoMode(QLineEdit::Password);
    ui->login->setPlaceholderText("Введите логин. . .");
    ui->password->setPlaceholderText("Введите пароль. . .");
}

Authorization::~Authorization()
{
    delete ui;
}

//Авторизация
//Считывание всех пользователей из файла и проверка
//есть ли введенный пользователь в файле
void Authorization::on_in_clicked()
{
    QList<User> users = Service::getAllUsers();

    foreach (User user, users)
    {
        if(user.getLogin() == ui->login->text() &&
                user.getPassword() == Service::encryption(ui->password->text()))
        {
            this->user = user;
            accept();
            return;
        }
    }

    QMessageBox::warning(this, "Ошибка", "Неверные логин или пароль");
}

User Authorization::getUser() const
{
    return user;
}

