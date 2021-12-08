#ifndef USER_H
#define USER_H

#include <QString>



class User
{
public:
    User();
    static void LoggedIn(int id, QString login, float accBalance);
    static int GetUserId();
    static QString GetUserName();
    static float GetUserAccountBalance();
    static void RenewUserBalance();
private:
    static int userId;
    static QString userName;
    static float userAccountBalance;
};

#endif // USER_H
