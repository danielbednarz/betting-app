#include "initialscreen.h"
#include "ui_initialscreen.h"

InitialScreen::InitialScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InitialScreen)
{
    ui->setupUi(this);
    DbConnector::SetUpConnection();
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
    QString login = ui->loginPageLoginInputField->text();
    QString password = ui->loginPagePasswordInputField->text();

    QString query = QString("SELECT Id, Login, AccountBalance FROM Users WHERE Login = '%1' AND Password = '%2'").arg(login, password);

    QSqlQuery queryStatus = DbConnector::SelectQuery(query);

    if (queryStatus.next() == true) {
        QMessageBox::information(this, "BettingApp", "Zalogowano pomyślnie");

        int userId = queryStatus.value(0).toInt();
        QString login = queryStatus.value(1).toString();
        float accBalance = queryStatus.value(2).toFloat();
        query = QString("SELECT Id, Money, BetType, MatchId FROM Bets WHERE UserId = '%1'").arg(userId);
        queryStatus = DbConnector::SelectQuery(query);
        list<UserBet> userBets;
        while (queryStatus.next() == true) {
            UserBet userBet(queryStatus.value(0).toInt(), queryStatus.value(1).toInt(), queryStatus.value(2).toInt(), queryStatus.value(3).toInt(), "Druzyna 1", "Druzyna 2");
            userBets.push_back(userBet);
        }
        User::LoggedIn(userId, login, accBalance, userBets);

        mainWindow = new MainWindow(this);
        mainWindow->show();
        InitialScreen::hide();
    }
    else {
        QMessageBox::warning(this, "BettingApp", "Nie udało się zalogować. Błędny login lub hasło.");
    }
}


void InitialScreen::on_confirmRegisterButton_clicked()
{
    QString login = ui->registerPageLoginInputField->text();
    QString password = ui->registerPagePasswordInputField->text();
    QString confirmPassword = ui->registerPageConfirmPasswordInputField->text();

    if(password == confirmPassword) {
        QString query = QString("INSERT INTO Users VALUES ('%1', '%2', 0)").arg(login, password);

        int queryStatus = DbConnector::InsertQuery(query);

        if (queryStatus != -1) {
            QMessageBox::information(this, "BettingApp", "Konto zostało utworzone pomyślnie");
            mainWindow = new MainWindow(this);
            mainWindow->show();
            InitialScreen::hide();
        }
        else {
            qDebug() << "Blad";
            QMessageBox::warning(this, "BettingApp", "Nie udało się utworzyć konta. Podany login już istnieje.");
        }
    }
    else {
        QMessageBox::warning(this, "BettingApp", "Nie udało się utworzyć konta. Podane hasła są różne.");
    }

}

