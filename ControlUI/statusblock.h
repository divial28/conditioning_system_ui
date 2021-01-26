#ifndef STATUSBLOCK_H
#define STATUSBLOCK_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <vector>
#include "scalingwidgets.h"
#include "networkclient.h"

/* StatusBlock class represent status information about system
 *
 */
class StatusBlock : public QWidget
{
private:
    NetworkClient* m_NetWorker;

public:
    StatusBlock(NetworkClient* client, QWidget* parent = 0);

private slots:


};

#endif // STATUSBLOCK_H
