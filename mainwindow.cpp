#include "mainwindow.h"
#include "score.h"
#include "ui_mainwindow.h"
#include "bet.h"
#include <vector>
Bet bet;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bet.DrawOdds();
    vector<float> odds = bet.GetOdds();
    ui->betHomeButton->setText(QString::number(odds[0]));
    ui->betDrawButton->setText(QString::number(odds[1]));
    ui->betAwayButton->setText(QString::number(odds[2]));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ResetAfterBet()
{
    bet.DrawOdds();
    vector<float> odds = bet.GetOdds();
    ui->betHomeButton->setText(QString::number(odds[0]));
    ui->betDrawButton->setText(QString::number(odds[1]));
    ui->betAwayButton->setText(QString::number(odds[2]));
    // do ustalenia, czy da sie to zmienic
    bet.SetSelectedBetOption(-1);
    ui->betHomeButton->setStyleSheet("background-color: #6d6d6d;");
    ui->betDrawButton->setStyleSheet("background-color: #6d6d6d; margin: 0px 2px 0px 2px;");
    ui->betAwayButton->setStyleSheet("background-color: #6d6d6d;");
}


void MainWindow::on_pushButton_clicked()
{
    Score score;
    QString text = ui->textEdit->toPlainText();
    bool isOk;
    text.toInt(&isOk);
    QString selectedChoice = QString::number(bet.GetSelectedBetOption());

    if (isOk && selectedChoice != "-1")
    {
        QString selectedOdds = QString::number(bet.GetSelectedOdds());
        ui->team_1_score->setText("");
        ui->team_2_score->setText("");

        ui->textEdit_2->append("Obstawiono " + text + " na " + selectedChoice + " po kursie " + selectedOdds + ".");
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

        ResetAfterBet();
    }

}

void MainWindow::on_betHomeButton_clicked()
{
    bet.SetSelectedBetOption(1);
    ui->betHomeButton->setStyleSheet("background-color: #daa520;");
    ui->betDrawButton->setStyleSheet("background-color: #6d6d6d; margin: 0px 2px 0px 2px;");
    ui->betAwayButton->setStyleSheet("background-color: #6d6d6d;");
}


void MainWindow::on_betDrawButton_clicked()
{
    bet.SetSelectedBetOption(0);
    ui->betHomeButton->setStyleSheet("background-color: #6d6d6d;");
    ui->betDrawButton->setStyleSheet("background-color: #daa520; margin: 0px 2px 0px 2px;");
    ui->betAwayButton->setStyleSheet("background-color: #6d6d6d;");
}


void MainWindow::on_betAwayButton_clicked()
{
    bet.SetSelectedBetOption(2);
    ui->betHomeButton->setStyleSheet("background-color: #6d6d6d;");
    ui->betDrawButton->setStyleSheet("background-color: #6d6d6d; margin: 0px 2px 0px 2px;");
    ui->betAwayButton->setStyleSheet("background-color: #daa520;");
}

