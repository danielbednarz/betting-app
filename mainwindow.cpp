#include "mainwindow.h"
#include "score.h"
#include "ui_mainwindow.h"
#include "bet.h"
#include <vector>
#include <algorithm>
Bet bet;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bet.DrawOdds();
    srand(time(0));
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
        ui->team_1_score->setText("0");
        ui->team_2_score->setText("0");
        ui->homeGoals->setText("");
        ui->awayGoals->setText("");

        ui->textEdit_2->append("Obstawiono " + text + " na " + selectedChoice + " po kursie " + selectedOdds + ".");
        ui->textEdit->setText("");

        vector<int> scores = score.DrawScore();
        list<int> homeTeamGoalsMins = score.GetGoalsMinutes(scores[0]);
        list<int> awayTeamGoalsMins = score.GetGoalsMinutes(scores[1]);

        for(int i=0; i<=90; i++) {
            bool homeFound = (std::find(homeTeamGoalsMins.begin(), homeTeamGoalsMins.end(), i) != homeTeamGoalsMins.end());
            if (homeFound == true)
            {
                ui->homeGoals->append("⚽ " + QString::number(i) + "'");
                int currentHomeScore = ui->team_1_score->text().toInt();
                currentHomeScore++;
                ui->team_1_score->setText(QString::number(currentHomeScore));
            }
            bool awayFound = (std::find(awayTeamGoalsMins.begin(), awayTeamGoalsMins.end(), i) != awayTeamGoalsMins.end());
            if (awayFound == true)
            {
                ui->awayGoals->append("⚽ " + QString::number(i) + "'");
                int currentAwayScore = ui->team_2_score->text().toInt();
                currentAwayScore++;
                ui->team_2_score->setText(QString::number(currentAwayScore));
            }
            std::chrono::milliseconds timespan(50);
            std::this_thread::sleep_for(timespan);
            ui->progressBar->setValue(i);
        }

        ResetAfterBet();
    }

}

void MainWindow::on_betHomeButton_clicked()
{
    bet.SetSelectedBetOption(1);
    ui->betHomeButton->setStyleSheet("background-color: #ff6f00;");
    ui->betDrawButton->setStyleSheet("background-color: #6d6d6d; margin: 0px 2px 0px 2px;");
    ui->betAwayButton->setStyleSheet("background-color: #6d6d6d;");
}


void MainWindow::on_betDrawButton_clicked()
{
    bet.SetSelectedBetOption(0);
    ui->betHomeButton->setStyleSheet("background-color: #6d6d6d;");
    ui->betDrawButton->setStyleSheet("background-color: #ff6f00; margin: 0px 2px 0px 2px;");
    ui->betAwayButton->setStyleSheet("background-color: #6d6d6d;");
}


void MainWindow::on_betAwayButton_clicked()
{
    bet.SetSelectedBetOption(2);
    ui->betHomeButton->setStyleSheet("background-color: #6d6d6d;");
    ui->betDrawButton->setStyleSheet("background-color: #6d6d6d; margin: 0px 2px 0px 2px;");
    ui->betAwayButton->setStyleSheet("background-color: #ff6f00;");
}

