#include "controlsguibottom.h"

ControlsGuiBottom::ControlsGuiBottom(QWidget *parent) : QWidget(parent),
    mainGuiBottomLayout(new QHBoxLayout),
    playButton(new QPushButton(this)),
    stopButton(new QPushButton(this)),
    radioName(new QLabel(this))
{
    setupUI();
}

QPushButton *ControlsGuiBottom::getPlayButton() const
{
    return playButton;
}

QPushButton *ControlsGuiBottom::getStopButton() const
{
    return stopButton;
}

void ControlsGuiBottom::setRadioName(QString newRadioName)
{
    radioName->setText(newRadioName);
}

void ControlsGuiBottom::setupUI()
{
    playButton->setMinimumHeight(50);
    playButton->setMaximumWidth(100);
    playButton->setIcon(QIcon("://resources/baseline-play_circle_outline-24px.svg"));
    playButton->setIconSize(QSize(playButton->height() - 8, playButton->height() - 8));
    playButton->setToolTip("Play");

    stopButton->setMinimumHeight(50);
    stopButton->setMaximumWidth(200);
    stopButton->setIcon(QIcon("://resources/baseline-stop-24px.svg"));
    stopButton->setIconSize(QSize(stopButton->height() - 8, stopButton->height() - 8));
    stopButton->setToolTip("Stop");

    radioName->setText("");
    radioName->setMaximumWidth(100);

    mainGuiBottomLayout->addWidget(radioName);
    mainGuiBottomLayout->addWidget(playButton);
    mainGuiBottomLayout->addWidget(stopButton);

    setLayout(mainGuiBottomLayout);
}
