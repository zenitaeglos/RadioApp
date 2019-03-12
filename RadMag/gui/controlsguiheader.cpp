#include "controlsguiheader.h"

ControlsGuiHeader::ControlsGuiHeader(QWidget *parent) : QWidget(parent),
    guiHeaderLayout(new QHBoxLayout),
    searchStationsButton(new QPushButton(this)),
    searchLineEdit(new QLineEdit(this))
{
    searchLineEdit->setToolTip("Search radio station");
    searchStationsButton->setText("Search");

    guiHeaderLayout->addWidget(searchLineEdit);
    guiHeaderLayout->addWidget(searchStationsButton);

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
