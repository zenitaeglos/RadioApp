#ifndef CONTROLSGUIBOTTOM_H
#define CONTROLSGUIBOTTOM_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include "custom/radioappbutton.h"
#include "datasource/datasource.h"



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
    RadioAppButton* playButton;
    QLabel* playerInfo;
};

#endif // CONTROLSGUIBOTTOM_H
