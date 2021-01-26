#include "networkclient.h"

NetworkClient::NetworkClient(QObject* parent) :
    QTcpSocket(parent)
{
    connectToHost(QHostAddress::LocalHost, 5555);
}

//read [value] from network and route it to [target] widget
void NetworkClient::OnReadyRead()
{
    QDataStream in(this);
    int target;
    int value;

    in >> target;

    if(target == (int)TargetOption::AllData)
    {
        in >> value;
        emit PowerSwitched(value);
        in >> value;
        emit TemperatureChanged(value);
        in >> value;
        emit PressureChanged(value);
        in >> value;
        emit HumidityChanged(value);
        in >> value;
        emit DirectionChanged(value);
        in >> value;
        emit SystemStatusChanged(value);
        in >> value;
        emit FirstBlockStatusChanged(value);
        in >> value;
        emit SecondBlockStatusChanged(value);
        in >> value;
        emit ThirdBlockStatusChanged(value);
        return;
    }


    in >> value;

    switch((TargetOption)target)
    {
    case TargetOption::Power :
        emit PowerSwitched(value);
        break;
    case TargetOption::Temperature :
        emit TemperatureChanged(value);
        break;
    case TargetOption::Pressure :
        emit PressureChanged(value);
        break;
    case TargetOption::Humidity :
        emit HumidityChanged(value);
        break;
    case TargetOption::Direction :
        emit DirectionChanged(value);
        break;
    case TargetOption::SystemStatus :
        emit SystemStatusChanged(value);
        break;
    case TargetOption::FirstBlockStatus :
        emit FirstBlockStatusChanged(value);
        break;
    case TargetOption::SecondBlockStatus :
        emit SecondBlockStatusChanged(value);
        break;
    case TargetOption::ThirdBlockStatus :
        emit ThirdBlockStatusChanged(value);
        break;
    }
}

void NetworkClient::Send(TargetOption target, int value)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << (int)target << value;
    write(data);
}

void NetworkClient::OnDisconnected()
{
    deleteLater();
}

