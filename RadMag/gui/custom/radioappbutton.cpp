#include "radioappbutton.h"

RadioAppButton::RadioAppButton(QWidget *parent) : QPushButton(parent)
{

}

RadioAppButton::RadioAppButton(QString iconSource, QString toolTip, QWidget *parent) : QPushButton(parent)
{
    setIcon(QIcon(iconSource));
    setToolTip(toolTip);
}
