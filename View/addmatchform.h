#ifndef ADDMATCHFORM_H
#define ADDMATCHFORM_H

#include "Model/match.h"

#include <QDialog>

namespace Ui {
class AddMatchForm;
}

class AddMatchForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddMatchForm(QWidget *parent = 0);

    ~AddMatchForm();

    void updateComboBoxes();

     Match getMatch() const;

private slots:

     void on_ok_clicked();

private:
    Ui::AddMatchForm *ui;
    Match match;
};

#endif // ADDMATCHFORM_H
