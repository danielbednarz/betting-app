#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->textEdit->toPlainText();
    bool isOk;
    text.toInt(&isOk);
    if (isOk) {
        QString selectedChoice = ui->comboBox->currentText();
        ui->textEdit_2->append("Obstawiono " + text + " na drużynę " + selectedChoice);
        ui->textEdit->setText("");
    }
}

