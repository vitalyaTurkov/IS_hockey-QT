#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Service/service.h"
#include "View/authorization.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void updateTableWidget(QList<Player> players);
    void enable();
    void updateLabelAboutuser();

    ~MainWindow();

    Authorization *getAuthorization() const;

private slots:

    void on_addPlayer_clicked();

    void on_deletePlayer_clicked();

    void on_newMatch_clicked();

    void on_addTeam_clicked();

    void on_showStandings_clicked();

    void on_forwardsRanking_clicked();

    void on_goalkeeperRanking_clicked();

    void on_action_triggered();

    void on_addUserButton_clicked();

    void on_teamsButton_clicked();

    void on_exit_triggered();

    void on_searchLine_textChanged(const QString &arg1);

    void on_allPlayersButton_clicked();

    void on_defenderRankingButton_clicked();

private:
    Ui::MainWindow *ui;
    Authorization *authorization;
};

#endif // MAINWINDOW_H
