#include "recalculator.h"

Recalculator::Recalculator(QObject *parent) : QObject(parent)
{

}

void Recalculator::SetValue(int newValue)
{
    m_value = newValue;
    Recalculate();
}

void Recalculator::SetUnit(int newUnit)
{
    m_unit = newUnit;
    Recalculate();
}

TemperatureRecalculator::TemperatureRecalculator(QObject *parent) :
    Recalculator(parent)
{

}

void TemperatureRecalculator::Recalculate()
{
    switch(m_unit)
    {
    case (int)TemperatureUnit::Celsius :
        emit ValueRecalculated(m_value);
        break;
    case (int)TemperatureUnit::Fahrenheit :
        emit ValueRecalculated(qRound(m_value * 9. / 5 + 32));
        break;
    case (int)TemperatureUnit::Kelvin :
        emit ValueRecalculated(m_value + 273);
        break;
    }
}

PressureRecalculator::PressureRecalculator(QObject *parent) :
    Recalculator(parent)
{

}

void PressureRecalculator::Recalculate()
{
    switch(m_unit)
    {
    case (int)PressureUnit::Pascal :
        emit ValueRecalculated(qRound(m_value * 133.322));
        break;
    case (int)PressureUnit::Millimeter :
        emit ValueRecalculated(m_value);
        break;
    }
}
