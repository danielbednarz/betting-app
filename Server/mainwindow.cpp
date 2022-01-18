#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Response/response.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getToList(const QString &arg)
{
    ui->textEdit->append(arg);
}

