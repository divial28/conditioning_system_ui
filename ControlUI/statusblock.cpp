#include "statusblock.h"

StatusBlock::StatusBlock(NetworkClient* client, QWidget* parent)
    : QWidget(parent), m_NetWorker(client)
{
    auto Grid = new QGridLayout(this);
    std::vector<ScalingLabel*> labels;
    const char* labelNames[] = {"System status", "First block", "Second block", "Third block", "", "", "", ""};

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            labels.push_back(new ScalingLabel(labelNames[i*4 + j]));
            labels.back()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            Grid->addWidget(labels[i*4 + j], i, j);
        }
    }

    for(int j = 0; j < 4; j++)
    {
        labels[j]->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
        labels[4 + j]->setFrameStyle(QFrame::Box);

        //make lower labels in grid looks like indicator light
        labels[4 + j]->setAutoFillBackground(true);
    }

    //make lower labels in grid acts like indicator light
    connect(m_NetWorker, &NetworkClient::SystemStatusChanged,
            labels[4], &ScalingLabel::SetBackground);
    connect(m_NetWorker, &NetworkClient::FirstBlockStatusChanged,
            labels[5], &ScalingLabel::SetBackground);
    connect(m_NetWorker, &NetworkClient::SecondBlockStatusChanged,
            labels[6], &ScalingLabel::SetBackground);
    connect(m_NetWorker, &NetworkClient::ThirdBlockStatusChanged,
            labels[7], &ScalingLabel::SetBackground);

}
