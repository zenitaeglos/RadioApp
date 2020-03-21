#include "controlsguibottom.h"

ControlsGuiBottom::ControlsGuiBottom(QWidget *parent) : QWidget(parent),
    mainGuiBottomLayout(new QHBoxLayout),
    playButton(new RadioAppButton(DataSource::resource(DataSource::Play), "Play", this)),
    playerInfo(new QLabel(this)),
    radioIconButton(new QPushButton(this))
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

QPushButton *ControlsGuiBottom::getRadioIconButton() const
{
    return radioIconButton;
}

void ControlsGuiBottom::setupUI()
{
    playButton->setMinimumHeight(40);
    playButton->setMaximumHeight(40);
    playButton->setMaximumWidth(40);

    radioIconButton->setMinimumSize(QSize(60, 60));
    radioIconButton->setIconSize(QSize(60, 60));
    radioIconButton->setCheckable(false);
    radioIconButton->setFlat(true);


    playerInfo->setText("");
    playerInfo->setMinimumWidth(width() / 2);
    playerInfo->setWordWrap(true);

    mainGuiBottomLayout->addWidget(playButton);
    mainGuiBottomLayout->addWidget(playerInfo);
    //mainGuiBottomLayout->addStretch();
    mainGuiBottomLayout->addWidget(radioIconButton);

    setLayout(mainGuiBottomLayout);
}
