#include "bet.h"
#include <random>
#include <chrono>
#include <vector>

using namespace std;

void Bet::CreateBet()
{

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
