#include "mainwindow.h"

#include <QApplication>

#include <Response/response.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Response response;
    QObject::connect(&response, &Response::addToList, &w, &MainWindow::getToList);
    w.show();
    return a.exec();
}
