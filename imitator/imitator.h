#pragma once

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QApplication>
#include "customstyle.h"
#include "scalingwidgets.h"
#include "uisettings.h"
#include "networkserver.h"
#include "enums.h"

/* Imitator class imitate built-in conditioning system control that measures current
 * temperature pressure and humidity, change air direction and indicate status of system and
 * separated blocks. Imitator can interact with remote control interface via TCP socket.
 *
 */
class Imitator : public QWidget {
    Q_OBJECT

private:
    NetworkServer*  m_NetWorker;

public:
    Imitator(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QComboBox* CreateComboBox();


private slots:
    void OnPowerSwitched(bool);
    void OnNewConnection();

signals:
    void DataArrayReady(QByteArray&);
};
