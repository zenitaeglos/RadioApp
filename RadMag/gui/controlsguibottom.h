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

#include "network/networkdatamanager.h"
#include "network/networkdelegate.h"



class ControlsGuiBottom : public QWidget, public NetworkDelegate
{
    Q_OBJECT
public:
    explicit ControlsGuiBottom(QWidget *parent = nullptr);

    QPushButton* getPlayButton() const;
    void setRadioName(QString newRadioName);

    QPushButton* getRadioIconButton() const;

    void setIconToPlayButton(QIcon icon, QString toolTip);

    // network delegate methods
    virtual void didReceiveData(QByteArray byteArrayReceived) override;
    virtual void didNotReceiveData(QString error) override;

    // set icon
    void setIconImage(QString image);

private:
    void setupUI();
    QHBoxLayout* mainGuiBottomLayout;    
    RadioAppButton* playButton;
    QLabel* playerInfo;
    QPushButton* radioIconButton;

    NetworkDataManager* networkDataManager;
};

#endif // CONTROLSGUIBOTTOM_H
