#include "mainwindow.h"
#include "Score/score.h"
#include "ui_mainwindow.h"
#include "bet.h"
#include <vector>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SetTeamsForMatch();

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

void MainWindow::SetTeamsForMatch()
{
    vector<QString> teamsForMatch = Team::DrawTeamsForMatch();

    Team::SetHomeTeam(teamsForMatch[0]);
    Team::SetAwayTeam(teamsForMatch[1]);

    ui->label_5->setText(Team::GetHomeTeam());
    ui->label_3->setText(Team::GetAwayTeam());
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

QString MainWindow::GetSelectedTeamName()
{
    switch(Bet::GetSelectedBetOption())
    {
    case 1:
        return ui->label_5->text();
    case 2:
        return ui->label_3->text();
    default:
        return "remis";
    }
}

void MainWindow::on_pushButton_clicked()
{
    Score score;
    QString text = ui->textEdit->toPlainText();
    bool isOk;
    text.toInt(&isOk);
    QString selectedChoice = GetSelectedTeamName();

    if (isOk && selectedChoice != "-1")
    {
        QString selectedOdds = QString::number(Bet::GetSelectedOdds());
        ui->team_1_score->setText("0");
        ui->team_2_score->setText("0");
        ui->homeGoals->setText("");
        ui->awayGoals->setText("");

        if(Bet::GetSelectedBetOption() == 0)
        {
            ui->textEdit_2->append("Obstawiono " + text + " na remis w meczu " + Team::GetHomeTeam() + " - " + Team::GetAwayTeam() + " po kursie " + selectedOdds + ".");
        }
        else
        {
            ui->textEdit_2->append("Obstawiono " + text + " na " + selectedChoice +  " w meczu " + Team::GetHomeTeam() + " - " + Team::GetAwayTeam() + " po kursie " + selectedOdds + ".");
        }

        ui->textEdit->setText("");

        vector<int> scores = score.DrawScore();
        list<int> homeTeamGoalsMins = score.GetGoalsMinutes(scores[0]);
        list<int> awayTeamGoalsMins = score.GetGoalsMinutes(scores[1]);

        Bet::SetBetAmount(text.toInt());
        Bet::AddBet(score);
        Team::InsertMatchResult(Team::GetHomeTeam(), scores[0], Team::GetAwayTeam(), scores[1]);

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
        SetTeamsForMatch();

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

