#include "response.h"

using namespace std;

Response::Response(QObject *parent) : QObject(parent)
{
    srand(time(0));

    connect(&_server, &QTcpServer::newConnection, this, &Response::onNewConnection);
    connect(this, &Response::newMessage, this, &Response::onNewMessage);
    if(_server.listen(QHostAddress::Any, 45000)) {

    }
}

void Response::sendMessage(const QString &message)
{
    emit addToList(message);
    emit newMessage(message.toUtf8());
}

void Response::onNewConnection()
{
    emit addToList("Dolaczyl klient!");
    const auto client = _server.nextPendingConnection();
    if(client == nullptr) {
        return;
    }

    _clients.insert(this->getClientKey(client), client);

    connect(client, &QTcpSocket::readyRead, this, &Response::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &Response::onClientDisconnected);
}

void Response::onReadyRead()
{
    const auto client = qobject_cast<QTcpSocket*>(sender());

    if(client == nullptr) {
        return;
    }

    const auto message = client->readAll();



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

void Response::onClientDisconnected()
{
    emit addToList("Klient rozlaczyl sie.");
    const auto client = qobject_cast<QTcpSocket*>(sender());

    if(client == nullptr) {
        return;
    }

    _clients.remove(this->getClientKey(client));
}

void Response::onNewMessage(const QByteArray &ba)
{
    for(const auto &client : qAsConst(_clients)) {
        client->write(ba);
        client->flush();
    }
}

QString Response::getClientKey(const QTcpSocket *client) const
{
    return client->peerAddress().toString().append(":").append(QString::number(client->peerPort()));
}
