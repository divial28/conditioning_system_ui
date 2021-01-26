#ifndef CONTROLUI_H
#define CONTROLUI_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QBoxLayout>
#include <QStyleFactory>
#include <QFont>
#include <QSettings>
#include "controlblock.h"
#include "infoblock.h"
#include "statusblock.h"
#include "scalingwidgets.h"
#include "uisettings.h"
#include "customstyle.h"
#include "networkclient.h"

/* ControlUI class is top-level widget that represents application
 * It consists of:
 * information block that displays actual imitator values,
 * control block that provide control over imitator,
 * status block that displays imitators status
 * also it write and read application settings and keeps NetworkClient object
 * that implements network connection
 */

class ControlUI : public QWidget
{
    Q_OBJECT

private:
    ControlBlock*   m_ControlBlock;
    InfoBlock*      m_InfoBlock;
    StatusBlock*    m_StatusBlock;
    NetworkClient*  m_NetWorker;
    QSettings       m_Settings;

public:

    ControlUI(QWidget *parent = nullptr);
    ~ControlUI();

private:
    void resizeEvent(QResizeEvent* event) override;
    void ReadWindowSettings();
    QPair<int, int>  ReadUnitSettings();
    bool ReadThemeSettings();
    void WriteSettings();
};
#endif // CONTROLUI_H
