#include "mainwindow.h"

#include <QApplication>
#include <cstdlib>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    consoleLog("Запуск программы");
    return 0;
}
