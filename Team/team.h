#ifndef TEAM_H
#define TEAM_H

#include <QMainWindow>
#include <DbConnector/DbConnector.h>
#include "mainwindow.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <QString>

using namespace std;

class Team
{
public:
    Team();
    static void SeedTeams();
    static vector<QString> DrawTeamsForMatch();
    static void SetHomeTeam(QString input);
    static void SetAwayTeam(QString input);
    static QString GetHomeTeam();
    static QString GetAwayTeam();
    static void InsertMatchResult(QString homeTeam, int homeTeamScore, QString awayTeam, int awayTeamScore);

private:
    static vector<QString> GetTeams();
    static void InsertTeamResult(QString teamName, int score, bool isHome);

    static QString homeTeam;
    static QString awayTeam;

};

#endif // TEAM_H
