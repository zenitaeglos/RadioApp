#ifndef CONTROLSGUIBOTTOM_H
#define CONTROLSGUIBOTTOM_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class ControlsGuiBottom : public QWidget
{
    Q_OBJECT
public:
    explicit ControlsGuiBottom(QWidget *parent = nullptr);


private:
    QPushButton* playButton;
    QHBoxLayout* mainGuiBottomLayout;
};

#endif // CONTROLSGUIBOTTOM_H
