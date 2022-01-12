#include "DbConnector.h"

DbConnector::DbConnector()
{
}

void DbConnector::SetUpConnection()
{
    QString appsettings("..\\betting-app\\config.ini");
    QFileInfo check_file(appsettings);

    if (check_file.exists() && check_file.isFile()) {
        QSettings settings(appsettings, QSettings::IniFormat);

        QString server = settings.value("sql/server", "").toString();
        QString database = settings.value("sql/database", "").toString();

        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
        QString connectionString = QString("Driver=SQL Server;Server=%1;Database=%2;Trusted_Connection=True;").arg(server, database);

        db.setDatabaseName(connectionString);

        if (db.open()) {
            qDebug() << "Polaczono z baza danych";
        }
        else {
            qDebug() << "Blad przy probie polaczenia z baza danych";
        }
    }
    else {
        qDebug() << "Sprawdz plik config.ini w glownym folderze aplikacji.";
    }
}

QSqlQuery DbConnector::SelectQuery(QString queryToExecute)
{
    QSqlQuery query;
    if (query.exec(queryToExecute)) {
        qDebug() << "Ok: "<< queryToExecute;
    }
    else {
        qDebug() << "Blad: " << queryToExecute;
    }

    return query;
}

int DbConnector::InsertQuery(QString queryToExecute)
{
    QSqlQuery query;
    if (query.exec(queryToExecute)) {
        qDebug() << "Ok: "<< queryToExecute;
        return query.lastInsertId().toInt();
    }
    else {
        qDebug() << "Blad: " << queryToExecute;
        return -1;
    }
}

void DbConnector::SeedData()
{
    // Matches
    QSqlQuery matchesQuery = SelectQuery("SELECT Id FROM Matches");

    if(matchesQuery.next() == false)
    {
        InsertQuery("INSERT INTO Matches VALUES('2022-07-01')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-02')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-03')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-04')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-05')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-06')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-07')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-08')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-09')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-10')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-11')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-12')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-13')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-14')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-15')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-16')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-17')");
        InsertQuery("INSERT INTO Matches VALUES('2022-07-18')");
    }

    // Teams
    QSqlQuery teamsQuery = SelectQuery("SELECT Id FROM Teams");

    if(teamsQuery.next() == false)
    {
        InsertQuery("INSERT INTO Teams VALUES ('Belgia', 'Stade Roi Baudouin')");
        InsertQuery("INSERT INTO Teams VALUES ('Francja', 'Parc des Princes')");
        InsertQuery("INSERT INTO Teams VALUES ('Brazylia', 'Mané Garrincha')");
        InsertQuery("INSERT INTO Teams VALUES ('Anglia', 'Wembley')");
        InsertQuery("INSERT INTO Teams VALUES ('Portugalia', 'Estádio da Luz')");
        InsertQuery("INSERT INTO Teams VALUES ('Hiszpania', 'Santiago Bernabéu')");
        InsertQuery("INSERT INTO Teams VALUES ('Argentyna', 'Monumental Antonio Vespucio Liberti')");
        InsertQuery("INSERT INTO Teams VALUES ('Urugwaj', 'Centenario')");
        InsertQuery("INSERT INTO Teams VALUES ('Meksyk', 'Azteca')");
        InsertQuery("INSERT INTO Teams VALUES ('Wlochy', 'Olimpico')");
        InsertQuery("INSERT INTO Teams VALUES ('Niemcy', 'Olympiastadion Berlin')");
        InsertQuery("INSERT INTO Teams VALUES ('Polska', 'PGE Narodowy')");
    }

    // TeamsMatches
    QSqlQuery teamsMatchesQuery = SelectQuery("SELECT Id FROM TeamsMatches");

    if (teamsMatchesQuery.next() == false)
    {
        InsertQuery("INSERT INTO TeamsMatches VALUES(3, 1, 1, 1)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(2, 0, 1, 2)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(6, 1, 2, 3)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(0, 0, 2, 4)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(0, 1, 3, 5)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(2, 0, 3, 6)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(1, 1, 4, 7)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(1, 0, 4, 8)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(0, 1, 5, 9)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(0, 0, 5, 10)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(4, 1, 6, 11)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(4, 0, 6, 12)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(0, 0, 7, 1)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(1, 1, 7, 2)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(4, 0, 8, 3)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(3, 1, 8, 4)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(0, 0, 9, 5)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(2, 1, 9, 6)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(1, 0, 10, 7)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(2, 1, 10, 8)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(0, 0, 11, 9)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(4, 1, 11, 10)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(4, 0, 12, 11)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(3, 1, 12, 12)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(3, 1, 13, 1)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(3, 0, 13, 12)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(0, 1, 14, 2)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(0, 0, 14, 11)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(1, 1, 15, 3)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(1, 0, 15, 10)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(6, 1, 16, 4)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(6, 0, 16, 9)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(3, 1, 17, 5)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(3, 0, 17, 8)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(2, 1, 18, 6)");
        InsertQuery("INSERT INTO TeamsMatches VALUES(2, 0, 18, 7)");
    }
}
