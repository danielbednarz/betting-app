#include "mainwindow.h"
#include "InitialScreen/initialscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitialScreen w;
    w.show();
    return a.exec();
}
