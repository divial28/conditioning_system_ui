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

//enums binds temperature units with control id
enum class TemperatureUnit : int
{
    Celsius = 1,
    Fahrenheit,
    Kelvin
};

//enums binds pressure units with control id
enum class PressureUnit : int
{
    Pascal = 1,
    Millimeter
};

#endif // ENUMS_H
