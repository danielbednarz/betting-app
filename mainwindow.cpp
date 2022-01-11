#include "mainwindow.h"
#include "score.h"
#include "ui_mainwindow.h"
#include "bet.h"
#include <vector>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Bet::DrawOdds();
    srand(time(0));
    vector<float> odds = Bet::GetOdds();
    ui->betHomeButton->setText(QString::number(odds[0]));
    ui->betDrawButton->setText(QString::number(odds[1]));
    ui->betAwayButton->setText(QString::number(odds[2]));

    ui->loggedInAsValue->setText(User::GetUserName());
    ui->accountBalanceValue->setText(QString::number(User::GetUserAccountBalance()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ResetAfterBet()
{
    User::RenewUserBalance();
    ui->accountBalanceValue->setText(QString::number(User::GetUserAccountBalance()));
    Bet::DrawOdds();
    vector<float> odds = Bet::GetOdds();
    ui->betHomeButton->setText(QString::number(odds[0]));
    ui->betDrawButton->setText(QString::number(odds[1]));
    ui->betAwayButton->setText(QString::number(odds[2]));
    // do ustalenia, czy da sie to zmienic
    Bet::SetSelectedBetOption(-1);
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
    QString selectedChoice = QString::number(Bet::GetSelectedBetOption());

    if (isOk && selectedChoice != "-1")
    {
        QString selectedOdds = QString::number(Bet::GetSelectedOdds());
        ui->team_1_score->setText("0");
        ui->team_2_score->setText("0");
        ui->homeGoals->setText("");
        ui->awayGoals->setText("");

        ui->textEdit_2->append("Obstawiono " + text + " na " + selectedChoice + " po kursie " + selectedOdds + ".");
        ui->textEdit->setText("");

        vector<int> scores = score.DrawScore();
        list<int> homeTeamGoalsMins = score.GetGoalsMinutes(scores[0]);
        list<int> awayTeamGoalsMins = score.GetGoalsMinutes(scores[1]);

        Bet::SetBetAmount(text.toInt());
        Bet::AddBet(score);

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
    Bet::SetSelectedBetOption(1);
    ui->betHomeButton->setStyleSheet("background-color: #ff6f00;");
    ui->betDrawButton->setStyleSheet("background-color: #6d6d6d; margin: 0px 2px 0px 2px;");
    ui->betAwayButton->setStyleSheet("background-color: #6d6d6d;");
}


void MainWindow::on_betDrawButton_clicked()
{
    Bet::SetSelectedBetOption(0);
    ui->betHomeButton->setStyleSheet("background-color: #6d6d6d;");
    ui->betDrawButton->setStyleSheet("background-color: #ff6f00; margin: 0px 2px 0px 2px;");
    ui->betAwayButton->setStyleSheet("background-color: #6d6d6d;");
}


void MainWindow::on_betAwayButton_clicked()
{
    Bet::SetSelectedBetOption(2);
    ui->betHomeButton->setStyleSheet("background-color: #6d6d6d;");
    ui->betDrawButton->setStyleSheet("background-color: #6d6d6d; margin: 0px 2px 0px 2px;");
    ui->betAwayButton->setStyleSheet("background-color: #ff6f00;");
}

void MainWindow::on_profileButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->userProfileHeader->setText("Witaj " + User::GetUserName() + "!");
    ui->accountBalanceProfileLabel->setText("Stan konta: " + QString::number(User::GetUserAccountBalance()));
    ui->userHistoricalBets->setHorizontalHeaderLabels(QStringList() << "Kwota" << "Druzyna domowa" << "Typ zakladu" << "Druzyna wyjazdowa");
    ui->userHistoricalBets->setColumnWidth(0, 100);
    ui->userHistoricalBets->setColumnWidth(1, 170);
    ui->userHistoricalBets->setColumnWidth(2, 120);
    ui->userHistoricalBets->setColumnWidth(3, 170);
    int num = 0;
    for (auto const& i : User::GetUserBets()) {
        ui->userHistoricalBets->insertRow(num);
        QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(i.money));
        ui->userHistoricalBets->setItem(num, 0, item);
        item = new QTableWidgetItem(tr("%1").arg(i.homeTeamName));
        ui->userHistoricalBets->setItem(num, 1, item);
        item = new QTableWidgetItem(tr("%1").arg(i.betType));
        ui->userHistoricalBets->setItem(num, 2, item);
        item = new QTableWidgetItem(tr("%1").arg(i.awayTeamName));
        ui->userHistoricalBets->setItem(num, 3, item);
        num++;
    }
}

void MainWindow::on_returnToBetPageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

