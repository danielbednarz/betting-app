#include "team.h"

QString Team::homeTeam;
QString Team::awayTeam;

Team::Team()
{

}

void Team::SeedTeams()
{
    QSqlQuery teamsQuery = DbConnector::SelectQuery("SELECT [Name] FROM Teams");

    if(teamsQuery.next() == false)
    {
        DbConnector::InsertQuery("INSERT INTO Teams VALUES ('Anglia', 'Wembley')");
        DbConnector::InsertQuery("INSERT INTO Teams VALUES ('Francja', 'Parc de Princes')");
        DbConnector::InsertQuery("INSERT INTO Teams VALUES ('Niemcy', 'Stadion Olimplijski w Berlinie')");
        DbConnector::InsertQuery("INSERT INTO Teams VALUES ('Hiszpania', 'Estadio Santiago Bernabeu')");
        DbConnector::InsertQuery("INSERT INTO Teams VALUES ('Wlochy', 'Stadio Olimpico')");
        DbConnector::InsertQuery("INSERT INTO Teams VALUES ('Polska', 'PGE Narodowy')");
    }
}

vector<QString> Team::GetTeams()
{
    QSqlQuery teamsQuery = DbConnector::SelectQuery("SELECT [Name] FROM Teams");
    vector<QString> teams;

    while(teamsQuery.next())
    {
        QString teamName = teamsQuery.value(0).toString();

        teams.push_back(teamName);
    }

    return teams;
}

vector<QString> Team::DrawTeamsForMatch()
{
    vector<QString> teamsForMatch;
    vector<QString> teams = GetTeams();

    srand(time(0));

    for(int i=0; i<2; i++)
    {
        int teamId = rand() % teams.size();

        teamsForMatch.push_back(teams[teamId]);
        teams.erase(teams.begin() + teamId);
    }

    return teamsForMatch;
}


void Team::SetHomeTeam(QString input)
{
    Team::homeTeam = input;
}

void Team::SetAwayTeam(QString input)
{
    Team::awayTeam = input;
}

QString Team::GetHomeTeam()
{
    return Team::homeTeam;
}

QString Team::GetAwayTeam()
{
    return Team::awayTeam;
}

void Team::InsertMatchResult(QString homeTeam, int homeTeamScore, QString awayTeam, int awayTeamScore)
{
    InsertTeamResult(homeTeam, homeTeamScore, true);
    InsertTeamResult(awayTeam, awayTeamScore, false);
}

void Team::InsertTeamResult(QString teamName, int score, bool isHome)
{
    QString textScore = QString::number(score);

    if(isHome)
    {
        QString query = QString("INSERT INTO TeamsMatches VALUES (%1, 1, (SELECT TOP(1) Id FROM Matches ORDER BY MatchDate DESC), (SELECT Id FROM Teams WHERE [Name] = '%2'))").arg(textScore, teamName);

        DbConnector::InsertQuery(query);
    }

    else
    {
        QString query = QString("INSERT INTO TeamsMatches VALUES (%1, 0, (SELECT TOP(1) Id FROM Matches ORDER BY MatchDate DESC), (SELECT Id FROM Teams WHERE [Name] = '%2'))").arg(textScore, teamName);

        DbConnector::InsertQuery(query);
    }
}
