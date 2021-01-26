#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QDataStream>
#include <QDebug>
#include "enums.h"

/* NetworkServer class is a simple server that can liasten for incoming connection and
 * exchange data via TCP socket. Also it route incoming data to control widgets.
 */
class NetworkServer : public QTcpServer
{
    Q_OBJECT
public:
    NetworkServer(QObject* parent = 0);

private:
    QTcpSocket* m_Socket;

public slots:
    void IncommingConnection();
    void OnReadyRead();
    void Send(TargetOption, int);
    void SendAll(QByteArray& data);
    void OnDisconnected();

signals:
    void NewConnection();
    void PowerSwitched(bool);
    void TemperatureChanged(int);
    void DirectionChanged(int);
};

#endif // NETWORKSERVER_H
