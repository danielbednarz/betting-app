#include "MainWindow/mainwindow.h"
#include "InitialScreen/initialscreen.h"
#include "DbConnector/DbConnector.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitialScreen w;
    DbConnector::SeedData();
    w.show();
    return a.exec();
}
