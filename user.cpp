#include "user.h"

#include <DbConnector/DbConnector.h>
int User::userId;
QString User::userName;
float User::userAccountBalance;
list<UserBet> User::userBets;

User::User()
{
}

void User::LoggedIn(int id, QString login, float accBalance, list<UserBet> bets)
{
    User::userId = id;
    User::userName = login;
    User::userAccountBalance = accBalance;
    User::userBets = bets;
}

void User::RenewUserBalance()
{
    QString query = "SELECT AccountBalance FROM Users WHERE Id = " + QString::number(User::userId);
    QSqlQuery queryStatus = DbConnector::SelectQuery(query);
    if (queryStatus.next() == true)
    {
        userAccountBalance = queryStatus.value(0).toFloat();
    }
}

int User::GetUserId()
{
    return User::userId;
}

QString User::GetUserName()
{
    return User::userName;
}

float User::GetUserAccountBalance()
{
    return User::userAccountBalance;
}

list<UserBet> User::GetUserBets()
{
    return User::userBets;
}
