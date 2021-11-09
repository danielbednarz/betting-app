#include "mainwindow.h"
#include "score.h"
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
    Score score;
    QString text = ui->textEdit->toPlainText();
    bool isOk;
    text.toInt(&isOk);


    if (isOk) {
        QString selectedChoice = ui->comboBox->currentText();
        ui->team_1_score->setText("");
        ui->team_2_score->setText("");

        ui->textEdit_2->append("Obstawiono " + text + " na drużynę " + selectedChoice);
        ui->textEdit->setText("");

        for(int i=0; i<=100; i++) {
            std::chrono::milliseconds timespan(15);
            std::this_thread::sleep_for(timespan);
            ui->progressBar->setValue(i);
            if(i == 50) {
                ui->team_1_score->setText(QString::number(score.DrawScore()));
            }
        }

        ui->team_2_score->setText(QString::number(score.DrawScore()));
    }






}

