#include "customstyle.h"

CustomStyle::CustomStyle(const QString &key) :
    QProxyStyle(key)
{

}

//reimplement subControlRect only for slider
QRect CustomStyle::subControlRect(ComplexControl cc, const QStyleOptionComplex *opt,
                                   SubControl sc, const QWidget *widget) const
{
    QRect rect = QCommonStyle::subControlRect(cc, opt, sc, widget);
        switch (cc)
        {
        case CC_Slider:
            if (const QStyleOptionSlider *slider = qstyleoption_cast<const QStyleOptionSlider *>(opt))
            {
                switch (sc)
                {
                case SC_SliderHandle:
                {
                    rect.setHeight(proxy()->pixelMetric(PM_SliderThickness, 0, widget));
                    rect.setWidth(proxy()->pixelMetric(PM_SliderLength, 0, widget));
                    int centerY = slider->rect.center().y() - rect.height() / 2;
                    rect.moveTop(centerY);
                    break;
                }

                case SC_SliderGroove:
                {
                    QPoint grooveCenter = slider->rect.center();
                    const int grooveThickness = UISettings::SliderHandleSize/2;

                    rect.setHeight(grooveThickness);
                    rect.moveCenter(grooveCenter);
                    break;
                }
                default:
                    break;
                }
            }
            break;

        default:
            return QProxyStyle::subControlRect(cc, opt, sc, widget);
        }
    return rect;
}

//reimplement pixelMetric for slider
int CustomStyle::pixelMetric ( PixelMetric metric, const QStyleOption * option, const QWidget * widget) const
{
    switch(metric)
    {
    case PM_SliderLength  :
    case PM_SliderThickness :
        return UISettings::SliderHandleSize;

    default :
        return QProxyStyle::pixelMetric(metric,option,widget);
    }
}
