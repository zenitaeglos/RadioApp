#include "controlsguibottom.h"

ControlsGuiBottom::ControlsGuiBottom(QWidget *parent) : QWidget(parent),
    mainGuiBottomLayout(new QHBoxLayout),
    playButton(new QPushButton(this)),
    stopButton(new QPushButton(this))
{
    playButton->setText("Play");
    stopButton->setText("Stop");

    playButton->setMinimumHeight(50);
    playButton->setMaximumWidth(100);

    stopButton->setMinimumHeight(50);
    stopButton->setMaximumWidth(100);

    mainGuiBottomLayout->addWidget(playButton);
    mainGuiBottomLayout->addWidget(stopButton);

    setLayout(mainGuiBottomLayout);
}

QPushButton *ControlsGuiBottom::getPlayButton() const
{
    return playButton;
}

QPushButton *ControlsGuiBottom::getStopButton() const
{
    return stopButton;
}
