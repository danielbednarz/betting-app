#include "userbet.h"

UserBet::UserBet(int Id, int Money, int BetType, QString HomeTeamName, QString AwayTeamName, bool IsWon)
{
    id = Id;
    money = Money;
    betType = BetType;
    homeTeamName = HomeTeamName;
    awayTeamName = AwayTeamName;
    isWon = IsWon;
}
