#include "controlsguibottom.h"

ControlsGuiBottom::ControlsGuiBottom(QWidget *parent) : QWidget(parent),
    mainGuiBottomLayout(new QHBoxLayout),
    playButton(new QPushButton(this)),
    playerInfo(new QLabel(this))
{
    setupUI();
}

QPushButton *ControlsGuiBottom::getPlayButton() const
{
    return playButton;
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


    playerInfo->setText("");
    playerInfo->setMinimumWidth(width() / 2);
    playerInfo->setWordWrap(true);

    mainGuiBottomLayout->addWidget(playButton);
    mainGuiBottomLayout->addWidget(playerInfo);

    setLayout(mainGuiBottomLayout);
}
