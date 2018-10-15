#ifndef STANDINGSFORM_H
#define STANDINGSFORM_H

#include "Service/service.h"

#include <QDialog>

namespace Ui {
class StandingsForm;
}

class StandingsForm : public QDialog
{
    Q_OBJECT

public:

    explicit StandingsForm(QWidget *parent = 0);

    static bool caseInsensitiveLessThan(const Team &team_1, const Team &team_2);

    static bool caseInsensitiveLessThanScore(const Team &team_1, const Team &team_2);

    int getNumber(Team team);

    void updateTable();

    ~StandingsForm();

private slots:

    void on_scored_clicked();

private:
    Ui::StandingsForm *ui;
    QList<Team> teams;
};

#endif // STANDINGSFORM_H
