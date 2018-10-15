#ifndef ADDTEAMFORM_H
#define ADDTEAMFORM_H

#include "Model/team.h"

#include <QDialog>

namespace Ui {
class AddTeamForm;
}

class AddTeamForm : public QDialog
{
    Q_OBJECT

public:

    explicit AddTeamForm(QWidget *parent = 0);

    ~AddTeamForm();

    Team getTeam() const;

private slots:

    void on_ok_clicked();

private:
    Ui::AddTeamForm *ui;
    Team team;
};

#endif // ADDTEAMFORM_H
