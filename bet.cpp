#include "bet.h"
#include "Score/score.h"
#include "user.h"
#include <random>
#include <chrono>
#include <vector>
#include <DbConnector/DbConnector.h>

float Bet::homeOdds;
float Bet::drawOdds;
float Bet::awayOdds;
int Bet::betAmount;
int Bet::selectedBetOption = -1;

using namespace std;

void Bet::CreateBet()
{

}

void Bet::AddBet(Score score)
{
    int userId = User::GetUserId();
    int betAmount = Bet::GetBetAmount();
    int matchWinner = score.GetMatchWinner();
    // Do przypisania matchId w inny sposob - po ustaleniu w jaki sposob bedziemy je tworzyc (serwer?)
    QString matchQuery = "INSERT INTO Matches VALUES ('" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "');";
    int matchId = DbConnector::InsertQuery(matchQuery);
    QString betQuery = "INSERT INTO Bets VALUES (" + QString::number(betAmount) + ", " + QString::number(matchWinner) + ", NULL, " + QString::number(matchId) + ", " + QString::number(userId) + ");";
    DbConnector::InsertQuery(betQuery);
    QString takeBalanceQuery = "";
    if (selectedBetOption != matchWinner)
    {
        takeBalanceQuery = "UPDATE Users SET AccountBalance = AccountBalance - " + QString::number(betAmount) + " WHERE Id = " + QString::number(userId) + ";";
    }
    else
    {
        float wonAmount = Bet::GetBetAmount();
        switch (matchWinner)
        {
            case 0:
                wonAmount = wonAmount * Bet::drawOdds - Bet::GetBetAmount();
                break;
            case 1:
                wonAmount = wonAmount * Bet::homeOdds - Bet::GetBetAmount();
                break;
            case 2:
                wonAmount = wonAmount * Bet::awayOdds - Bet::GetBetAmount();
                break;
            default:
                wonAmount = 0;
                break;
        }
        takeBalanceQuery = "UPDATE Users SET AccountBalance = AccountBalance + " + QString::number(wonAmount) + " WHERE Id = " + QString::number(userId) + ";";
    }
    DbConnector::InsertQuery(takeBalanceQuery);
}

void Bet::SetSelectedBetOption(int option)
{
    selectedBetOption = option;
}

int Bet::GetSelectedBetOption()
{
    return selectedBetOption;
}

void Bet::DrawOdds()
{
    homeOdds = ceil((1.01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.00 - 1.01))))*100.0)/100.0;
    drawOdds = ceil((2.00 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.00 - 2.00))))*100.0)/100.0;
    awayOdds = ceil((1.01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.00 - 1.01))))*100.0)/100.0;
}

vector<float> Bet::GetOdds()
{
    vector<float> vec;
    vec.push_back(homeOdds);
    vec.push_back(drawOdds);
    vec.push_back(awayOdds);

    return vec;
}

float Bet::GetSelectedOdds()
{
    switch (selectedBetOption)
    {
        case 0:
            return drawOdds;
        case 1:
            return homeOdds;
        case 2:
            return awayOdds;
        default:
            return 0;
    }
}

void Bet::SetBetAmount(int number)
{
    betAmount = number;
}

int Bet::GetBetAmount()
{
    return betAmount;
}
