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
#include "MainWindow/mainwindow.h"

using namespace std;

class Score
{
public:
    vector<int> DrawScore();
    void SetMatchWinner(vector<int> scores);
    list<int> GetGoalsMinutes(int score);
    int GetMatchWinner();
    static void SetHomeScore(QString score);
    static void SetAwayScore(QString score);
    static QString GetHomeScore();
    static QString GetAwayScore();

private:
    static QString homeScore;
    static QString awayScore;
    int matchWinner;
};

#endif // SCORE_H
