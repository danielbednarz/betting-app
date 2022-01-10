#ifndef BET_H
#define BET_H
#include "Score/score.h"

#include <vector>

using namespace std;

class Bet
{
public:
    static void CreateBet();
    static void AddBet(Score score);
    static void SetSelectedBetOption(int option);
    static int GetSelectedBetOption();
    static void DrawOdds();
    static vector<float> GetOdds();
    static float GetSelectedOdds();
    static void SetBetAmount(int number);
    static int GetBetAmount();
private:
    static float homeOdds;
    static float drawOdds;
    static float awayOdds;
    static int betAmount;
    static int selectedBetOption;
};

#endif // BET_H
