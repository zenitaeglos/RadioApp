#include "controlsguibottom.h"

ControlsGuiBottom::ControlsGuiBottom(QWidget *parent) : QWidget(parent),
    mainGuiBottomLayout(new QHBoxLayout),
    playButton(new QPushButton(this))
{
    playButton->setText("play");

    mainGuiBottomLayout->addWidget(playButton);

    setLayout(mainGuiBottomLayout);
}

QPushButton *ControlsGuiBottom::getPlayButton() const
{
    return playButton;
}
