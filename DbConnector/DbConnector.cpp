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

bool DbConnector::InsertQuery(QString queryToExecute)
{
    QSqlQuery query;
    if (query.exec(queryToExecute)) {
        qDebug() << "Ok: "<< queryToExecute;
        return true;
    }
    else {
        qDebug() << "Blad: " << queryToExecute;
        return false;
    }
}
