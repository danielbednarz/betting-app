#include "userbet.h"

UserBet::UserBet(int Id, int Money, int BetType, int MatchId, QString HomeTeamName, QString AwayTeamName)
{
    id = Id;
    money = Money;
    betType = BetType;
    matchId = MatchId;
    homeTeamName = HomeTeamName;
    awayTeamName = AwayTeamName;
}
