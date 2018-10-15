#include "View/mainwindow.h"
#include <QApplication>

//Старт приложения
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();

    return a.exec();
}
