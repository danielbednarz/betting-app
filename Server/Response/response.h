#ifndef RESPONSE_H
#define RESPONSE_H

#include <QObject>
#include <QTcpServer>
#include <QHash>
#include <QTcpSocket>
#include <vector>
#include <ctime>

class Response : public QObject
{
    Q_OBJECT
public:
    explicit Response(QObject *parent = nullptr);

signals:
    void newMessage(const QByteArray &ba);
    void addToList(const QString& arg);

public slots:
    void sendMessage(const QString &message);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();
    void onNewMessage(const QByteArray &ba);

private:
    QString getClientKey(const QTcpSocket *client) const;
private:
    QTcpServer _server;
    QHash<QString, QTcpSocket*> _clients;
};

#endif // RESPONSE_H
