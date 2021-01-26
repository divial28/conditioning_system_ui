#ifndef ENUMS_H
#define ENUMS_H

//TargetOption defines which option must be changed/sent
enum class TargetOption : int
{
    Power = 0,
    Temperature,
    Pressure,
    Humidity,
    Direction,
    SystemStatus,
    FirstBlockStatus,
    SecondBlockStatus,
    ThirdBlockStatus,
    AllData
};

#endif // ENUMS_H
