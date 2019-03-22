#include "controlsguibottom.h"

ControlsGuiBottom::ControlsGuiBottom(QWidget *parent) : QWidget(parent),
    mainGuiBottomLayout(new QHBoxLayout),
    playButton(new QPushButton(this)),
    stopButton(new QPushButton(this))
{

    playButton->setMinimumHeight(50);
    playButton->setMaximumWidth(100);
    playButton->setIcon(QIcon("://resources/baseline-play_circle_outline-24px.svg"));
    playButton->setIconSize(QSize(playButton->height() - 8, playButton->height() - 8));

    stopButton->setMinimumHeight(50);
    stopButton->setMaximumWidth(100);
    stopButton->setIcon(QIcon("://resources/baseline-stop-24px.svg"));
    stopButton->setIconSize(QSize(stopButton->height() - 8, stopButton->height() - 8));

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
