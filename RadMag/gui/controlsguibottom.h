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

    QPushButton* getPlayButton() const;
    QPushButton* getStopButton() const;

private:
    QHBoxLayout* mainGuiBottomLayout;    
    QPushButton* playButton;
    QPushButton* stopButton;
};

#endif // CONTROLSGUIBOTTOM_H
