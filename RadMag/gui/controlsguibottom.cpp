#include "controlsguibottom.h"

ControlsGuiBottom::ControlsGuiBottom(QWidget *parent) : QWidget(parent),
    mainGuiBottomLayout(new QHBoxLayout),
    playButton(new QPushButton(this)),
    stopButton(new QPushButton(this))
{
    playButton->setText("play");
    stopButton->setText("Stop");

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
