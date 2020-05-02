#include "controlsguibottom.h"

ControlsGuiBottom::ControlsGuiBottom(QWidget *parent) : QWidget(parent),
    mainGuiBottomLayout(new QHBoxLayout),
    playButton(new RadioAppButton(DataSource::resource(DataSource::Play), "Play", this)),
    playerInfo(new QLabel(this)),
    radioIconButton(new QPushButton(this)),
    networkDataManager(new NetworkDataManager(this))
{
    networkDataManager->setDelegate(this);
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

void ControlsGuiBottom::setIconToPlayButton(QIcon icon, QString toolTip)
{
    playButton->setIcon(icon);
    playButton->setToolTip(toolTip);
}

void ControlsGuiBottom::didReceiveData(QByteArray byteArrayReceived)
{
    /*
    receive the icon image bytearray
    */
    QPixmap pix;
    pix.loadFromData(byteArrayReceived);
    QIcon icon(pix);
    radioIconButton->setIcon(icon);
}

void ControlsGuiBottom::didNotReceiveData(QString error)
{
    qDebug() << error;
    //TODO set default icon
}

void ControlsGuiBottom::setIconImage(QString image)
{
    networkDataManager->fetchData(image);
}

void ControlsGuiBottom::setupUI()
{

    playButton->setMinimumHeight(60);
    playButton->setMaximumHeight(60);
    playButton->setMaximumWidth(60);

    radioIconButton->setMinimumSize(QSize(60, 60));
    radioIconButton->setIconSize(QSize(50, 50));
    radioIconButton->setCheckable(false);
    radioIconButton->setFlat(true);

    playerInfo->setText("");
    playerInfo->setMinimumWidth(width() / 2);
    playerInfo->setWordWrap(true);
    playerInfo->setStyleSheet("QLabel { color: black }");


    //setStyleSheet("QWidget { background-color: red; border: 0px }");
    setStyleSheet("QWidget { border-image: url(://resources/main_bg.png) 0 0 0 0 stretch stretch; border: 0px }");
    mainGuiBottomLayout->addWidget(playButton);
    mainGuiBottomLayout->addWidget(playerInfo);

    mainGuiBottomLayout->addWidget(radioIconButton);
    mainGuiBottomLayout->setContentsMargins(0, 0, 0, 0);
    mainGuiBottomLayout->setMargin(0);
    mainGuiBottomLayout->setSpacing(0);


    setLayout(mainGuiBottomLayout);
}
