#include "controlsguibottom.h"

ControlsGuiBottom::ControlsGuiBottom(QWidget *parent) : QWidget(parent),
    playButton(new QPushButton(this)),
    mainGuiBottomLayout(new QHBoxLayout)
{
    playButton->setText("play");

    mainGuiBottomLayout->addWidget(playButton);

    setLayout(mainGuiBottomLayout);
}
