#ifndef ADDPLAYER_H
#define ADDPLAYER_H

#include "Model/player.h"
#include "Model/user.h"

#include <QDialog>

namespace Ui {
class AddPlayer;
}

class AddPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit AddPlayer(QWidget *parent = 0);
    ~AddPlayer();

    void updateComboBox();
    Player getPlayer() const;

    void setTeams(const QList<Team> &teams);

    User getUser() const;
    void setUser(const User &value);

private slots:

    void on_ok_clicked();

private:
    Ui::AddPlayer *ui;
    Player player;
    QList<Team> teams;
    User user;
};

#endif // ADDPLAYER_H
