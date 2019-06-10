#include "controlsguiheader.h"
#include <QDebug>

ControlsGuiHeader::ControlsGuiHeader(QWidget *parent) : QWidget(parent),
    guiHeaderLayout(new QHBoxLayout),
    searchStationsButton(new QPushButton(this)),
    searchLineEdit(new QLineEdit(this)),
    volumeSlider(new QSlider(Qt::Horizontal, this))
{
    setupUI();

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

void ControlsGuiHeader::setupUI()
{
    searchLineEdit->setPlaceholderText("Search Radio");
    searchLineEdit->setToolTip("Search radio station");
    searchStationsButton->setIcon(QIcon("://resources/baseline-search-24px.svg"));
    searchStationsButton->setIconSize(QSize(searchStationsButton->height() - 12, searchStationsButton->height() - 12));

    searchStationsButton->setToolTip("Search");

    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setValue(50);
    volumeSlider->setMaximumWidth(80);

    //searchStationsButton->setMinimumHeight(50);
    searchStationsButton->setMaximumHeight(searchLineEdit->height());

    guiHeaderLayout->addWidget(searchLineEdit);
    guiHeaderLayout->addWidget(searchStationsButton);

    guiHeaderLayout->addWidget(volumeSlider);

    setLayout(guiHeaderLayout);
}
