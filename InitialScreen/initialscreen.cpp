#include "initialscreen.h"
#include "ui_initialscreen.h"

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

