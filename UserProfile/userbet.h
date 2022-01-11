#ifndef USERBET_H
#define USERBET_H

#include <QString>


using namespace std;

class UserBet
{
public:
    UserBet(int Id, int Money, int BetType, int MatchId, QString HomeTeamName, QString AwayTeamName);
    int id;
    int money;
    int betType;
    int matchId;
    QString homeTeamName;
    QString awayTeamName;
};

#endif // USERBET_H
