#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include "enums.h"

/* NetworkClient class is kind of a router that get and send data and manage
 * which target widget must recieve value
 */

class NetworkClient : public QTcpSocket
{
    Q_OBJECT

public:
    NetworkClient(QObject* parent = 0);

public slots:
    void OnReadyRead();
    void Send(TargetOption, int);
    void OnDisconnected();

signals:
    void PowerSwitched(bool);
    void TemperatureChanged(int);
    void PressureChanged(int);
    void HumidityChanged(int);
    void DirectionChanged(int);
    void SystemStatusChanged(int);
    void FirstBlockStatusChanged(int);
    void SecondBlockStatusChanged(int);
    void ThirdBlockStatusChanged(int);
};

#endif // NETWORKCLIENT_H
