#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "Service/service.h"
#include "Model/user.h"

#include <QDialog>

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = 0);
    ~Registration();

    User getUser() const;

private slots:
    void on_ok_clicked();

private:
    Ui::Registration *ui;
    User user;
};

#endif // REGISTRATION_H
