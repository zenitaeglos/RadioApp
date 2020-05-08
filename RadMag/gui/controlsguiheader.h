#ifndef CONTROLSGUIHEADER_H
#define CONTROLSGUIHEADER_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QSlider>
#include <QCompleter>
#include <QMessageBox>
#include <QPropertyAnimation>
#include "custom/radioappbutton.h"
#include "datasource/datasource.h"

#include "network/networkdatamanager.h"
#include "network/networkdelegate.h"

/*
 *header widget. Mainly for search bar.
 */

class ControlsGuiHeader : public QWidget, public NetworkDelegate
{
    Q_OBJECT
public:
    explicit ControlsGuiHeader(QWidget *parent = nullptr);

    RadioAppButton* getSearchStationsButton() const;
    QLineEdit* getSearchLineEdit() const;
    QSlider* getVolumeSlider() const;

    void keyPressEvent(QKeyEvent* event) override;

    // delegate methods of networkDelegate
    virtual void didReceiveData(QByteArray byteArrayReceived) override;
    virtual void didNotReceiveData(QString error) override;


signals:
    void dataRecevied(QByteArray playLists);

private slots:
    void fetchRadioStations(bool checked);

    void changeSearchSize();

private:
    void setupUI();
    QHBoxLayout* guiHeaderLayout;
    RadioAppButton* searchStationsButton;
    QLineEdit* searchLineEdit;
    QSlider* volumeSlider;
    QCompleter* completer;

    NetworkDataManager* networkDataManager;
};

#endif // CONTROLSGUIHEADER_H
