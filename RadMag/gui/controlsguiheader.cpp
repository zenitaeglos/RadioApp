#include "controlsguiheader.h"

ControlsGuiHeader::ControlsGuiHeader(QWidget *parent) : QWidget(parent),
    searchStationsButton(new QPushButton(this)),
    searchLineEdit(new QLineEdit(this)),
    guiHeaderLayout(new QHBoxLayout)
{
    searchLineEdit->setToolTip("Search radio station");
    searchStationsButton->setText("Search");

    guiHeaderLayout->addWidget(searchLineEdit);
    guiHeaderLayout->addWidget(searchStationsButton);

    setLayout(guiHeaderLayout);
}
