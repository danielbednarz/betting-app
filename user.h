#ifndef USER_H
#define USER_H

#include <QString>
#include <list>

#include "UserProfile/userbet.h"

using namespace std;

class User
{
public:
    User();
    static void LoggedIn(int id, QString login, float accBalance, list<UserBet> bets);
    static int GetUserId();
    static QString GetUserName();
    static float GetUserAccountBalance();
    static list<UserBet> GetUserBets();
    static void RenewUserBalance();
private:
    static int userId;
    static QString userName;
    static float userAccountBalance;
    static list<UserBet> userBets;
};

#endif // USER_H
