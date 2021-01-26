#include "scalingwidgets.h"

ScalingLabel::ScalingLabel(const QString title, int length,
                           QWidget* parent) :
    QLabel(title, parent), m_length(length)
{

}

//convert value to string with fixed length
//fixed length achieved by using monospaced font and ' ' append
//(its the only solution I found)
void ScalingLabel::SetNum(int value)
{
    QString num = QString::number(value);

    if(m_length < num.length())
    {
        setText(num);
        return;
    }

    QString text;
    text.fill(' ', m_length - num.length());
    text.append(num);
    setText(text);
}

//allows label to act like indicator light
void ScalingLabel::SetBackground(int value)
{
    QPalette palette;
    switch(value)
    {
    case 0 :
        palette.setColor(this->backgroundRole(), Qt::green);
        setPalette(palette);
        break;
    case 1 :
        palette.setColor(this->backgroundRole(), Qt::yellow);
        setPalette(palette);
        break;
    case 2 :
        palette.setColor(this->backgroundRole(), Qt::red);
        setPalette(palette);
        break;
    default :
        break;
    }
}

ScalingButton::ScalingButton(const QString title, QWidget* parent) :
    QPushButton(title, parent)
{

}

//set checked forcing emitting toggle signal
void ScalingButton::ForceSetChecked(bool checked)
{
    if(checked == isChecked())
        emit toggled(checked);
    else
        setChecked(checked);
}

//make button narrower
QSize ScalingButton::sizeHint() const
{
    QSize Size = QPushButton::sizeHint();
    Size.setWidth(25);
    return Size;
}

AdvancedSlider::AdvancedSlider(QString title,
                             Qt::Orientation orientation,
                             QWidget* parent) :
    QWidget(parent)
{
    QFont font("Courier New");
    font.setStyleHint(QFont::Monospace);

    auto Grid = new QGridLayout(this);

    m_MinValueLabel = new ScalingLabel("0");
    m_MinValueLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_MinValueLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    m_MinValueLabel->setMinimumHeight(20);

    m_MaxValueLabel = new ScalingLabel("0");
    m_MaxValueLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_MaxValueLabel->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    m_MaxValueLabel->setMinimumHeight(20);

    m_CurrentValueLabel = new ScalingLabel(" 0", 2);
    m_CurrentValueLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_CurrentValueLabel->setFont(font);
    m_CurrentValueLabel->setFrameStyle(QFrame::Box);
    m_CurrentValueLabel->setMinimumHeight(20);
    m_CurrentValueLabel->setAutoFillBackground(true);

    m_TitleLabel = new ScalingLabel(title);
    m_TitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_TitleLabel->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
    m_TitleLabel->setMinimumHeight(20);

    m_Slider = new QSlider(orientation);
    m_Slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_Slider->setSingleStep(1);
    m_Slider->setMinimumHeight(20);
    m_Slider->setTracking(false);

    Grid->addWidget(m_MinValueLabel, 0, 0);
    Grid->addWidget(m_TitleLabel, 0, 1);
    Grid->addWidget(m_MaxValueLabel, 0, 2);
    Grid->addWidget(m_Slider, 1, 0, 1, 3);
    Grid->addWidget(m_CurrentValueLabel, 1, 3);

    Grid->setColumnStretch(1, 1);

    connect(m_Slider, &QSlider::sliderMoved,
            [this] (int value) {m_CurrentValueLabel->SetNum(value);});
    connect(m_Slider, &QSlider::valueChanged,
            [this] (int value) {m_CurrentValueLabel->SetNum(value);});
    connect(m_Slider, &QSlider::valueChanged,
            [this] (int value) {emit ValueChanged(value);} );
}

void AdvancedSlider::SetRange(int min, int max)
{
    m_Slider->setRange(min, max);
    QString minStr = QString::number(min);
    QString maxStr = QString::number(max);

    //just a trick to set title position on center between min and max
    while (minStr.length() < maxStr.length())
    {
        minStr.append(' ');
    }

    m_MinValueLabel->setText(minStr);
    m_MaxValueLabel->setText(maxStr);
}

//set value without emitting setValue signal
void AdvancedSlider::SetValue(int value)
{
    m_Slider->blockSignals(true);
    m_Slider->setValue(value);
    m_Slider->blockSignals(false);
    m_CurrentValueLabel->SetNum(value);
}
