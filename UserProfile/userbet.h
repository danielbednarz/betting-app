#ifndef USERBET_H
#define USERBET_H

#include <QString>


using namespace std;

class UserBet
{
public:
    UserBet(int Id, int Money, int BetType, QString HomeTeamName, QString AwayTeamName, bool IsWon);
    int id;
    int money;
    int betType;
    QString homeTeamName;
    QString awayTeamName;
    bool isWon;
};

#endif // USERBET_H
