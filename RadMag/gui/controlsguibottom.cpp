#include "controlsguibottom.h"

ControlsGuiBottom::ControlsGuiBottom(QWidget *parent) : QWidget(parent),
    mainGuiBottomLayout(new QHBoxLayout),
    playButton(new QPushButton(this)),
    stopButton(new QPushButton(this)),
    playerInfo(new QLabel(this))
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
    playerInfo->setText(newRadioName);
}

void ControlsGuiBottom::setupUI()
{
    playButton->setMinimumHeight(40);
    playButton->setMaximumWidth(40);
    playButton->setIcon(QIcon("://resources/baseline-play_circle_outline-24px.svg"));
    playButton->setIconSize(QSize(playButton->height() - 20, playButton->height() - 20));
    playButton->setToolTip(tr("Play"));

    stopButton->setMinimumHeight(40);
    stopButton->setMaximumWidth(40);
    stopButton->setIcon(QIcon("://resources/baseline-stop-24px.svg"));
    stopButton->setIconSize(QSize(stopButton->height() - 20, stopButton->height() - 20));
    stopButton->setToolTip(tr("Stop"));

    playerInfo->setText("");
    playerInfo->setMinimumWidth(width() / 2);
    playerInfo->setWordWrap(true);

    mainGuiBottomLayout->addWidget(playButton);
    mainGuiBottomLayout->addWidget(stopButton);
    mainGuiBottomLayout->addWidget(playerInfo);

    setLayout(mainGuiBottomLayout);
}
