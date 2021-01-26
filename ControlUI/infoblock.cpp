#include "infoblock.h"

InfoBlock::InfoBlock(NetworkClient* client, QPair<int, int> units, QWidget* Parent) :
    QWidget(Parent), m_NetWorker(client)
{
    auto Grid = new QGridLayout(this);

    QFont Font("Courier New");
    Font.setStyleHint(QFont::Monospace);

    // creating labels for temperature, pressure and humidity and their values
    auto TemperatureLabel = CreateLabel("Temperature", QFrame::NoFrame,
                                        Qt::AlignLeft | Qt::AlignVCenter);
    auto PressureLabel = CreateLabel("Pressure", QFrame::NoFrame,
                                     Qt::AlignLeft | Qt::AlignVCenter);
    auto HumidityLabel = CreateLabel("Humidity", QFrame::NoFrame,
                                     Qt::AlignLeft | Qt::AlignVCenter);
    auto TemperatureValue = CreateLabel("        0", QFrame::Box,
                                        Qt::AlignRight | Qt::AlignVCenter, &Font, 9);
    auto PressureValue = CreateLabel("        0", QFrame::Box,
                                     Qt::AlignRight | Qt::AlignVCenter, &Font, 9);
    auto HumidityValue = CreateLabel("        0", QFrame::Box,
                                     Qt::AlignRight | Qt::AlignVCenter, &Font, 9);

    //temperature units
    auto Celsius = CreateButton("°C");
    auto Fahrenheit = CreateButton("°F");
    auto Kelvin = CreateButton("K");

    auto Pascal = CreateButton("Pa");
    auto Millimeter = CreateButton("mm");

    // creating button groups units to make them behave like radio buttons
    auto TemperatureUnit = new QButtonGroup(this);
    TemperatureUnit->addButton(Celsius, 1);
    TemperatureUnit->addButton(Fahrenheit, 2);
    TemperatureUnit->addButton(Kelvin, 3);
    TemperatureUnit->setExclusive(true); 

    auto PressureUnit = new QButtonGroup(this);
    PressureUnit->addButton(Pascal, 1);
    PressureUnit->addButton(Millimeter, 2);
    PressureUnit->setExclusive(true);

    // button group doesnt offer a layout so i need to do it by myself
    auto TemperatureUnitLayout = new QHBoxLayout(this);
    TemperatureUnitLayout->addWidget(Celsius);
    TemperatureUnitLayout->addWidget(Fahrenheit);
    TemperatureUnitLayout->addWidget(Kelvin);

    auto PressureUnitLayout = new QHBoxLayout(this);
    PressureUnitLayout->addWidget(Pascal);
    PressureUnitLayout->addWidget(Millimeter);

    //compose
    Grid->addWidget(TemperatureLabel, 0, 0);
    Grid->addWidget(TemperatureValue, 0, 1);
    Grid->addLayout(TemperatureUnitLayout, 1, 1);
    Grid->addWidget(PressureLabel, 2, 0);
    Grid->addWidget(PressureValue, 2, 1);
    Grid->addLayout(PressureUnitLayout, 3, 1);
    Grid->addWidget(HumidityLabel, 4, 0);
    Grid->addWidget(HumidityValue, 4, 1);

    // handlers must recalculate value depending on units
    auto TemperatureHandler = new TemperatureRecalculator(this);
    auto PressureHandler = new PressureRecalculator(this);

    // when units changes values must be recalculated
    connect(TemperatureUnit, &QButtonGroup::idToggled,
            TemperatureHandler, &Recalculator::SetUnit);
    connect(PressureUnit, &QButtonGroup::idToggled,
            PressureHandler, &Recalculator::SetUnit);

    // incoming values first get in handlers
    connect(m_NetWorker, &NetworkClient::TemperatureChanged,
            TemperatureHandler, &Recalculator::SetValue);
    connect(m_NetWorker, &NetworkClient::PressureChanged,
            PressureHandler, &Recalculator::SetValue);

    // then recalculated value transmitted to labels
    connect(TemperatureHandler, &Recalculator::ValueRecalculated,
            TemperatureValue, &ScalingLabel::SetNum);
    connect(PressureHandler, &Recalculator::ValueRecalculated,
            PressureValue, &ScalingLabel::SetNum);

    // humidty doesnt have handler so it just go directly to the label
    connect(m_NetWorker, &NetworkClient::HumidityChanged,
            HumidityValue, &ScalingLabel::SetNum);

    // units must set checked after all handlers connection for correct recalculating on load
    TemperatureUnit->button(units.first)->setChecked(true);
    PressureUnit->button(units.second)->setChecked(true);
}

//create resizable togglable button (for units)
ScalingButton* InfoBlock::CreateButton(const char* Title)
{
    ScalingButton* NewButton = new ScalingButton(Title);
    NewButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    NewButton->setCheckable(true);

    return NewButton;
}

//toggle units buttons on load
void InfoBlock::SetUnits(int TemperatureUnitIndex, int PressureUnitIndex)
{
    auto ButtonGroupList = findChildren<QButtonGroup*>();
    ButtonGroupList.front()->button(TemperatureUnitIndex)->setChecked(true);
    ButtonGroupList.back()->button(PressureUnitIndex)->setChecked(true);
}

int InfoBlock::GetTemperatureUnit()
{
    auto ButtonGroupList = findChildren<QButtonGroup*>();
    int unit =  ButtonGroupList.front()->checkedId();
    return unit;
}

int InfoBlock::GetPressureUnit()
{
    auto ButtonGroupList = findChildren<QButtonGroup*>();
    int unit = ButtonGroupList.back()->checkedId();
    return unit;
}

ScalingLabel* InfoBlock::CreateLabel(const char* Title, int QFrameStyle,
                                     Qt::Alignment Align, QFont* Font, int Length)
{
    ScalingLabel* NewLabel = new ScalingLabel(Title, Length, this);
    NewLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    NewLabel->setFrameStyle(QFrameStyle);
    NewLabel->setAlignment(Align);
    if(Font)
    {
        NewLabel->setFont(*Font);
    }

    return NewLabel;
}

