#include "imitator.h"

Imitator::Imitator(QWidget *parent)
    : QWidget(parent)
{


    qApp->setStyle(new CustomStyle("Fusion"));

    auto Title = new ScalingLabel("Imitator");
    auto Power = new QPushButton("Power");
    Power->setCheckable(true);

    //add controls for all options we need
    auto TemperatureSlider = new AdvancedSlider("Temperature");
    TemperatureSlider->SetRange(0, 50);
    auto PressureSlider = new AdvancedSlider("Pressure");
    PressureSlider->SetRange(0, 999);
    auto HumiditySlider = new AdvancedSlider("Humidity");
    HumiditySlider->SetRange(0, 99);
    auto DirectionSlider = new AdvancedSlider("Direction");
    DirectionSlider->SetRange(0, 90);

    auto SystemLabel = new ScalingLabel("System status");
    SystemLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    auto FirstBlockLabel = new ScalingLabel("First block");
    FirstBlockLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    auto SecondBlockLabel = new ScalingLabel("Second block");
    SecondBlockLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    auto ThirdBlockLabel = new ScalingLabel("Third block");
    ThirdBlockLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    auto SystemStatus = CreateComboBox();
    auto FirstBlockStatus = CreateComboBox();
    auto SecondBlockStatus = CreateComboBox();
    auto ThirdBlockStatus = CreateComboBox();

    //compose all widgets
    auto Grid = new QGridLayout(this);
    Grid->addWidget(Title,              0, 0, 1, 2);
    Grid->addWidget(Power,              0, 2, 1, 2);
    Grid->addWidget(TemperatureSlider,  1, 0, 1, 4);
    Grid->addWidget(PressureSlider,     2, 0, 1, 4);
    Grid->addWidget(HumiditySlider,     3, 0, 1, 4);
    Grid->addWidget(DirectionSlider,    4, 0, 1, 4);
    Grid->addWidget(SystemLabel,        5, 0);
    Grid->addWidget(FirstBlockLabel,    5, 1);
    Grid->addWidget(SecondBlockLabel,   5, 2);
    Grid->addWidget(ThirdBlockLabel,    5, 3);
    Grid->addWidget(SystemStatus,       6, 0);
    Grid->addWidget(FirstBlockStatus,   6, 1);
    Grid->addWidget(SecondBlockStatus,  6, 2);
    Grid->addWidget(ThirdBlockStatus,   6, 3);

    Grid->setRowStretch(1, 0);
    Grid->setRowStretch(2, 0);
    Grid->setRowStretch(3, 0);
    Grid->setRowStretch(4, 0);
    Grid->setRowStretch(5, 0);


    setMinimumSize(300, 400);

    setLayout(Grid);

    //imitator switched off on bootup
    OnPowerSwitched(false);

    m_NetWorker = new NetworkServer();

    connect(Power, &QPushButton::toggled, this, &Imitator::OnPowerSwitched);

    //route data to widgets
    connect(m_NetWorker, &NetworkServer::TemperatureChanged,
            TemperatureSlider, &AdvancedSlider::SetValue);
    connect(m_NetWorker, &NetworkServer::DirectionChanged,
            DirectionSlider, &AdvancedSlider::SetValue);
    connect(m_NetWorker, &NetworkServer::PowerSwitched,
            Power, &QPushButton::toggle);

    //regular send widget values
    connect(Power, &QPushButton::clicked,
            [this] (bool value) { m_NetWorker->Send(TargetOption::Power, value); });
    connect(TemperatureSlider, &AdvancedSlider::ValueChanged,
            [this] (int value) { m_NetWorker->Send(TargetOption::Temperature, value); });
    connect(PressureSlider, &AdvancedSlider::ValueChanged,
            [this] (int value) { m_NetWorker->Send(TargetOption::Pressure, value); });
    connect(HumiditySlider, &AdvancedSlider::ValueChanged,
            [this] (int value) { m_NetWorker->Send(TargetOption::Humidity, value); });
    connect(DirectionSlider, &AdvancedSlider::ValueChanged,
            [this] (int value) { m_NetWorker->Send(TargetOption::Direction, value); });
    connect(SystemStatus, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this] (int value) { m_NetWorker->Send(TargetOption::SystemStatus, value); });
    connect(FirstBlockStatus, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this] (int value) { m_NetWorker->Send(TargetOption::FirstBlockStatus, value); });
    connect(SecondBlockStatus, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this] (int value) { m_NetWorker->Send(TargetOption::SecondBlockStatus, value); });
    connect(ThirdBlockStatus, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this] (int value) { m_NetWorker->Send(TargetOption::ThirdBlockStatus, value); });

    //send all data on new connection
    connect(m_NetWorker, &NetworkServer::newConnection,
            this, &Imitator::OnNewConnection);


}

void Imitator::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    //calculate ratio according to window width and height
    QRect Rect = this->contentsRect();
    int ratio;
    int ratioByHeight = Rect.height() / 18;
    int ratioByWidth = Rect.width() / 30;

    if(ratioByHeight > ratioByWidth)
        ratio = ratioByWidth;
    else
        ratio = ratioByHeight;

    //set font size of all wiget in app
    auto widgetList = findChildren<QWidget*>();
    foreach(auto widget, widgetList)
    {
        QFont font = widget->font();
        font.setPixelSize(ratio);
        widget->setFont(font);
    }

    UISettings::SliderHandleSize = ratio;

}

QComboBox* Imitator::CreateComboBox()
{
    QComboBox* NewComboBox = new QComboBox();
    NewComboBox->addItem("good");
    NewComboBox->addItem("normal");
    NewComboBox->addItem("bad");
    return NewComboBox;
}

//disable or enable all control widgets
void Imitator::OnPowerSwitched(bool power)
{
    auto sliderList = this->findChildren<AdvancedSlider*>();

    foreach(auto slider, sliderList)
    {
        slider->setEnabled(power);
    }

    auto comboBoxList = findChildren<QComboBox*>();
    foreach(auto comboBox, comboBoxList)
    {
        comboBox->setEnabled(power);
    }
}

//send all data on new connection
void Imitator::OnNewConnection()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    out << (int)TargetOption::AllData;
    out << (int) (findChild<QPushButton*>())->isChecked();

    auto sliderList = findChildren<AdvancedSlider*>();
    foreach(auto slider, sliderList)
    {
        out << slider->Value();

    }

    auto comboBoxList = findChildren<QComboBox*>();
    foreach(auto comboBox, comboBoxList)
    {
        out << comboBox->currentIndex();
    }

    m_NetWorker->SendAll(data);
}
