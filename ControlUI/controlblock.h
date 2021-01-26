#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H

#include <QApplication>
#include <QWidget>
#include <QLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QSlider>
#include "networkclient.h"
#include "scalingwidgets.h"
#include "customstyle.h"
#include "enums.h"

/* ControlBlock class is a widget which realize control over temperature and direction
 */
class ControlBlock : public QWidget
{
    Q_OBJECT

private:
    NetworkClient*  m_NetWorker;
    bool            m_darkTheme;

private:
    void SetTheme();

public:
    ControlBlock(NetworkClient* client, bool darkTheme = false, QWidget* parent = 0);
    bool GetTheme() { return m_darkTheme; }

private slots:
    void ChangeTheme();
    void OnPowerSwitched(bool);

};

#endif // CONTROLBLOCK_H
