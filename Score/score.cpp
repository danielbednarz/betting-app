#include "score.h"

vector<int> Score::DrawScore()
{
    vector<int> scores;
//    for (int i = 0; i < 2; i++)
//    {
//        int score = rand() % 6;
//        scores.push_back(score);
//    }

    scores.push_back(GetHomeScore().toInt());
    scores.push_back(GetAwayScore().toInt());

    SetMatchWinner(scores);

    return scores;
}

void Score::SetHomeScore(QString score)
{
    Score::homeScore = score;
}

void Score::SetAwayScore(QString score)
{
    Score::awayScore = score;
}

QString Score::GetHomeScore()
{
    return Score::homeScore;
}

QString Score::GetAwayScore()
{
    return Score::awayScore;
}

void Score::SetMatchWinner(vector<int> scores)
{
    if (scores[0] < scores[1])
    {
        matchWinner = 2;
    }
    else if (scores[0] > scores[1])
    {
        matchWinner = 1;
    }
    else if (scores[0] == scores[1])
    {
        matchWinner = 0;
    }
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

int Score::GetMatchWinner()
{
    return matchWinner;
}

