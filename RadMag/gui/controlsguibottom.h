#ifndef CONTROLSGUIBOTTOM_H
#define CONTROLSGUIBOTTOM_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>

class ControlsGuiBottom : public QWidget
{
    Q_OBJECT
public:
    explicit ControlsGuiBottom(QWidget *parent = nullptr);

    QPushButton* getPlayButton() const;
    void setRadioName(QString newRadioName);

private:
    void setupUI();
    QHBoxLayout* mainGuiBottomLayout;    
    QPushButton* playButton;
    QLabel* playerInfo;
};

#endif // CONTROLSGUIBOTTOM_H
