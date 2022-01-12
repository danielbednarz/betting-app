#include "bet.h"

float Bet::homeOdds;
float Bet::drawOdds;
float Bet::awayOdds;
int Bet::betAmount;
int Bet::selectedBetOption = -1;

using namespace std;

void Bet::CreateBet()
{

}

void Bet::AddBet(Score score)
{
    int userId = User::GetUserId();
    int betAmount = Bet::GetBetAmount();
    int matchWinner = score.GetMatchWinner();
    // Do przypisania matchId w inny sposob - po ustaleniu w jaki sposob bedziemy je tworzyc (serwer?)
    QString matchQuery = "INSERT INTO Matches VALUES ('" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "');";
    int matchId = DbConnector::InsertQuery(matchQuery);
    QString betQuery = "INSERT INTO Bets VALUES (" + QString::number(betAmount) + ", " + QString::number(selectedBetOption) + ", NULL, " + QString::number(matchId) + ", " + QString::number(userId) + ");";
    DbConnector::InsertQuery(betQuery);
    QString takeBalanceQuery = "";
    if (selectedBetOption != matchWinner)
    {
        takeBalanceQuery = "UPDATE Users SET AccountBalance = AccountBalance - " + QString::number(betAmount) + " WHERE Id = " + QString::number(userId) + ";";
    }
    else
    {
        float wonAmount = Bet::GetBetAmount();
        switch (matchWinner)
        {
            case 0:
                wonAmount = wonAmount * Bet::drawOdds - Bet::GetBetAmount();
                break;
            case 1:
                wonAmount = wonAmount * Bet::homeOdds - Bet::GetBetAmount();
                break;
            case 2:
                wonAmount = wonAmount * Bet::awayOdds - Bet::GetBetAmount();
                break;
            default:
                wonAmount = 0;
                break;
        }
        takeBalanceQuery = "UPDATE Users SET AccountBalance = AccountBalance + " + QString::number(wonAmount) + " WHERE Id = " + QString::number(userId) + ";";
    }
    DbConnector::InsertQuery(takeBalanceQuery);
}

void Bet::SetSelectedBetOption(int option)
{
    selectedBetOption = option;
}

int Bet::GetSelectedBetOption()
{
    return selectedBetOption;
}

void Bet::DrawOdds(QString homeTeam, QString awayTeam)
{
    vector<float> weights = CalculateTeamsWeight(homeTeam, awayTeam);
    float totalRate = 5.0;

    float homeTeamRate = totalRate - weights[0];
    float awayTeamRate = totalRate - weights[1];

    if(homeTeamRate <= 1)
    {
        homeTeamRate += 1;
        awayTeamRate -= 1;
    }

    if(awayTeamRate <= 1)
    {
        homeTeamRate -= 1;
        awayTeamRate += 1;
    }

    homeTeamRate = RoundToTwoDecimalPlaces(homeTeamRate);
    awayTeamRate = RoundToTwoDecimalPlaces(awayTeamRate);

    homeOdds = homeTeamRate; //ceil((1.01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.00 - 1.01))))*100.0)/100.0;
    drawOdds = ceil((2.00 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.00 - 2.00))))*100.0)/100.0;
    awayOdds = awayTeamRate; //ceil((1.01 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.00 - 1.01))))*100.0)/100.0;
}

float Bet::RoundToTwoDecimalPlaces(float val)
{
    QString convertedValue = QString::number(val, 'f', 2);

    return convertedValue.toFloat();
}


vector<float> Bet::CalculateTeamsWeight(QString homeTeam, QString awayTeam)
{
    vector<float> weights;

    float homeTeamAverageGoals = CalculateAverageGoalsPerMatch(homeTeam);
    float awayTeamAverageGoals = CalculateAverageGoalsPerMatch(awayTeam);

    if(homeTeamAverageGoals == 0)
    {
        homeTeamAverageGoals = 2.5;
    }
    if(awayTeamAverageGoals == 0)
    {
        awayTeamAverageGoals = 2.5;
    }

    float totalWeight = 5;
    float averageTeamGoalsSum = homeTeamAverageGoals + awayTeamAverageGoals;

    if(homeTeamAverageGoals != awayTeamAverageGoals)
    {
        float homeTeamWeightFactor = homeTeamAverageGoals / averageTeamGoalsSum;
        float awayTeamWeightFactor = 1 - homeTeamWeightFactor;

        weights.push_back(totalWeight * homeTeamWeightFactor);
        weights.push_back(totalWeight * awayTeamWeightFactor);
    }
    else
    {
        // W przypadku takiej samej sredniej liczby goli nadajemy te same wagi, przyjalem 2.5 jako srednia wage
        weights.push_back(2.5);
        weights.push_back(2.5);

        return weights;
    }

    qDebug() << weights[0] << " " << weights[1];

    return weights;
}

float Bet::CalculateAverageGoalsPerMatch(QString team)
{
    QString query = QString("SELECT AVG(CAST(Score as decimal(18,2))) FROM TeamsMatches teamsMatches JOIN Teams team ON teamsMatches.TeamId = team.Id WHERE team.[Name] = '%1'").arg(team);
    QSqlQuery averageGoalsPerMatchQuery = DbConnector::SelectQuery(query);

    if(averageGoalsPerMatchQuery.next())
    {
        return averageGoalsPerMatchQuery.value(0).toFloat();
    }
    else
    {
        return 2.5;
    }
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

void Bet::SetBetAmount(int number)
{
    betAmount = number;
}

int Bet::GetBetAmount()
{
    return betAmount;
}
