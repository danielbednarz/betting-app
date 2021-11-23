#include "score.h"
#include <chrono> //For system_clock
#include <random>
#include "mainwindow.h"
using namespace std;

vector<int> Score::DrawScore()
{
//    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//    std::default_random_engine generator(seed);

//    std::uniform_int_distribution<int> distributionInteger(0, 6); // Set the numbers for int.

//    return distributionInteger(generator);
    vector<int> scores;
    for (int i = 0; i < 2; i++)
    {
        int score = rand() % 6;
        scores.push_back(score);
    }

    return scores;
}

list<int> Score::GetGoalsMinutes(int score)
{
    list<int> goalsMins;
    for (int i =0; i < score; i++){
        int min = rand() % 89 + 1;
        goalsMins.push_back(min);
    }
    goalsMins.sort();
    return goalsMins;
}
