#ifndef RADIOAPPBUTTON_H
#define RADIOAPPBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>


class RadioAppButton : public QPushButton
{
    Q_OBJECT
public:
    explicit RadioAppButton(QWidget *parent = nullptr);
    explicit RadioAppButton(QString iconSource, QString toolTip, QWidget *parent = nullptr);

signals:

};

#endif // RADIOAPPBUTTON_H
