#include "user.h"

#include <DbConnector/DbConnector.h>
int User::userId;
QString User::userName;
float User::userAccountBalance;

User::User()
{
}

void User::LoggedIn(int id, QString login, float accBalance)
{
    User::userId = id;
    User::userName = login;
    User::userAccountBalance = accBalance;
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
