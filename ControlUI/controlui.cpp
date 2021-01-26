#include "controlui.h"

ControlUI::ControlUI(QWidget *parent)
    : QWidget(parent), m_Settings("settings.ini", QSettings::IniFormat)
{
    qApp->setStyle(new CustomStyle("Fusion"));

    m_Settings.setPath(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::applicationFilePath());



    ScalingLabel *Title = new ScalingLabel("Conditioning system");
    Title->setAlignment(Qt::AlignCenter);
    Title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    m_NetWorker = new NetworkClient();

    connect(m_NetWorker, &QTcpSocket::readyRead, m_NetWorker, &NetworkClient::OnReadyRead);

    m_ControlBlock = new ControlBlock(m_NetWorker, ReadThemeSettings());
    m_InfoBlock = new InfoBlock(m_NetWorker, ReadUnitSettings());
    m_StatusBlock = new StatusBlock(m_NetWorker);

    //parent must be empty, otherwise status block bugs
    auto WorkBox = new QHBoxLayout();
    WorkBox->addWidget(m_InfoBlock);
    WorkBox->addWidget(m_ControlBlock);
    WorkBox->setStretchFactor(m_ControlBlock, 1);

    auto MainBox = new QVBoxLayout(this);
    MainBox->addWidget(Title);
    MainBox->setStretchFactor(Title, 1);
    MainBox->addLayout(WorkBox);
    MainBox->setStretchFactor(WorkBox, 5);
    MainBox->addWidget(m_StatusBlock);
    MainBox->setStretchFactor(m_StatusBlock, 2);

    setLayout(MainBox);

    setMinimumSize(400, 300);

    ReadWindowSettings();


}

ControlUI::~ControlUI()
{
    WriteSettings();
}

void ControlUI::resizeEvent(QResizeEvent* Event)
{
    QWidget::resizeEvent(Event);

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

    //set spacing of all grid layouts
    int vSpacing = ratioByHeight / 2;
    int hSpacing = ratioByWidth / 2;
    auto gridList = findChildren<QGridLayout*>();
    foreach(auto grid, gridList)
    {
        grid->setHorizontalSpacing(hSpacing);
        grid->setVerticalSpacing(vSpacing);
    }

    UISettings::SliderHandleSize = ratio;
}

/*settings routine*/

void ControlUI::ReadWindowSettings()
{
    m_Settings.beginGroup("window");
    restoreGeometry(m_Settings.value("geometry").toByteArray());
    m_Settings.endGroup();
}

QPair<int, int> ControlUI::ReadUnitSettings()
{
    QPair<int, int> units;
    m_Settings.beginGroup("unit");
    units.first = m_Settings.value("temperature", 1).toInt();
    units.second = m_Settings.value("pressure", 2).toInt();
    m_Settings.endGroup();
    return units;
}

bool ControlUI::ReadThemeSettings()
{
    return m_Settings.value("darktheme", false).toBool();
}

void ControlUI::WriteSettings()
{
    m_Settings.beginGroup("window");
    m_Settings.setValue("geometry", saveGeometry());
    m_Settings.endGroup();

    m_Settings.beginGroup("unit");
    m_Settings.setValue("temperature", m_InfoBlock->GetTemperatureUnit());
    m_Settings.setValue("pressure", m_InfoBlock->GetPressureUnit());
    m_Settings.endGroup();

    m_Settings.setValue("darktheme", m_ControlBlock->GetTheme());
}
