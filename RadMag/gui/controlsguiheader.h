#ifndef CONTROLSGUIHEADER_H
#define CONTROLSGUIHEADER_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QSlider>
#include "custom/radioappbutton.h"
#include "datasource/datasource.h"

/*
 *header widget. Mainly for search bar.
 */

class ControlsGuiHeader : public QWidget
{
    Q_OBJECT
public:
    explicit ControlsGuiHeader(QWidget *parent = nullptr);

    RadioAppButton* getSearchStationsButton() const;
    QLineEdit* getSearchLineEdit() const;
    QSlider* getVolumeSlider() const;

    void keyPressEvent(QKeyEvent* event);

private:
    void setupUI();
    QHBoxLayout* guiHeaderLayout;
    RadioAppButton* searchStationsButton;
    QLineEdit* searchLineEdit;
    QSlider* volumeSlider;
};

#endif // CONTROLSGUIHEADER_H
