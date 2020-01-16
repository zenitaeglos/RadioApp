#include "controlsguibottom.h"

ControlsGuiBottom::ControlsGuiBottom(QWidget *parent) : QWidget(parent),
    mainGuiBottomLayout(new QHBoxLayout),
    playButton(new RadioAppButton(DataSource::resource(DataSource::Play), "Play", this)),
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
    playButton->setMaximumHeight(40);
    playButton->setMaximumWidth(40);


    playerInfo->setText("");
    playerInfo->setMinimumWidth(width() / 2);
    playerInfo->setWordWrap(true);

    mainGuiBottomLayout->addWidget(playButton);
    mainGuiBottomLayout->addWidget(playerInfo);

    setLayout(mainGuiBottomLayout);
}
