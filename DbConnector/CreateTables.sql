CREATE DATABASE BettingApp;
GO
USE [BettingApp]

CREATE TABLE Users (
	 [Id] int NOT NULL IDENTITY(1,1) PRIMARY KEY 
	,[Login] nvarchar(64) NOT NULL
	,[Password] nvarchar(64) NOT NULL
	,[AccountBalance] decimal(18,2),
	UNIQUE ([Login])
)

CREATE TABLE Matches (
	 [Id] int NOT NULL IDENTITY(1,1) PRIMARY KEY
	,[MatchDate] datetime2 NOT NULL
)

CREATE TABLE Bets (
	 [Id] int NOT NULL IDENTITY(1,1) PRIMARY KEY
	,[Money] decimal(18,2)
	,[BetType] int NOT NULL 
	,[NumberOfGoals] int
	,[MatchId] int NOT NULL FOREIGN KEY(MatchId) REFERENCES Matches(Id)
	,[UserId] int NOT NULL FOREIGN KEY(UserId) REFERENCES Users(Id)
)

CREATE TABLE Teams (
	 [Id] int NOT NULL IDENTITY(1,1) PRIMARY KEY
	,[Name] nvarchar(max) NOT NULL
	,[Stadium] nvarchar(max) NOT NULL
)

CREATE TABLE TeamsMatches (
	 [Id] int NOT NULL IDENTITY(1,1) PRIMARY KEY
	,[Score] int NOT NULL
	,[IsHome] bit NOT NULL
	,[MatchId] int NOT NULL FOREIGN KEY(MatchId) REFERENCES Matches(Id)
	,[TeamId] int NOT NULL FOREIGN KEY(TeamId) REFERENCES Teams(Id)
)

GO

CREATE OR ALTER VIEW BetHistory
    AS
    SELECT [match].[Id],
            [Money],
            [BetType],
                        (SELECT Name FROM Teams WHERE Id = matchesHome.TeamId) AS [HomeTeamName],
                        (SELECT Name FROM Teams WHERE Id = matchesAway.TeamId) AS [AwayTeamName],
            CASE
                WHEN BetType = 1 AND matchesHome.Score > matchesAway.Score THEN 1
                WHEN BetType = 0 AND matchesHome.Score = matchesAway.Score THEN 1
                WHEN BetType = 2 AND matchesHome.Score < matchesAway.Score THEN 1
                ELSE 0
            END as IsWon,
                        [UserId]
    FROM Bets bet
    JOIN Matches [match]
    ON [match].Id = bet.MatchId
    JOIN TeamsMatches matchesHome
    ON matchesHome.MatchId = [match].Id AND matchesHome.IsHome = 1
    JOIN TeamsMatches matchesAway
    ON matchesAway.MatchId = [match].Id AND matchesAway.IsHome = 0
