#ifndef SCALINGWIDGETS_H
#define SCALINGWIDGETS_H

#include <QLabel>
#include <QSlider>
#include <QGridLayout>
#include "uisettings.h"

/* ScalingLabel class with special behavior for numbers
 */
class ScalingLabel : public QLabel
{
    Q_OBJECT
private:
    int m_length;

public:
    ScalingLabel(const QString title, int length = 0, QWidget* parent = 0);

public slots:
    void SetNum(int value);
};

/* Advanced slider is improved QSlider that displays min/max/current values and title
 * Also have special behavior on setValue
 */
class AdvancedSlider : public QWidget
{
    Q_OBJECT

private:
    ScalingLabel*   m_MinValueLabel;
    ScalingLabel*   m_MaxValueLabel;
    ScalingLabel*   m_CurrentValueLabel;
    ScalingLabel*   m_TitleLabel;
    QSlider*        m_Slider;

public:
    AdvancedSlider(QString title = "",
                   Qt::Orientation orientation = Qt::Orientation::Horizontal,
                   QWidget* parent = 0);
    void SetRange(int min, int  max);
    int Value() { return m_Slider->value(); }

public slots:
    void SetValue(int);

signals:
    void ValueChanged(int);

};

#endif // SCALINGWIDGETS_H
