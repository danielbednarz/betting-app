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
