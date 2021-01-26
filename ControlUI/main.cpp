#include "controlui.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ControlUI w;

    w.show();

    return a.exec();
}
