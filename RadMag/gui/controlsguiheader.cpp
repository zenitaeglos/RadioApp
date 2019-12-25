#include "controlsguiheader.h"
#include <QDebug>

ControlsGuiHeader::ControlsGuiHeader(QWidget *parent) : QWidget(parent),
    guiHeaderLayout(new QHBoxLayout),
    searchStationsButton(new RadioAppButton("://resources/baseline-search-24px.svg", "Search", this)),
    searchLineEdit(new QLineEdit(this)),
    volumeSlider(new QSlider(Qt::Horizontal, this))
{
    setupUI();

    //TODO connect enter pressed while QLineEdit on focus with search
}

RadioAppButton* ControlsGuiHeader::getSearchStationsButton() const
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

void ControlsGuiHeader::setupUI()
{
    searchLineEdit->setPlaceholderText(tr("Search Radio"));
    searchLineEdit->setToolTip(tr("Search radio station"));

    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setValue(50);
    volumeSlider->setMaximumWidth(80);
    volumeSlider->setToolTip(tr("Change volume"));

    searchStationsButton->setMaximumHeight(searchLineEdit->height());

    guiHeaderLayout->addWidget(searchLineEdit);
    guiHeaderLayout->addWidget(searchStationsButton);

    guiHeaderLayout->addWidget(volumeSlider);
    guiHeaderLayout->setMargin(0);
    guiHeaderLayout->setSpacing(2);

    setLayout(guiHeaderLayout);
}
