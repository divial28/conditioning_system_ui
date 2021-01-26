#ifndef RECALCULATOR_H
#define RECALCULATOR_H

#include <QObject>
#include <QDebug>
#include "enums.h"

/* Recalculator class is a handler that recalculate values from one units to other
 * Note: Recalculator is pure virtual class so Recalculate method must be reimplemented the way u want
 */
class Recalculator : public QObject
{
    Q_OBJECT
protected:
    int m_value;
    int m_unit;

public:
    explicit Recalculator(QObject *parent = 0);
    virtual ~Recalculator() {}

protected:
    virtual void Recalculate() = 0;

public slots:
    void SetValue(int);
    void SetUnit(int);

signals:
    void ValueRecalculated(int);
};

/* Recalculator class specificly reimplemeted for Temperature
 */
class TemperatureRecalculator : public Recalculator
{
public:
    TemperatureRecalculator(QObject *parent = 0);

private:
    void Recalculate() override;
};

/* Recalculator class specificly reimplemeted for Temperature
 */
class PressureRecalculator : public Recalculator
{
public:
    PressureRecalculator(QObject *parent = 0);

private:
    void Recalculate() override;
};

#endif // RECALCULATOR_H
