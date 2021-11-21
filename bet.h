#ifndef BET_H
#define BET_H
#include <vector>

using namespace std;

class Bet
{
public:
    void CreateBet();
    void SetSelectedBetOption(int option);
    int GetSelectedBetOption();
    void DrawOdds();
    vector<float> GetOdds();
    float GetSelectedOdds();
private:
    float homeOdds;
    float drawOdds;
    float awayOdds;
    int selectedBetOption = -1;
};

#endif // BET_H
