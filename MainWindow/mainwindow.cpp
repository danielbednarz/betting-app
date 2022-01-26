#include "mainwindow.h"
#include "Score/score.h"
#include "ui_mainwindow.h"
#include "Bet/bet.h"
#include <vector>
#include <algorithm>

QString Score::homeScore;
QString Score::awayScore;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SetTeamsForMatch();

    srand(time(0));

    ui->loggedInAsValue->setText(User::GetUserName());
    ui->accountBalanceValue->setText(QString::number(User::GetUserAccountBalance()));

    socket.connectToHost("127.0.0.1", 45000);

    connect(&socket, &QTcpSocket::connected, this, &MainWindow::OnConnected);
    connect(&socket, &QTcpSocket::readyRead, this, &MainWindow::OnReadyRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetTeamsForMatch()
{
    vector<QString> teamsForMatch = Team::DrawTeamsForMatch();

    QString homeTeam = teamsForMatch[0];
    QString awayTeam = teamsForMatch[1];

    Team::SetHomeTeam(homeTeam);
    Team::SetAwayTeam(awayTeam);

    ui->labelHome->setText(Team::GetHomeTeam());
    ui->labelAway->setText(Team::GetAwayTeam());

    SetTeamsRate(homeTeam, awayTeam);
}

void MainWindow::SetTeamsRate(QString homeTeam, QString awayTeam)
{
    Bet::DrawOdds(homeTeam, awayTeam);

    vector<float> odds = Bet::GetOdds();

    ui->betHomeButton->setText(QString::number(odds[0]));
    ui->betDrawButton->setText(QString::number(odds[1]));
    ui->betAwayButton->setText(QString::number(odds[2]));
}

void MainWindow::ResetAfterBet()
{
    User::RenewUserBalance();
    ui->accountBalanceValue->setText(QString::number(User::GetUserAccountBalance()));

    SetTeamsForMatch();

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
        return ui->labelHome->text();
    case 2:
        return ui->labelAway->text();
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

        SendScoreRequest();
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

        ui->textEdit_2->append(Team::GetHomeTeam() + " " + QString::number(scores[0]) + ":" + QString::number(scores[1]) + " " + Team::GetAwayTeam());
        ui->textEdit->setText("");

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
    ui->userProfileHeader->setText("Witaj " + User::GetUserName() + "!");
    ui->accountBalanceProfileLabel->setText("Stan konta: " + QString::number(User::GetUserAccountBalance()));
    ui->userHistoricalBets->setHorizontalHeaderLabels(QStringList() << "Kwota" << "Druzyna domowa" << "Typ zakladu" << "Druzyna wyjazdowa" << "Rezultat");
    ui->userHistoricalBets->setColumnWidth(0, 80);
    ui->userHistoricalBets->setColumnWidth(1, 130);
    ui->userHistoricalBets->setColumnWidth(2, 100);
    ui->userHistoricalBets->setColumnWidth(3, 150);
    ui->userHistoricalBets->setColumnWidth(4, 80);
    int num = 0;
    QString query = QString("SELECT * FROM BetHistory WHERE UserId = '%1'").arg(User::GetUserId());
    QSqlQuery queryStatus = DbConnector::SelectQuery(query);
    list<UserBet> userBets;
    while (queryStatus.next() == true) {
        UserBet userBet(queryStatus.value(0).toInt(), queryStatus.value(1).toInt(), queryStatus.value(2).toInt(), queryStatus.value(3).toString(), queryStatus.value(4).toString(), queryStatus.value(5).toBool());
        userBets.push_back(userBet);
    }
    for (auto const& bet : userBets) {
        ui->userHistoricalBets->insertRow(num);
        QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(bet.money));
        ui->userHistoricalBets->setItem(num, 0, item);
        item = new QTableWidgetItem(tr("%1").arg(bet.homeTeamName));
        ui->userHistoricalBets->setItem(num, 1, item);
        item = new QTableWidgetItem(tr("%1").arg(bet.betType));
        ui->userHistoricalBets->setItem(num, 2, item);
        item = new QTableWidgetItem(tr("%1").arg(bet.awayTeamName));
        ui->userHistoricalBets->setItem(num, 3, item);
        QString result = bet.isWon ? "Wygrana" : "Przegrana";
        item = new QTableWidgetItem(tr("%1").arg(result));
        ui->userHistoricalBets->setItem(num, 4, item);
        num++;
    }
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_returnToBetPageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->userHistoricalBets->clear();
    ui->userHistoricalBets->setRowCount(0);
}

void MainWindow::OnConnected()
{
    qInfo() << "Connected to host.";
    SendScoreRequest();
}

void MainWindow::OnReadyRead()
{
    const auto message = socket.readAll();

    emit newMessage(message);

    QString score = QString(message);

    Score::SetHomeScore(score.at(0));
    Score::SetAwayScore(score.at(1));
}

void MainWindow::SendScoreRequest()
{
    QString request = "Score";

    socket.write(request.toUtf8());
    socket.flush();
}

