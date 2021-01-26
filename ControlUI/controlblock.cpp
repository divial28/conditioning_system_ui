#include "controlblock.h"

ControlBlock::ControlBlock(NetworkClient* client, bool darkTheme, QWidget* parent) :
    QWidget(parent), m_NetWorker(client), m_darkTheme(darkTheme)
{
    auto Grid = new QGridLayout(this);

    // control elements
    auto ThemeButton = new ScalingButton("Theme");
    ThemeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ThemeButton->setMinimumHeight(20);

    auto PowerButton = new ScalingButton("Power");
    PowerButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    PowerButton->setMinimumHeight(20);
    PowerButton->setCheckable(true);

    auto TemperatureSlider = new AdvancedSlider("Temperature");
    TemperatureSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    TemperatureSlider->SetRange(0, 50);

    auto DirectionSlider = new AdvancedSlider("Direction");
    DirectionSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    DirectionSlider->SetRange(0, 90);

    // compose
    Grid->addWidget(ThemeButton, 0, 0);
    Grid->addWidget(PowerButton, 0, 1);
    Grid->addWidget(TemperatureSlider, 1, 0, 1, 2);
    Grid->addWidget(DirectionSlider, 2, 0, 1, 2);

    Grid->setRowStretch(0, 1);
    Grid->setRowStretch(1, 2);
    Grid->setRowStretch(2, 2);

    // app control logic
    connect(ThemeButton, &ScalingButton::clicked,
            this, &ControlBlock::ChangeTheme);
    connect(PowerButton, &ScalingButton::toggled,
            this, &ControlBlock::OnPowerSwitched);

    // recieved data must be
    connect(m_NetWorker, &NetworkClient::PowerSwitched,
            PowerButton, &ScalingButton::ForceSetChecked);
    connect(m_NetWorker, &NetworkClient::TemperatureChanged,
            TemperatureSlider, &AdvancedSlider::SetValue);
    connect(m_NetWorker, &NetworkClient::DirectionChanged,
             DirectionSlider, &AdvancedSlider::SetValue);

    // sending data on each control value changed
    connect(PowerButton, &ScalingButton::clicked,
            [this] (bool value) { m_NetWorker->Send(TargetOption::Power, value); });
    connect(TemperatureSlider, &AdvancedSlider::ValueChanged,
            [this] (int value) { m_NetWorker->Send(TargetOption::Temperature, value); });
    connect(DirectionSlider, &AdvancedSlider::ValueChanged,
            [this] (int value) { m_NetWorker->Send(TargetOption::Direction, value) ;});

    SetTheme();

}

void ControlBlock::ChangeTheme()
{
    m_darkTheme = !m_darkTheme;

    SetTheme();
}

void ControlBlock::OnPowerSwitched(bool power)
{
    auto SliderList = findChildren<AdvancedSlider*>();
    foreach(auto Slider, SliderList)
        Slider->setEnabled(power);
}

void ControlBlock::SetTheme()
{
    QPalette Palette;
    if(m_darkTheme)
    {
        Palette.setColor(QPalette::Window, QColor(40, 40, 40));
        Palette.setColor(QPalette::WindowText, Qt::white);
        Palette.setColor(QPalette::Base, QColor(15, 15, 15));
        Palette.setColor(QPalette::Text, Qt::white);
        Palette.setColor(QPalette::Button, QColor(40, 40, 40));
        Palette.setColor(QPalette::ButtonText, Qt::white);
        Palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    }
    else
    {
        Palette.setColor(QPalette::Window, QColor(202, 202, 202));
        Palette.setColor(QPalette::WindowText, Qt::black);
        Palette.setColor(QPalette::Base, QColor(230, 230, 230));
        Palette.setColor(QPalette::Text, Qt::black);
        Palette.setColor(QPalette::Button, QColor(202, 202, 202));
        Palette.setColor(QPalette::ButtonText, Qt::black);
        Palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    }
    qApp->setPalette(Palette);
}
