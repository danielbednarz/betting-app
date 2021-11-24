#include "initialscreen.h"
#include "ui_initialscreen.h"
#include "mainwindow.h"

InitialScreen::InitialScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InitialScreen)
{
    ui->setupUi(this);
}

InitialScreen::~InitialScreen()
{
    delete ui;
}

void InitialScreen::on_pushButton_8_clicked()
{
    InitialScreen::close();
}


void InitialScreen::on_aboutGameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void InitialScreen::on_backFromAboutGameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void InitialScreen::on_loginButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void InitialScreen::on_backToMenuButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void InitialScreen::on_backToMenuFromRegisterButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void InitialScreen::on_registerButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void InitialScreen::on_loginSubmitButton_clicked()
{
    mainWindow = new MainWindow(this);
    mainWindow->show();
    InitialScreen::hide();

}


void InitialScreen::on_confirmRegisterButton_clicked()
{
    mainWindow = new MainWindow(this);
    mainWindow->show();
    InitialScreen::hide();
}

