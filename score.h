#ifndef SCORE_H
#define SCORE_H

#include <QMainWindow>

#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>
#include <random>
#include <cstdlib>
#include <vector>

using namespace std;

class Score
{
public:
    vector<int> DrawScore();
    list<int> GetGoalsMinutes(int score);
};

#endif // SCORE_H
