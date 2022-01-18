#include "TcpServer.hpp"

using namespace std;

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    srand(time(0));

    connect(&_server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
    connect(this, &TcpServer::newMessage, this, &TcpServer::onNewMessage);
    if(_server.listen(QHostAddress::Any, 45000)) {
        qInfo() << "Listening ...";
    }
}

void TcpServer::sendMessage(const QString &message)
{
    emit newMessage(message.toUtf8());
}

void TcpServer::onNewConnection()
{
    const auto client = _server.nextPendingConnection();
    if(client == nullptr) {
        return;
    }

    qInfo() << "New client connected.";

    _clients.insert(this->getClientKey(client), client);

    connect(client, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &TcpServer::onClientDisconnected);
}

void TcpServer::onReadyRead()
{
    const auto client = qobject_cast<QTcpSocket*>(sender());

    if(client == nullptr) {
        return;
    }

    const auto message = client->readAll();


    emit newMessage(message);

    if(QString(message) == QString("Score"))
    {
        vector<int> scores;
        for (int i = 0; i < 2; i++)
        {
            int score = rand() % 6;
            scores.push_back(score);
        }

        QString response;
        response.append(QString::number(scores[0]));
        response.append(QString::number(scores[1]));

        sendMessage(response);

    }

}

void TcpServer::onClientDisconnected()
{
    const auto client = qobject_cast<QTcpSocket*>(sender());

    if(client == nullptr) {
        return;
    }

    _clients.remove(this->getClientKey(client));
}

void TcpServer::onNewMessage(const QByteArray &ba)
{
    for(const auto &client : qAsConst(_clients)) {
        client->write(ba);
        client->flush();
    }
}

QString TcpServer::getClientKey(const QTcpSocket *client) const
{
    return client->peerAddress().toString().append(":").append(QString::number(client->peerPort()));
}
