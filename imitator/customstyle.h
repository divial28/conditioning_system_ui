#ifndef CUSTOMSTYLE_H
#define CUSTOMSTYLE_H

#include <QProxyStyle>
#include <QStyleOption>
#include "uisettings.h"

/*
 * CustomStyle class - ProxyStyle class with reimplemented for QSlider functions
 */
class CustomStyle : public QProxyStyle
{
public:
    CustomStyle(const QString &key);

    QRect subControlRect(QStyle::ComplexControl control,
                         const QStyleOptionComplex *option,
                         SubControl subcontrol,
                         const QWidget *widget = 0
                         ) const override;

    int pixelMetric ( PixelMetric metric, const QStyleOption * option = 0,
                      const QWidget * widget = 0 ) const override;

};

#endif // CUSTOMSTYLE_H
