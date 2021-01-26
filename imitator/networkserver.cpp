#include "networkserver.h"

NetworkServer::NetworkServer(QObject* parent) :
    QTcpServer(parent), m_Socket(0)
{
    if(listen(QHostAddress::LocalHost, 5555))
    {
        connect(this, &QTcpServer::newConnection, this, &NetworkServer::IncommingConnection);
    }
}

void NetworkServer::IncommingConnection()
{
    //only one connection could be in one time
    if(!m_Socket)
    {
        m_Socket = nextPendingConnection();
        connect(m_Socket, &QTcpSocket::readyRead, this, &NetworkServer::OnReadyRead);
        connect(m_Socket, &QTcpSocket::disconnected, this, &NetworkServer::OnDisconnected);
    }
}

void NetworkServer::OnReadyRead()
{
    QDataStream in(m_Socket);
    TargetOption target;
    in >> target;

    int value;
    in >> value;

    switch(target)
    {
    case TargetOption::Power :
        emit PowerSwitched(value);
        break;
    case TargetOption::Temperature :
        emit TemperatureChanged(value);
        break;
    case TargetOption::Direction :
        emit DirectionChanged(value);
        break;
    }
}

//send [value] to controlUI [target]
void NetworkServer::Send(TargetOption target, int value)
{
    if(!m_Socket)
        return;
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << (int)target << value;
    qDebug() << (int)target << value;
    m_Socket->write(data);
}

void NetworkServer::SendAll(QByteArray &data)
{
    if(!m_Socket)
        return;
    m_Socket->write(data);
}

void NetworkServer::OnDisconnected()
{
    m_Socket->deleteLater();
    //socket will be deleted automatically but we need to free pointer to accept new connection
    //(i. e. remote control was restarted)
    m_Socket = 0;
}
