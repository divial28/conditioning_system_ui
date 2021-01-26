#ifndef INFOBLOCK_H
#define INFOBLOCK_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QLCDNumber>
#include "scalingwidgets.h"
#include "networkclient.h"
#include "enums.h"
#include "recalculator.h"


/* InfoBlock class displays temperature, pressure and humidity and
 * provides recalculating values using Recalculator handlers
 */

class InfoBlock : public QWidget
{
    Q_OBJECT

private:
    NetworkClient*  m_NetWorker;

public:
    InfoBlock(NetworkClient* client, QPair<int, int> units, QWidget* parent = 0);
    void SetUnits(int temperatureUnitIndex, int pressureUnitIndex);
    int GetTemperatureUnit();
    int GetPressureUnit();

private:
    ScalingButton* CreateButton(const char* title);
    ScalingLabel* CreateLabel(const char* title, int frameStyle = QFrame::NoFrame,
                              Qt::Alignment align = Qt::AlignLeft, QFont* font = 0,
                              int length = 0);

private slots:

};

#endif // INFOBLOCK_H
