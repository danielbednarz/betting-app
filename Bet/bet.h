#ifndef BET_H
#define BET_H

#include "Score/score.h"
#include "User/user.h"
#include <random>
#include <chrono>
#include <vector>
#include <DbConnector/DbConnector.h>

using namespace std;

class Bet
{
public:
    static void CreateBet();
    static void AddBet(Score score);
    static void SetSelectedBetOption(int option);
    static int GetSelectedBetOption();
    static void DrawOdds(QString homeTeam, QString awayTeam);

    static vector<float> CalculateTeamsWeight(QString homeTeam, QString awayTeam);
    static float CalculateAverageGoalsPerMatch(QString team);
    static vector<float> GetOdds();
    static float GetSelectedOdds();
    static void SetBetAmount(int number);
    static int GetBetAmount();
private:
    static float RoundToTwoDecimalPlaces(float val);
    static float homeOdds;
    static float drawOdds;
    static float awayOdds;
    static int betAmount;
    static int selectedBetOption;
};

#endif // BET_H
