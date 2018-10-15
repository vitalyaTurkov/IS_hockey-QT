#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include "Model/user.h"

#include <QDialog>

namespace Ui {
class Authorization;
}

class Authorization : public QDialog
{
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = 0);
    ~Authorization();

    User getUser() const;

private slots:
    void on_in_clicked();

private:
    Ui::Authorization *ui;
    User user;
};

#endif // AUTHORIZATION_H
