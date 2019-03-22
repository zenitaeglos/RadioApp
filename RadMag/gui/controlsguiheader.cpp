#include "controlsguiheader.h"
#include <QDebug>

ControlsGuiHeader::ControlsGuiHeader(QWidget *parent) : QWidget(parent),
    guiHeaderLayout(new QHBoxLayout),
    searchStationsButton(new QPushButton(this)),
    searchLineEdit(new QLineEdit(this)),
    volumeSlider(new QSlider(Qt::Horizontal, this))
{
    searchLineEdit->setToolTip("Search radio station");
    searchStationsButton->setText("Search");

    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setValue(50);
    volumeSlider->setMaximumWidth(80);

    guiHeaderLayout->addWidget(searchLineEdit);
    guiHeaderLayout->addWidget(searchStationsButton);

    guiHeaderLayout->addWidget(volumeSlider);

    setLayout(guiHeaderLayout);

    //TODO connect enter pressed while QLineEdit on focus with search
}

QPushButton* ControlsGuiHeader::getSearchStationsButton() const
{
    return searchStationsButton;
}

QLineEdit *ControlsGuiHeader::getSearchLineEdit() const
{
    return searchLineEdit;
}

QSlider *ControlsGuiHeader::getVolumeSlider() const
{
    return volumeSlider;
}

void ControlsGuiHeader::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return) {
        searchStationsButton->clicked();
    }
}
