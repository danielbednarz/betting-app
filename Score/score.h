#ifndef SCORE_H
#define SCORE_H

#include <QMainWindow>

#include <stdio.h>
#include <ctime>
#include <string>
#include <iostream>
#include <random>
#include <cstdlib>
#include <vector>

#include <chrono> //For system_clock
#include "mainwindow.h"

using namespace std;

class Score
{
public:
    vector<int> DrawScore();
    void SetMatchWinner(vector<int> scores);
    list<int> GetGoalsMinutes(int score);
    int GetMatchWinner();
private:
    int matchWinner;
};

#endif // SCORE_H
